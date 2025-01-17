#include "sootModel_QMOM.h"
#include "binomial.h"
#include <algorithm>         // fill
#include <cmath>             // isfinite (not nan or inf)

using namespace std;
using namespace soot;

//------ LApack function
extern "C" void dstev_(char *JOBZ, int *N, double *D, double *E, double *Z, int *LDZ, double *WORK, int *INFO);

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking pointers to chemistry models as input.
/// User creates these pointers nominally by "new-ing" them.
///
/// @param nsoot_ \input number of soot moments (even number)
/// @param nucl_  \input pointer to nucleation model.
/// @param grow_  \input pointer to growth model.
/// @param oxid_  \input pointer to oxidation model.
/// @param coag_  \input pointer to coagulation model.
///
////////////////////////////////////////////////////////////////////////////////

sootModel_QMOM::sootModel_QMOM(size_t            nsoot_,
                               nucleationModel  *nucl_,
                               growthModel      *grow_,
                               oxidationModel   *oxid_,
                               coagulationModel *coag_,
                               size_t            Ntar_,
                               tarModel         *tar_) :
        sootModel(nsoot_, nucl_, grow_, oxid_, coag_, Ntar_, tar_) {

    if (nsoot_%2 == 1 || nsoot_ < 1)
        throw runtime_error("Invalid number of soot moments requested: must be even number");

    if (nsoot_ > 6)
        cerr << "Warning: QMOM inversion algorithm may behave unpredictably with "
                "8+ soot moments. Proceed with caution." << endl;

    psdMechType = psdMech::QMOM;

}

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking enumerations names as input.
/// Chemistry pointers are created (new-ed) here based on those enumerations.
///
/// @param nsoot_ \input number of soot moments (even number)
/// @param Nmech  \input one of enum class nucleationMech in sootDefs.h
/// @param Gmech  \input one of enum class growthMech in sootDefs.h
/// @param Omech  \input one of enum class oxidationMech in sootDefs.h
/// @param Cmech  \input one of enum class coagulationMech in sootDefs.h
///
////////////////////////////////////////////////////////////////////////////////

