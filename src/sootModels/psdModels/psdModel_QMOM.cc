#include "psdModel_QMOM.h"

using namespace std;
using namespace soot;

psdModel_QMOM::psdModel_QMOM(size_t n) {

    if (n%2 == 1 || n < 1)
        throw runtime_error("Invalid number of soot moments requested");

    if (n > 6)
        cerr << "Warning: QMOM inversion algorithm may behave unpredictably with "
                "8+ soot moments. Proceed with caution." << endl;

    this->nMom = n;

    // initialize sourceTerms soot variable
    for (int i=0; i<nMom; i++)
        sourceTerms->sootSourceTerms.push_back(0);

}

////////////////////////////////////////////////////////////////////////////////
/** getSourceTermsImplementation function
 *  
 *      Calculates soot source terms using quadrature method of moments
 *      (QMOM). Returns soot, gas, and PAH source terms (where applicable). 
 *
 *      @param  state    \input     thermodynamic state
 *
 */

void psdModel_QMOM::getSourceTermsImplementation(state& state, std::ostream* out) const {

    if (out) {
        *out << " === [SootModel QMOM] ===" << endl;
        *out << endl;
    }

    vector<double> weights = {0};
    vector<double> abscissas = {0};

    //---------- set weights and abscissas

    getWtsAbs(state.sootVar, weights, abscissas);           // wheeler algorithms applied here

    for (size_t i = 0; i < weights.size(); i++) {
        if (weights.at(i) < 0)
            weights.at(i) = 0;
        if (abscissas.at(i) < 0)
            abscissas.at(i) = 0;
    }

    if (out) {
        *out << "weights (" << weights.size() << ")" << endl;
        for (size_t i = 0; i < weights.size(); i++)
            *out << i << ": " << weights.at(i) << endl;
        *out << "abscissas (" << abscissas.size() << ")" << endl;
        for (size_t i = 0; i < abscissas.size(); i++)
            *out << i << ": " << abscissas.at(i) << endl;
        *out << endl;
    }

    //---------- get chemical rates

    double jNuc = sootModel.nuc->getNucleationRate(state, abscissas, weights);
    double kGrw = sootModel.grw->getGrowthRate(state);
    double kOxi = sootModel.oxi->getOxidationRate(state);
    double jCoa = sootModel.coa->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));

    if (out) {
        *out << "jNuc: " << jNuc << endl;
        *out << "kGrw: " << kGrw << endl;
        *out << "kOxi: " << kOxi << endl;
        *out << endl;
    }

    //---------- nucleation terms

    vector<double> nucleationSourceM(state.sootVar.size(), 0.);                        // nucleation source terms for moments
    const double mNuc = state.cMin * gasSpMW.at(gasSp::C) / Na;                              // mass of a nucleated particle
    for (size_t i = 0; i < state.sootVar.size(); i++)
        nucleationSourceM.at(i) = pow(mNuc, i) * jNuc;                          // Nuc_rate = m_nuc^r * jNuc

    if (out) {
        *out << "nucleation source terms for moments (" << nucleationSourceM.size() << ")" << endl;
        for (size_t i = 0; i < nucleationSourceM.size(); i++)
            *out << i << ": " << nucleationSourceM.at(i) << endl;
        *out << endl;
    }

    //---------- PAH condensation terms

    vector<double> condensationSourceM(state.sootVar.size(), 0);                            // PAH condensation source terms
    if (sootModel.nucleationMechanism == nucleationMech::PAH) {      // do PAH condensation if PAH nucleation is selected
        for (size_t i = 1; i < state.sootVar.size(); i++) {                                         // M0 = 0.0 for condensation by definition
            for (size_t j = 0; j < abscissas.size(); j++)
                condensationSourceM.at(i) += sootChemistry.coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(j)) * pow(abscissas.at(j), i - 1) * weights.at(j);
            condensationSourceM.at(i) *= state.getDimer() * state.getMDimer() * (double) i;
        }
    }

    if (out) {
        *out << "PAH condensation source terms (" << condensationSourceM.size() << ")" << endl;
        for (size_t i = 0; i < condensationSourceM.size(); i++)
            *out << i << ": " << condensationSourceM.at(i) << endl;
        *out << endl;
    }

    //---------- growth terms

    vector<double> growthSourceM(state.sootVar.size(), 0);                                      // growth source terms for moments
    const double Acoef = M_PI * pow(abs(6 / M_PI / rhoSoot), 2.0 / 3);   // Acoef (=) kmol^2/3 / kg^2/3
    for (size_t i = 1; i < state.sootVar.size(); i++)                                                   // M0 = 0.0 for growth by definition
        growthSourceM.at(i) = kGrw * Acoef * (double) i * Mk((double) i - 1.0 / 3, weights, abscissas);                  // kg^k/m3*s

    if (out) {
        *out << "growth source terms for moments (" << growthSourceM.size() << ")" << endl;
        for (size_t i = 0; i < growthSourceM.size(); i++)
            *out << i << ": " << growthSourceM.at(i) << endl;
        *out << endl;
    }

    //---------- oxidation terms

    vector<double> oxidationSourceM(state.sootVar.size(), 0);                                   // oxidation source terms
    for (size_t i = 1; i < state.sootVar.size(); i++)                                                   // M0 = 0.0 for oxidation by definition
        oxidationSourceM.at(i) = -kOxi * Acoef * (double) i * Mk((double) i - 1.0 / 3, weights, abscissas);              // kg^k/m3*s

    if (out) {
        *out << "oxidation source terms (" << oxidationSourceM.size() << ")" << endl;
        for (size_t i = 0; i < oxidationSourceM.size(); i++)
            *out << i << ": " << oxidationSourceM.at(i) << endl;
        *out << endl;
    }

    //---------- coagulation terms

    vector<double> coagulationSourceM(state.sootVar.size(), 0);                                 // coagulation source terms: initialize to zero!

    // there is a different case for the first moment
    // the second moment does not need calculation
    // the other moments are handled by the second loop
    for (size_t i = 0; i < abscissas.size(); i++) {
    	if (i != 0) {
    		for (size_t j = 0; j < i; j++)
			    coagulationSourceM.at(0) += sootModel.coa->getCoagulationRate(state, abscissas.at(i), abscissas.at(j)) * weights.at(i) * weights.at(j) * -1;
    	}
	    coagulationSourceM.at(0) += sootModel.coa->getCoagulationRate(state, abscissas.at(i), abscissas.at(i)) * weights.at(i) * weights.at(i) * -0.5;
    }
    for (size_t i = 2; i < state.sootVar.size(); i++) {
    	for (size_t j = 0; j < abscissas.size(); j++) {
    		if (j != 0) {
    			for (size_t k = 0; k < j; k++)
				    coagulationSourceM.at(i) += sootModel.coa->getCoagulationRate(state, abscissas.at(j), abscissas.at(k)) * weights.at(j) * weights.at(k) * (i == 0 ? -1 : (pow(abscissas.at(j) + abscissas.at(k), i)) - pow(abscissas.at(j), i) - pow(abscissas.at(k), i));
    		}
		    coagulationSourceM.at(i) += sootModel.coa->getCoagulationRate(state, abscissas.at(j), abscissas.at(j)) * weights.at(j) * weights.at(j) * (i == 0 ? -0.5 : pow(abscissas.at(j), i) * (pow(2, i - 1) - 1));
    	}
    }

    if (out) {
        *out << "coagulation source terms (" << coagulationSourceM.size() << ")" << endl;
        for (size_t i = 0; i < coagulationSourceM.size(); i++)
            *out << i << ": " << coagulationSourceM.at(i) << endl;
        *out << endl;
    }

    //---------- combinine to make source terms

    vector<double> sootSourceTerms(state.sootVar.size(), 0);

    for (size_t i = 0; i < state.sootVar.size(); i++)
        sootSourceTerms.at(i) = (nucleationSourceM.at(i) + condensationSourceM.at(i) + growthSourceM.at(i) + oxidationSourceM.at(i) + coagulationSourceM.at(i)) / state.getRhoGas();

    if (out) {
        *out << "Soot Source Terms (" << sootSourceTerms.size() << ")" << endl;
        for (size_t i = 0; i < sootSourceTerms.size(); i++)
            *out << i << ": " << sootSourceTerms.at(i) << endl;
        *out << endl;
    }

    //---------- get gas source terms

    map<gasSp, double> gasSourceTerms = SootChemistry::getGasSourceTerms(state, massRateRatios, nucleationSourceM.at(1), growthSourceM.at(1), oxidationSourceM.at(1), 0);
    map<size_t, double> PAHSourceTerms = SootChemistry::getPAHSourceTerms(state, massRateRatios, nucleationSourceM.at(1), 0, oxidationSourceM.at(1), 0);

    if (out) {
        *out << "Gas Source Terms (" << gasSourceTerms.size() << ")" << endl;
        for (const auto& [g, t] : gasSourceTerms)
            *out << (int) g << ": " << t << endl;
        *out << "PAH Source Terms (" << PAHSourceTerms.size() << ")" << endl;
        for (const auto& [s, t] : PAHSourceTerms)
            *out << s << ": " << t << endl;
        *out << endl;
    }

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
////////////////////////////////////////////////////////////////////////////////
/*! Wheeler algorithm for computing weights and abscissas from moments
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
void psdModel_QMOM::wheeler(const vector<double>& m, size_t N, vector<double>& w, vector<double>& x)
{
	vector<vector<double>> sigma(N + 1, vector<double>(N * 2, 0));
	vector<double> a(N, 0);
	vector<double> b(N, 0);
	vector<double> eval(N);
	vector<double> evec(N * N);
	vector<double> j_diag(N);
	vector<double> j_ldiag(N);

	for (size_t i = 0; i <= N * 2 - 1; i++)
		sigma.at(1).at(i) = m.at(i);

	a.at(0) = m.at(1) / m.at(0);

	for (size_t i = 1; i < N; i++) {
		for (size_t j = i; j < N * 2 - i; j++)
			sigma.at(i + 1).at(j) = sigma.at(i).at(j + 1) - a.at(i - 1) * sigma.at(i).at(j) - b.at(i - 1) * sigma.at(i - 1).at(j);
		a.at(i) = -sigma.at(i).at(i) / sigma.at(i).at(i - 1) + sigma.at(i + 1).at(i + 1) / sigma.at(i + 1).at(i);
		b.at(i) = sigma.at(i + 1).at(i) / sigma.at(i).at(i - 1);
	}

	j_diag = a;
	for (size_t i = 1; i < N; i++)
		j_ldiag.at(i) = -sqrt(abs(b.at(i)));

	for (size_t i = 0; i < N; i++)
		evec.at(i + N * i) = 1;

//    int flag = tql2(N, &j_diag.at(0), &j_ldiag.at(0), &evec.at(0));       // for eispack

	//char VorN = 'V';
	//vector<double> work(2*N-2);
	//int info;
	//dstev_( &VorN, &N, &j_diag.at(0), &j_ldiag.at(1), &evec.at(0), &N, &work.at(0), &info);

	x = j_diag;      // j_diag are now the vector of eigenvalues.

	for (size_t i = 0; i < N; i++)
		w.at(i) = pow(evec.at(0 + i * N), 2) * m.at(0);
}
////////////////////////////////////////////////////////////////////////////////
/*! getWtsAbs function
 *
 *      Calculates weights and abscissas from moments using PD algorithm or
 *      wheeler algorithm.
 *
 *      @param M        \input  vector of moments
 *      @param wts      \input  weights
 *      @param absc     \input  abscissas
 *
 *      Notes:
 *      - Use wheeler over pdalg whenever possible.
 *      - wts and abs DO NOT change size; if we downselect to a smaller number
 *      of moments, the extra values are set at and stay zero
 *      - using w_temp and a_temp means we don't have to resize wts and absc,
 *      which is more convenient when wts and absc are used to reconstitute
 *      moment source terms.
 */
