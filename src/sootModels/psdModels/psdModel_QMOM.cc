#include "sootModels/psdModels/psdModel_QMOM.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

psdModel_QMOM::psdModel_QMOM(sourceTermStruct* sourceTerms, int nsoot_, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C)
        : psdModel(sourceTerms, nsoot_, N, G, X, C) {

    if (nsoot_%2 == 1 || nsoot_ < 1)
        throw runtime_error("Invalid number of soot moments requested");

    if (nsoot_ > 6)
        cerr << "Warning: QMOM inversion algorithm may behave unpredictably with "
                "8+ soot moments. Proceed with caution." << endl;

    nsoot = nsoot_;

    // initialize sourceTerms soot variable
    sourceTerms->sootSourceTerms.resize(nsoot, 0);

    mechType = psdMech::QMOM;
}

////////////////////////////////////////////////////////////////////////////////

void psdModel_QMOM::setSourceTerms(state& state, sourceTermStruct *sourceTerms) const {

    //---------- get weights and abscissas

//    vector<double> wts = {0};
//    vector<double> absc = {0};

    // moment downselection and wheeler algorithm inversion applied here
    getWtsAbs(state.sootVar, state.wts, state.absc);

    for (size_t i = 0; i < state.wts.size(); i++) {
        if (state.wts[i] < 0  ) { state.wts[i] = 0;  }
        if (state.absc[i] < 0)  { state.absc[i] = 0; }
    }

    //---------- get chemical rates

    double jNuc = nuc->getNucleationSootRate(state);
    double kGrw = grw->getGrowthSootRate(state);
    double kOxi = oxi->getOxidationSootRate(state);

    //---------- nucleation terms

    vector<double> nucSrcM(nsoot, 0.);
    const double mNuc = state.cMin * gasSpMW[(int)gasSp::C] / Na;      // mass of a nucleated particle
    for (size_t i = 0; i < nsoot; i++)
        nucSrcM[i] = pow(mNuc, i) * jNuc;                            // Nuc_rate = m_nuc^r * jNuc

    //---------- PAH condensation terms

    vector<double> cndSrcM(nsoot, 0);
    if (nuc->mechType == nucleationMech::PAH) {
        for (size_t i = 1; i < nsoot; i++) {                             // M0 = 0.0 for condensation by definition
            for (size_t j = 0; j < state.absc.size(); j++)
                cndSrcM[i] += coa->getCoagulationSootRate(state, nuc->DIMER.mDimer, state.absc[j]) * pow(state.absc[j], i - 1) * state.wts[j];
            cndSrcM[i] *= nuc->DIMER.nDimer * nuc->DIMER.mDimer * i;
        }
    }

    //---------- growth terms

    vector<double> grwSrcM(nsoot, 0);
    const double Acoef = M_PI * pow(abs(6 / M_PI / rhoSoot), 2.0 / 3);      // Acoef (=) kmol^2/3 / kg^2/3
    for (size_t i = 1; i < nsoot; i++)                                                // M0 = 0.0 for growth by definition
        grwSrcM[i] = kGrw * Acoef * i * Mk(i - 1.0 / 3, state.wts, state.absc);          // kg^k/m3*s

    //---------- oxidation terms

    vector<double> oxiSrcM(nsoot, 0);
    for (size_t i = 1; i < nsoot; i++)                                                // M0 = 0.0 for oxidation by definition
        oxiSrcM[i] = -kOxi * Acoef * i * Mk(i - 1.0 / 3, state.wts, state.absc);         // kg^k/m3*s

    //---------- coagulation terms

    vector<double> coaSrcM(nsoot, 0);

    for(int k=0; k < nsoot; k++) {

        // off-diagonal terms (looping half of them) with *2 incorporated
        for(int ii=1; ii < state.absc.size(); ii++)
            for(int j=0; j<ii; j++)
                coaSrcM[k] += coa->getCoagulationSootRate(state, state.absc[ii], state.absc[j]) * state.wts[ii] * state.wts[j] *
                              (k == 0 ? -1.0 : (pow(state.absc[ii] + state.absc[j], k)) - pow(state.absc[ii], k) - pow(state.absc[j], k) );      // M0 special case

        // diagonal terms
        for(int ii=0; ii < state.absc.size(); ii++)
            coaSrcM[k] += coa->getCoagulationSootRate(state, state.absc[ii], state.absc[ii]) * state.wts[ii] * state.wts[ii] *
                          (k == 0 ? -0.5 : pow(state.absc[ii], k) * (pow(2, k - 1) - 1) );                                  // M0 special case
    }

    coaSrcM[1] = 0.0;    // M1 = 0.0 for coagulation by definition

    //---------- combine to make soot source terms

    for (size_t i = 0; i < nsoot; i++)
        sourceTerms->sootSourceTerms[i] = (nucSrcM[i] + cndSrcM[i] + grwSrcM[i] + oxiSrcM[i] + coaSrcM[i]);

    //---------- get gas source terms

    for (int sp=0; sp<(int)gasSp::size; sp++) {
        if(sp == (int)gasSp::C) continue;
            sourceTerms->gasSourceTerms[sp] = nuc->getNucleationGasRates(state, nucSrcM[1]).gasSourceTerms[sp] +
                                              grw->getGrowthGasRates(state,     grwSrcM[1]).gasSourceTerms[sp] + 
                                              oxi->getOxidationGasRates(state,  oxiSrcM[1]).gasSourceTerms[sp];
    }

    //---------- get PAH source terms

    if(nuc->mechType == nucleationMech::PAH)
        for (int sp=0; sp<(int)pahSp::size; sp++)
            sourceTerms->pahSourceTerms[sp] = nuc->getNucleationPahRates(state).pahSourceTerms[sp];
}

////////////////////////////////////////////////////////////////////////////////

void psdModel_QMOM::getWtsAbs(const vector<double>& M, vector<double>& weights, vector<double>& abscissas)
{
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

void psdModel_QMOM::wheeler(const vector<double>& m, size_t N, vector<double>& w, vector<double>& x) {

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

double psdModel_QMOM::Mk(double exp, const vector<double>& wts, const vector<double>& absc)
{
	double Mk = 0;

	for (size_t i = 0; i < wts.size() / 2; i++) {
		if (wts[i] == 0 || absc[i] == 0)
			return 0;
		else
			Mk += wts[i] * pow(absc[i], exp);
	}

	return Mk;
}
