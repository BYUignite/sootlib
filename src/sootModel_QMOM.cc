#include "sootModel_QMOM.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sootModel_QMOM::sootModel_QMOM(size_t            nsoot_,
                               nucleationModel  *nucl_,
                               growthModel      *grow_,
                               oxidationModel   *oxid_,
                               coagulationModel *coag_) :
        sootModel(nsoot_, nucl_, grow_, oxid_, coag_) {

    if (nsoot_%2 == 1 || nsoot_ < 1)
        throw runtime_error("Invalid number of soot moments requested");

    if (nsoot_ > 6)
        cerr << "Warning: QMOM inversion algorithm may behave unpredictably with "
                "8+ soot moments. Proceed with caution." << endl;

    psdMechType = psdMech::QMOM;
}

////////////////////////////////////////////////////////////////////////////////

sootModel_QMOM::sootModel_QMOM(size_t          nsoot_,
                               nucleationMech  Nmech,
                               growthMech      Gmech,
                               oxidationMech   Omech,
                               coagulationMech Cmech) :
        sootModel(nsoot_, Nmech, Gmech, Omech, Cmech) {

    if (nsoot_%2 == 1 || nsoot_ < 1)
        throw runtime_error("Invalid number of soot moments requested");

    if (nsoot_ > 6)
        cerr << "Warning: QMOM inversion algorithm may behave unpredictably with "
                "8+ soot moments. Proceed with caution." << endl;

    psdMechType = psdMech::QMOM;
}

////////////////////////////////////////////////////////////////////////////////

