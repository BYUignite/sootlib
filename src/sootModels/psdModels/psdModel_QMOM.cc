#include "psdModel_QMOM.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

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

void psdModel_QMOM::getSourceTermsImplementation(state& state, std::ostream* out) const {

    if (out) {
        *out << " === [SootModel QMOM] ===" << endl;
        *out << endl;
    }

    //---------- get weights and abscissas

    vector<double> wts = {0};
    vector<double> absc = {0};

    // moment downselection and wheeler algorithm inversion applied here
    getWtsAbs(state.sootVar, wts, absc);

    for (size_t i = 0; i < wts.size(); i++) {
        if (wts.at(i) < 0  ) { wts.at(i) = 0;  }
        if (absc.at(i) < 0)  { absc.at(i) = 0; }
    }

    //---------- get chemical rates

    double jNuc = nuc->getNucleationSootRate(state, absc, wts);
    double kGrw = grw->getGrowthSootRate(state);
    double kOxi = oxi->getOxidationSootRate(state);

    //---------- nucleation terms

    vector<double> nucSrcM(nMom, 0.);
    const double mNuc = state.cMin * gasSpMW.at(gasSp::C) / Na;      // mass of a nucleated particle
    for (size_t i = 0; i < nMom; i++)
        nucSrcM.at(i) = pow(mNuc, i) * jNuc;                            // Nuc_rate = m_nuc^r * jNuc

    //---------- PAH condensation terms

    vector<double> cndSrcM(nMom, 0);
    if (nucleationMechanism == nucleationMech::PAH) {
        for (size_t i = 1; i < nMom; i++) {                             // M0 = 0.0 for condensation by definition
            for (size_t j = 0; j < absc.size(); j++)
                cndSrcM.at(i) += coa->getCoagulationSootRate(state, nuc->DIMER.mDimer, absc.at(j)) * pow(absc.at(j), i - 1) * wts.at(j);
            cndSrcM.at(i) *= nuc->DIMER.nDimer * nuc->DIMER.mDimer * i;
        }
    }

    //---------- growth terms

    vector<double> grwSrcM(nMom, 0);
    const double Acoef = M_PI * pow(abs(6 / M_PI / rhoSoot), 2.0 / 3);      // Acoef (=) kmol^2/3 / kg^2/3
    for (size_t i = 1; i < nMom; i++)                                                // M0 = 0.0 for growth by definition
        grwSrcM.at(i) = kGrw * Acoef * i * Mk(i - 1.0 / 3, wts, absc);          // kg^k/m3*s

    //---------- oxidation terms

    vector<double> oxiSrcM(nMom, 0);
    for (size_t i = 1; i < nMom; i++)                                                // M0 = 0.0 for oxidation by definition
        oxiSrcM.at(i) = -kOxi * Acoef * i * Mk(i - 1.0 / 3, wts, absc);         // kg^k/m3*s

    //---------- coagulation terms

    vector<double> coaSrcM(nMom, 0);

    for(int k=0; k < nMom; k++) {

        // off-diagonal terms (looping half of them) with *2 incorporated
        for(int ii=1; ii < absc.size(); ii++)
            for(int j=0; j<ii; j++)
                coaSrcM[k] += coa->getCoagulationSootRate(state, absc[ii], absc[j]) * wts[ii] * wts[j] *
                              (k == 0 ? -1.0 : (pow(absc[ii] + absc[j], k)) - pow(absc[ii], k) - pow(absc[j], k) );      // M0 special case

        // diagonal terms
        for(int ii=0; ii < absc.size(); ii++)
            coaSrcM[k] += coa->getCoagulationSootRate(state, absc[ii], absc[ii]) * wts[ii] * wts[ii] *
                          (k == 0 ? -0.5 : pow(absc[ii], k) * (pow(2, k - 1) - 1) );                                  // M0 special case
    }

    coaSrcM.at(1) = 0.0;    // M1 = 0.0 for coagulation by definition

    //---------- combine to make soot source terms

    for (size_t i = 0; i < nMom; i++)
        sourceTerms->sootSourceTerms.at(i) = (nucSrcM.at(i) + cndSrcM.at(i) + grwSrcM.at(i) + oxiSrcM.at(i) + coaSrcM.at(i)) / state.rhoGas;
    
    //---------- get gas source terms

    map<gasSp, double> nucGasSrc = nuc->getNucleationGasRates(state, nucSrcM[1]).gasSourceTerms;
    map<gasSp, double> grwGasSrc = grw->getGrowthGasRates(state, grwSrcM[1]).gasSourceTerms;
    map<gasSp, double> oxiGasSrc = oxi->getOxidationGasRates(state, oxiSrcM[1]).gasSourceTerms;
    // coagulation does not contribute to gas sources/sinks

    for (auto const& x : sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        if (sp != gasSp::C)
            sourceTerms->gasSourceTerms.at(sp) = nucGasSrc.at(sp) + grwGasSrc.at(sp) + oxiGasSrc.at(sp);
    }

}

////////////////////////////////////////////////////////////////////////////////

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

void psdModel_QMOM::getWtsAbs(const vector<double>& M, vector<double>& weights, vector<double>& abscissas)
{
	size_t N = M.size();        // local nMom; may change with moment downselection

	for (double num : M) {      // if any moments are zero,
		if (num <= 0)           // return with zero wts and abscs
			return;
	}

	bool bad_values;            // downselection flag

	vector<double> w_temp(N / 2, 0);
	vector<double> a_temp(N / 2, 0);

    // downselection loop
	do {

	    // reset flag
		bad_values = false;                                   

		// reinitialize weights and abscs with zeros
		for (size_t i = 0; i < N / 2; i++) {            
			w_temp.at(i) = 0;
			a_temp.at(i) = 0;
		}

		// in 2 moment case, return MONO output
		if (N == 2) {                                   
			weights.at(0) = M.at(0);
			abscissas.at(0) = M.at(1) / M.at(0);
			return;
		}

		// wheeler algorithm for moment inversion
		wheeler(M, N / 2, w_temp, a_temp);      

		// check for bad values
		for (size_t i = 0; i < N / 2; i++) {              
			if (w_temp.at(i) < 0 || a_temp.at(i) < 0)     // check for negative values
				bad_values = true;
			if (w_temp.at(i) > 1)                         // check for weights > 1
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
		weights.at(i) = w_temp.at(i);
		abscissas.at(i) = a_temp.at(i);
	}
}

////////////////////////////////////////////////////////////////////////////////

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