sootModel_QMOM::sootModel_QMOM(size_t          nsoot_,
                               nucleationMech  Nmech,
                               growthMech      Gmech,
                               oxidationMech   Omech,
                               coagulationMech Cmech,
                               size_t          Ntar_,
                               tarMech         Tmech) :
        sootModel(nsoot_, Nmech, Gmech, Omech, Cmech, Ntar_, Tmech) {

    if (nsoot_%2 == 1 || nsoot_ < 1)
        throw runtime_error("Invalid number of soot moments requested: must be even number");

    if (nsoot_ > 6)
        cerr << "Warning: QMOM inversion algorithm may behave unpredictably with "
                "8+ soot moments. Proceed with caution." << endl;

    psdMechType = psdMech::QMOM;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Primary user interface.
/// 
/// @param state       \input  gas and soot state, set by user.
///
/// sets sources.sootSources vector
/// sets sources.gasSources vector
/// sets sources.pahSources vector
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_QMOM::setSourceTerms(state &state) {

    //---------- get weights and abscissas

    getWtsAbs(state.sootVar, state.wts, state.absc);    // moment downselection applied

    //---------- get chemical rates

    double jNuc = nucl->getNucleationSootRate(state);
    double kGrw = grow->getGrowthSootRate(state);
    double kOxi = oxid->getOxidationSootRate(state);

    //---------- nucleation terms

    vector<double> nucSrcM(nsoot, 0.);

    if (nucl->mechType != nucleationMech::NONE) {
        const double mNuc = state.cMin*gasSpMW[(int)gasSp::C]/Na;      // mass of a nucleated particle
        for (size_t i=0; i<nsoot; i++)
            nucSrcM[i] = pow(mNuc, i)*jNuc;                            // Nuc_rate = m_nuc^r * jNuc
    }

    //---------- PAH condensation terms

    vector<double> cndSrcM(nsoot, 0);
    if (nucl->mechType == nucleationMech::PAH) {
        for (size_t k=1; k<nsoot; k++) {                             // loop moments k, skip moment 0
            for (size_t i=0; i<state.absc.size(); i++)               // loop abscissas
                cndSrcM[k] += coag->getCoagulationSootRate(state, nucl->DIMER.mDimer, state.absc[i]) * 
                              state.wts[i] * ((k==1) ? 1.0 : (k==2) ? state.absc[i] : pow(state.absc[i], k-1));
            cndSrcM[k] *= k * nucl->DIMER.nDimer * nucl->DIMER.mDimer;
        }
    }

    //---------- growth terms

    vector<double> grwSrcM(nsoot, 0);

    const double Acoef = M_PI*pow(6. /(M_PI*rhoSoot), twothird);          // Acoef (=) kmol^2/3 / kg^2/3

    if (grow->mechType != growthMech::NONE)
        for (size_t k=1; k<nsoot; k++)                                        // Rate_M0 = 0.0 for growth by definition
            grwSrcM[k] =  kGrw*Acoef*k*Mr(k-onethird, state.wts, state.absc); // kg^k/m3*s

    //---------- oxidation terms

    vector<double> oxiSrcM(nsoot, 0);

    if (oxid->mechType != oxidationMech::NONE)
        for (size_t k=1; k<nsoot; k++)                                        // Rate_M0 = 0.0 for oxidation by definition
            oxiSrcM[k] = -kOxi*Acoef*k*Mr(k-onethird, state.wts, state.absc); // kg^k/m3*s

    //---------- coagulation terms

    vector<double> coaSrcM(nsoot, 0.0);              // init to 0 to handle M1

    if (coag->mechType != coagulationMech::NONE) {

        double s;

        for(int r=0; r<nsoot; r++) {                 // loop all moments r
            if (r==1) continue;                      // rate is zero for r==1

            //------ off-diagonal terms (looping half of them, with *2 incorporated)

            for(int i=1; i<state.absc.size(); i++)
                for(int j=0; j<i; j++) {                  
                    s = (r==0) ? -1.0 : 0.0;
                    for(int k=1; k<=r-1; k++)        // not entered if r==0, then s=-1
                        s += binomial_coefficient(r,k) * pow(state.absc[i],k) * pow(state.absc[j],r-k);
                    coaSrcM[r] += coag->getCoagulationSootRate(state,state.absc[i],state.absc[j]) * state.wts[i]*state.wts[j] * s;
                }

            //------ diagonal terms

            s = (r==0) ? -1.0 : 0.0;
            for(int k=1; k<=r-1; k++)                // not entered if r==0, then s=-1
                s += binomial_coefficient(r,k);
            for(int i=0; i<state.absc.size(); i++) {
                coaSrcM[r] += 0.5*coag->getCoagulationSootRate(state,state.absc[i],state.absc[i]) *state.wts[i]*state.wts[i] * s *
                    ((r==0) ? 1.0 : pow(state.absc[i], r));
            }
        }
    }

    //---------- combine to make soot source terms

    for (size_t i = 0; i < nsoot; i++)
        sources.sootSources[i] = nucSrcM[i] + cndSrcM[i] + grwSrcM[i] + oxiSrcM[i] + coaSrcM[i];  // kg^k/m3*s

    //---------- set gas source terms

    vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

    nucl->getNucleationGasRates(nucSrcM[1], nucl_gasSources);
    grow->getGrowthGasRates(    grwSrcM[1], grow_gasSources);
    oxid->getOxidationGasRates( oxiSrcM[1], oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        sources.gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

    //---------- set PAH source terms

    if(nucl->mechType == nucleationMech::PAH)
        sources.pahSources = nucl->nucleationPahRxnRates;        // includes both nucleation and condensation
}

////////////////////////////////////////////////////////////////////////////////
///
/// Calculates weights and abscissas from moments using wheeler algorithm.
///
/// @param M         \input      vector of moments
/// @param weights   \output     weights
/// @param abscissas \output     abscissas
///
/// NOTE: wts and absc variables DO NOT change size during downselection;
/// instead, the extra values are set to zero. This is more convenient than
/// resizing when wts and absc are used to reconstitute moment source terms.
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_QMOM::getWtsAbs(const vector<double>& M, vector<double>& weights, vector<double>& abscissas) {

    fill(weights.begin(),   weights.end(),   0.0);   // initialize weights and abscissas
    fill(abscissas.begin(), abscissas.end(), 0.0);

    if(M[0] <= 0.0) return;

    //----------

    size_t Nenv = M.size()/2;   // local nsoonsoot; may change with moment downselection

	vector<double> w_temp(Nenv, 0);
	vector<double> a_temp(Nenv, 0);

	bool bad_values;            // downselection flag
	do {                        // downselection loop

		bad_values = false;     // reset flag

		//---- 1 env (2 moment) case, return MONO output
		if (Nenv == 1) {
            //cout << endl << "downselected to mono" << endl;
			w_temp[0] = M[0];
			a_temp[0] = M[1] / M[0];
			break;
		}

		//---- wheeler algorithm for moment inversion
		wheeler(M, Nenv, w_temp, a_temp);

		//---- check for bad values
		for (size_t i=0; i<Nenv; i++) {
            if ( (!isfinite(w_temp[i]) || w_temp[i]<0) ||
                 (!isfinite(a_temp[i]) || a_temp[i]<0) )
				bad_values = true;
		}

		//---- if we find bad values, downselect to 2 fewer moments (1 fewer env) and try again
		if (bad_values) {
            Nenv--;
            w_temp.assign(Nenv, 0.0);       // resizes and assigns 0.0
            a_temp.assign(Nenv, 0.0);
		}

	}
	while (bad_values);

	//---------- assign temporary variables to output
	for (size_t i=0; i<Nenv; i++) {
		weights[i]   = w_temp[i] >= 0 ? w_temp[i] : 0.0;     // these checks should be redundant
		abscissas[i] = a_temp[i] >= 0 ? a_temp[i] : 0.0;
	}
}

////////////////////////////////////////////////////////////////////////////////
///
/// Wheeler algorithm for computing weights and abscissas from moments.
///
/// From Marchisio and Fox (2013) Computational Models for Polydisperse and
/// Multiphase Systems.
/// LApack's dstev function to compute eigenvalues and eigenvectors of symmetrical
/// tridiagonal matrix.
///
/// @param m    \input     vector of moments (size = 2N)
/// @param N    \input     number of quadrature nodes (abscissas)
/// @param w    \output    weights
/// @param x    \output    abscissas
///
////////////////////////////////////////////////////////////////////////////////

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

    //----- compute eigenvalues/eigenvectors (lapack)

    char VorN = 'V';
    vector<double> work(2*N-2);
    int info;
    int NN = int(N);
    dstev_( &VorN, &NN, &j_diag[0], &j_ldiag[1], &evec[0], &NN, &work[0], &info);

    //-----

    x = j_diag;      // j_diag are now the vector of eigenvalues.

    for (size_t i = 0; i < N; i++)
        w[i] = pow(evec[0 + i * N], 2) * m[0];
}

////////////////////////////////////////////////////////////////////////////////
///
/// calculates fractional moments from weights and abscissas.
///
/// @param r        \input      fractional moment to compute; corresponds to exponent
/// @param wts      \input      weights
/// @param absc     \input      abscissas
/// @return Mr
///
////////////////////////////////////////////////////////////////////////////////

double sootModel_QMOM::Mr(double r, const vector<double>& wts, const vector<double>& absc) {
	double Mr = 0;

	for (size_t i=0; i<wts.size(); i++) {
		if (wts[i] <= 0 || absc[i] <= 0)
			return 0;
		else
			Mr += wts[i] * pow(absc[i], r);
	}
	return Mr;
}