void sootModel_QMOM::getSourceTerms(state &state, 
                                    std::vector<double> &sootSources,
                                    std::vector<double> &gasSources,
                                    std::vector<double> &pahSources) const {

    //---------- get weights and abscissas

    getWtsAbs(state.sootVar, state.wts, state.absc);    // moment downselection applied

    for (size_t i=0; i<state.wts.size(); i++) {
        if (state.wts[i] < 0)  state.wts[i]  = 0;
        if (state.absc[i] < 0) state.absc[i] = 0;
    }

    //---------- get chemical rates

    double jNuc = nucl->getNucleationSootRate(state);
    double kGrw = grow->getGrowthSootRate(state);
    double kOxi = oxid->getOxidationSootRate(state);

    //---------- nucleation terms

    vector<double> nucSrcM(nsoot, 0.);
    const double mNuc = state.cMin*gasSpMW[(int)gasSp::C]/Na;      // mass of a nucleated particle
    for (size_t i=0; i<nsoot; i++)
        nucSrcM[i] = pow(mNuc, i)*jNuc;                            // Nuc_rate = m_nuc^r * jNuc

    //---------- PAH condensation terms

    vector<double> cndSrcM(nsoot, 0);
    if (nucl->mechType == nucleationMech::PAH) {
        for (size_t i=1; i<nsoot; i++) {                             // M0 = 0.0 for condensation by definition
            for (size_t j=0; j<state.absc.size(); j++)
                cndSrcM[i] += coag->getCoagulationSootRate(state, nucl->DIMER.mDimer, state.absc[j]) * 
                              pow(state.absc[j], i - 1) * state.wts[j];
            cndSrcM[i] *= nucl->DIMER.nDimer * nucl->DIMER.mDimer * i;
        }
    }

    //---------- growth terms

    vector<double> grwSrcM(nsoot, 0);
    const double Acoef = M_PI*pow(6. /(M_PI*rhoSoot), twothird);            // Acoef (=) kmol^2/3 / kg^2/3
    for (size_t i=1; i<nsoot; i++)                                          // M0 = 0.0 for growth by definition
        grwSrcM[i] =  kGrw*Acoef*i*Mk(i - onethird, state.wts, state.absc); // kg^k/m3*s

    //---------- oxidation terms

    vector<double> oxiSrcM(nsoot, 0);
    for (size_t i=1; i<nsoot; i++)                                          // M0 = 0.0 for oxidation by definition
        oxiSrcM[i] = -kOxi*Acoef*i*Mk(i - onethird, state.wts, state.absc); // kg^k/m3*s

    //---------- coagulation terms

    vector<double> coaSrcM(nsoot, 0);

    for(int k=0; k < nsoot; k++) {
        for(int ii=1; ii<state.absc.size(); ii++)                // off-diag terms (looping half of them with *2 incorporated
            for(int j=0; j<ii; j++)
                coaSrcM[k] += coag->getCoagulationSootRate(state, state.absc[ii], state.absc[j]) * state.wts[ii] * state.wts[j] *
                              (k == 0 ? -1.0 : (pow(state.absc[ii] + state.absc[j], k)) - pow(state.absc[ii], k) - pow(state.absc[j], k) );      // M0 special case

        for(int ii=0; ii<state.absc.size(); ii++)                // diagonal trerms
            coaSrcM[k] += coag->getCoagulationSootRate(state, state.absc[ii], state.absc[ii]) * state.wts[ii] * state.wts[ii] *
                          (k == 0 ? -0.5 : pow(state.absc[ii], k) * (pow(2, k - 1) - 1) );                                  // M0 special case
    }

    coaSrcM[1] = 0.0;    // M1 = 0.0 for coagulation by definition

    //---------- combine to make soot source terms

    for (size_t i = 0; i < nsoot; i++)
        sootSources[i] = nucSrcM[i] + cndSrcM[i] + grwSrcM[i] + oxiSrcM[i] + coaSrcM[i];  // kg^k/m3*s

    //---------- set gas source terms

    vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

    nucl->getNucleationGasRates(state, nucSrcM[1], nucl_gasSources);
    grow->getGrowthGasRates(    state, grwSrcM[1], grow_gasSources);
    oxid->getOxidationGasRates( state, oxiSrcM[1], oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

    //---------- set PAH source terms

    if(nucl->mechType == nucleationMech::PAH)
        pahSources = nucl->nucleationPahRxnRates;

    //todo: what about pah condensation? (here and in other models)

}

////////////////////////////////////////////////////////////////////////////////
/** getWtsAbs function
 *
 *      Calculates weights and abscissas from moments using wheeler algorithm.
 *
 *      @param M        \input      vector of moments
 *      @param wts      \input      weights
 *      @param absc     \input      abscissas
 *
 *      NOTE: wts and absc variables DO NOT change size during downselection;
 *      instead, the extra values are set to zero. This is more convenient than
 *      resizing when wts and absc are used to reconstitute moment source terms.
 */

void sootModel_QMOM::getWtsAbs(const vector<double>& M, vector<double>& weights, vector<double>& abscissas) {
	size_t N = M.size();        // local nsoonsoot; may change with moment downselection

	for (double num : M) {      // if any moments are zero,
		if (num <= 0)           // return with zero wts and absc
			return;
	}

	bool bad_values;            // downselection flag

	vector<double> w_temp(N / 2, 0);
	vector<double> a_temp(N / 2, 0);

    // downselection loop
	do {

	    // reset flag
		bad_values = false;

		// reinitialize weights and absc with zeros
		for (size_t i = 0; i < N / 2; i++) {
			w_temp[i] = 0;
			a_temp[i] = 0;
		}

		// in 2 moment case, return MONO output
		if (N == 2) {
			w_temp[0] = M[0];
			a_temp[0] = M[1] / M[0];
			break;
		}

		// wheeler algorithm for moment inversion
		wheeler(M, N / 2, w_temp, a_temp);

		// check for bad values
		for (size_t i = 0; i < N / 2; i++) {
			if (w_temp[i] < 0 || a_temp[i] < 0)     // check for negative values
				bad_values = true;
			if (w_temp[i] > 1)                         // check for weights > 1
			    bad_values = true;
		}

		// if we find bad values, downselect to two fewer moments and try again
		if (bad_values) {
			N = N - 2;
			w_temp.resize(N / 2);
			a_temp.resize(N / 2);
		}

	}
	while (bad_values);

	// assign temporary variables to output
	for (size_t i = 0; i < w_temp.size(); i++) {
		weights[i] = w_temp[i];
		abscissas[i] = a_temp[i];
	}
}

////////////////////////////////////////////////////////////////////////////////
/** Wheeler algorithm for computing weights and abscissas from moments
 *
 *      From Marchisio and Fox (2013) Computational Models for Polydisperse and
 *      Multiphase Systems. Uses eispack function tql2 for eigenvalues and
 *      eigenvectors of a symmetric tridiagonal matrix. If eispack version tql2
 *      is desired, download eispack.hpp and eispack.cc. LApack's dstev
 *      function to compute eigenvalues and eigenvectors of symmetrical
 *      tridiagonal matrix.
 *
 *      @param m    \input     vector of moments (size = 2N)
 *      @param N    \input     number of quadrature nodes (abscissas)
 *      @param w    \output    weights
 *      @param x    \output    abscissas
 */

void sootModel_QMOM::wheeler(const vector<double>& m, size_t N, vector<double>& w, vector<double>& x) {

    vector<vector<double>> sigma(N + 1, vector<double>(N * 2, 0));
    vector<double> a(N, 0);
    vector<double> b(N, 0);
    vector<double> eval(N);
    vector<double> evec(N * N);
    vector<double> j_diag(N);
    vector<double> j_ldiag(N);

    for (size_t i = 0; i <= N * 2 - 1; i++)
        sigma[1][i] = m[i];

    a[0] = m[1] / m[0];

    for (size_t i = 1; i < N; i++) {
        for (size_t j = i; j < N * 2 - i; j++)
            sigma[i + 1][j] = sigma[i][j + 1] - a[i - 1] * sigma[i][j] - b[i - 1] * sigma[i - 1][j];
        a[i] = -sigma[i][i] / sigma[i][i - 1] + sigma[i + 1][i + 1] / sigma[i + 1][i];
        b[i] = sigma[i + 1][i] / sigma[i][i - 1];
    }

    j_diag = a;
    for (size_t i = 1; i < N; i++)
        j_ldiag[i] = -sqrt(abs(b[i]));

    for (size_t i = 0; i < N; i++)
        evec[i + N * i] = 1;

//    int flag = tql2(N, &j_diag[0], &j_ldiag[0], &evec[0]);       // for eispack

    //char VorN = 'V';
    //vector<double> work(2*N-2);
    //int info;
    //dstev_( &VorN, &N, &j_diag[0], &j_ldiag[1], &evec[0], &N, &work[0], &info);

    x = j_diag;      // j_diag are now the vector of eigenvalues.

    for (size_t i = 0; i < N; i++)
        w[i] = pow(evec[0 + i * N], 2) * m[0];
}

////////////////////////////////////////////////////////////////////////////////
/** Mk function (QMOM)
 *
 *       calculates fractional moments from weights and abscissas.
 *
 *       @param exp      \input      fractional moment to compute; corresponds to exponent
 *       @param wts      \input      weights
 *       @param absc     \input      abscissas
 *       @param Mk       \output     fractional moment value
 */

double sootModel_QMOM::Mk(double exp, const vector<double>& wts, const vector<double>& absc) {
	double Mk = 0;

	for (size_t i = 0; i < wts.size() / 2; i++) {
		if (wts[i] == 0 || absc[i] == 0)
			return 0;
		else
			Mk += wts[i] * pow(absc[i], exp);
	}

	return Mk;
}