void psdModel_QMOM::getWtsAbs(const vector<double>& M, vector<double>& weights, vector<double>& abscissas)
{
	size_t N = M.size();              // local nMom; may change with moment deselection

	for (double num : M) {                // if any moments are zero, return with zero wts and absc
		if (num <= 0)
			return;
	}

	bool negs;                          // flag for downselecting if there are negative wts/abs

	vector<double> w_temp(N / 2, 0);
	vector<double> a_temp(N / 2, 0);

	do {                                        // downselection loop

		negs = false;                           // reset flag

		for (size_t i = 0; i < N / 2; i++) {             // reinitialize weights and abscissas with zeros
			w_temp.at(i) = 0;
			a_temp.at(i) = 0;
		}

		if (N == 2) {                           // in 2 moment case, return monodisperse output
			weights.at(0) = M.at(0);
			abscissas.at(0) = M.at(1) / M.at(0);
			return;
		}

		//pdAlg(N,N/2,ymom,wts,absc);           // PD algorithm
		wheeler(M, N / 2, w_temp, a_temp);        // wheeler algorithm

		for (size_t i = 0; i < N / 2; i++) {
			if (w_temp.at(i) < 0 || a_temp.at(i) < 0 || a_temp.at(i) > 1)
				negs = true;
		}

		if (negs) {                     // if we found negative values
			N = N - 2;                          // downselect to two fewer moments and try again
			w_temp.resize(N / 2);
			a_temp.resize(N / 2);
		}

	}
	while (negs);                     // end of downselection loop

	for (size_t i = 0; i < w_temp.size(); i++) {   // assign temporary variables to output
		weights.at(i) = w_temp.at(i);
		abscissas.at(i) = a_temp.at(i);
	}
}
////////////////////////////////////////////////////////////////////////////////
/** Mk function
*
*  calculates fractional moments from weights and abscissas.
*
*  @param exp  \input  fractional moment to compute, corresponds to exponent
*  @param wts  \input  weights
*  @param absc \input  abscissas
*  @param Mk   \output fractional moment value
*/
double psdModel_QMOM::Mk(double exp, const vector<double>& wts, const vector<double>& absc)
{
	double Mk = 0;

	for (size_t i = 0; i < wts.size() / 2; i++) {
		if (wts.at(i) == 0 || absc.at(i) == 0)
			return 0;
		else
			Mk += wts.at(i) * pow(absc.at(i), exp);
	}

	return Mk;
}
void psdModel_QMOM::checkState(const state& state) const {
    if (state.sootVar.size() < 2)
        throw runtime_error("QMOM soot model requries 2, 4 or 6 moments");
    if (state.sootVar.size() % 2 == 1)
        throw runtime_error("QMOM soot model requires 2, 4 or 6 moments");
    if (state.sootVar.size() > 6)
        cerr << "QMOM soot model requires 2, 4 or 6 moments, got " << state.sootVar.size() << endl;
}
