#include "sootModel_MOMIC.h"
#include "binomial.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sootModel_MOMIC::sootModel_MOMIC(size_t            nsoot_,
                                 nucleationModel  *nucl_,
                                 growthModel      *grow_,
                                 oxidationModel   *oxid_,
                                 coagulationModel *coag_) :
        sootModel(nsoot_, nucl_, grow_, oxid_, coag_) {

    if (nsoot_ < 2)
        throw runtime_error("MOMIC requires nsoot>1");
}

////////////////////////////////////////////////////////////////////////////////

sootModel_MOMIC::sootModel_MOMIC(size_t          nsoot_,
                                 nucleationMech  Nmech,
                                 growthMech      Gmech,
                                 oxidationMech   Omech,
                                 coagulationMech Cmech) :
        sootModel(nsoot_, Nmech, Gmech, Omech, Cmech) {

    if (nsoot_ < 2)
        throw runtime_error("MOMIC requires nsoot>1");
}

////////////////////////////////////////////////////////////////////////////////

void sootModel_MOMIC::getSourceTerms(state &state, 
                                     std::vector<double> &sootSources,
                                     std::vector<double> &gasSources,
                                     std::vector<double> &pahSources) const {

    //---------- get moment values

    vector<double> Mtemp(nsoot,0);
    for (size_t i=0; i<nsoot; i++)
        Mtemp[i] = state.sootVar[i];

    downselectIfNeeded(Mtemp);
    int Nsoot = Mtemp.size();

    //---------- get chemical rates

    double Jnuc = nucl->getNucleationSootRate(state);
    double Kgrw = grow->getGrowthSootRate(state);
    double Koxi = oxid->getOxidationSootRate(state);

    //---------- nucleation terms

    vector<double> Mnuc(Nsoot, 0);

    double m_nuc = state.cMin*gasSpMW[(int)gasSp::C]/Na;
    for (size_t i=0; i<Nsoot; i++)
        Mnuc[i] = pow(m_nuc, i)*Jnuc;

    //---------- PAH condensation terms

    vector<double> Mcnd(Nsoot, 0);

    if (nucl->mechType == nucleationMech::PAH) {
        for (size_t i=1; i<Nsoot; i++)
            Mcnd[i] = MOMICCoagulationRate(state, (int) i, Mtemp) * 
                      nucl->DIMER.nDimer * nucl->DIMER.mDimer * i;
    }

    //---------- growth terms

    vector<double> Mgrw(Nsoot, 0);

    const double Acoef = M_PI * pow(6./(M_PI*rhoSoot), twothird);
    for (size_t i=1; i<Nsoot; i++)
        Mgrw[i] = Kgrw*Acoef*i*MOMIC(i - onethird, Mtemp);

    //---------- oxidation terms

    vector<double> Moxi(Nsoot, 0);

    for (size_t i = 1; i < Nsoot; i++)
        Moxi[i] = Koxi*Acoef*i * MOMIC(i - onethird, Mtemp);

    //---------- coagulation terms

    vector<double> Mcoa(Nsoot, 0);

    if (coag->mechType != coagulationMech::NONE) {
        for (size_t i=0; i<Nsoot; i++)
            Mcoa[i] = MOMICCoagulationRate(state, i, Mtemp);
    }

    //---------- combine to make soot source terms

    for (size_t i=0; i<Nsoot; i++)
        sootSources[i] = Mnuc[i] + Mcnd[i] + Mgrw[i] + Moxi[i] + Mcoa[i];

    //---------- set gas source terms

    vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

    nucl->getNucleationGasRates(state, Mnuc[1], nucl_gasSources);
    grow->getGrowthGasRates(    state, Mgrw[1], grow_gasSources);
    oxid->getOxidationGasRates( state, Moxi[1], oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

    //---------- set PAH source terms

    if(nucl->mechType == nucleationMech::PAH)
        pahSources = nucl->nucleationPahRxnRates;

    //todo: what about pah condensation? (here and in other models)

}

////////////////////////////////////////////////////////////////////////////////
/** downselectIfNeeded function
 *
 *      Reduces the number of moments to avoid invalid inversion
 *
 *      @param state      \input      thermodynamic state
 *      @param M          \input      vector of moment values
 *
 */

void sootModel_MOMIC::downselectIfNeeded(vector<double> &M) const {

    //----------- lognormal distribution constants

    const double sigL = 3.0;
    const double mavg = 1.0E-21;

     if (M[0] <= 0)
		return;

    if (M[1] <= 0.0)
        M[1] = M[0] * mavg * exp(0.5 * pow(sigL,2.0));     // estimate an M1 value based on M0 and lognormal distribution

    if (M[2] <= 0.0)
        M[2] = M[0] * pow(mavg,2) * exp(0.5 * 4 * pow(sigL,2.0));     // estimate an M2 value based on M0 and lognormal distribution

    // CHECK: all remaining moments <= 0.0

	size_t Nsoot = M.size();
	bool zeros = false;

	do {
	    zeros = false;                   // reset flag
        for (size_t i=0; i<Nsoot; i++)
            if (M[i] <= 0.0) {           // if value <= 0.0 found, throw flag and downselect by one
                zeros = true; 
                Nsoot = Nsoot - 1; 
            }

	} while (Nsoot>3 && zeros);        // will not downselect below 3 moments

    M.resize(Nsoot);

	return;
}

////////////////////////////////////////////////////////////////////////////////
/** f_grid function
 *
 *      Calculates the grid function described in Frenklach 2002 MOMIC paper
 *      using lagrange interpolation between whole order moments
 *
 *      @param x     \input x grid point
 *      @param y     \input y grid point
 *      @param M     \input vector of whole order moments
 *
 */

double  sootModel_MOMIC::f_grid(int x, int y, const vector<double>& M) {

	// repeated values of MOMIC calculation
	const double M_Xn12  = MOMIC(x - 1.0  / 2.0, M);
	const double M_Yp16  = MOMIC(y + 1.0  / 6.0, M);
	const double M_Xn16  = MOMIC(x - 1.0  / 6.0, M);
	const double M_Yn16  = MOMIC(y - 1.0  / 6.0, M);
	const double M_Xp16  = MOMIC(x + 1.0  / 6.0, M);
	const double M_Yn12  = MOMIC(y - 1.0  / 2.0, M);
	const double M_Yp76  = MOMIC(y + 7.0  / 6.0, M);
	const double M_Yp56  = MOMIC(y + 5.0  / 6.0, M);
	const double M_Yp12  = MOMIC(y + 1.0  / 2.0, M);
	const double M_Xp12  = MOMIC(x + 1.0  / 2.0, M);
	const double M_Xp56  = MOMIC(x + 5.0  / 6.0, M);
	const double M_Xp76  = MOMIC(x + 7.0  / 6.0, M);
	const double M_Yp136 = MOMIC(y + 13.0 / 6.0, M);
	const double M_Yp116 = MOMIC(y + 11.0 / 6.0, M);
	const double M_Yp32  = MOMIC(y + 3.0  / 2.0, M);
	const double M_Xp32  = MOMIC(x + 3.0  / 2.0, M);
	const double M_Xp116 = MOMIC(x + 11.0 / 6.0, M);
	const double M_Xp136 = MOMIC(x + 13.0 / 6.0, M);
    const double M_Yp196 = MOMIC(y + 19.0 / 6.0, M);
    const double M_Yp176 = MOMIC(y + 17.0 / 6.0, M);
    const double M_Yp52  = MOMIC(y + 5.0  / 2.0, M);
    const double M_Xp52  = MOMIC(x + 5.0  / 2.0, M);
    const double M_Xp176 = MOMIC(x + 17.0 / 6.0, M);
    const double M_Xp196 = MOMIC(x + 19.0 / 6.0, M);

	const double f1_0 = M_Xn12 * M_Yp16 + 2 * M_Xn16 * M_Yn16 + M_Xp16 * M_Yn12;
	const double f1_1 = M_Xn12 * M_Yp76 + 2 * M_Xn16 * M_Yp56 + M_Xp16 * M_Yp12 +
                        M_Xp12 * M_Yp16 + 2 * M_Xp56 * M_Yn16 + M_Xp76 * M_Yn12;

	vector<double> temp_x;
	vector<double> temp_y;
	double value;

	if (y >= 4) {
		temp_x = {0., 1.};
		temp_y = {log10(f1_0), log10(f1_1)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);
		return pow(10, value);
	}

	double f1_2 = M_Xn12*M_Yp136 + 2.*M_Xn16*M_Yp116 + M_Xp16*M_Yp32 + 2.*M_Xp12 *M_Yp76 +
                4.*M_Xp56*M_Yp56 + 2.*M_Xp76*M_Yp12  + M_Xp32*M_Yp16 + 2.*M_Xp116*M_Yn16 + M_Xp136*M_Yn12;

	if (y >= 3) {
		temp_x = {0., 1., 2.};
		temp_y = {log10(f1_0), log10(f1_1), log10(f1_2)};

		value = lagrangeInterp(0.5, temp_x, temp_y);

		return pow(10, value);
	}

    double f1_3 = M_Xn12*M_Yp196 + 2.*M_Xn16*M_Yp176 +    M_Xp16*M_Yp52  + 3.*M_Xp12*M_Yp136 +
              6.*M_Xp56*M_Yp116  + 3.*M_Xp76*M_Yp32  + 3.*M_Xp32*M_Yp76  + 6.*M_Xp116*M_Yp56 +
              3.*M_Xp136*M_Yp12  +    M_Xp52*M_Yp16  + 2.*M_Xp176*M_Yn16 +    M_Xp196*M_Yn12;

	temp_x = {0., 1., 2., 3.};
	temp_y = {log10(f1_0), log10(f1_1), log10(f1_2), log10(f1_3)};

	value = lagrangeInterp(0.5, temp_x, temp_y);

	return pow(10., value);
}

////////////////////////////////////////////////////////////////////////////////

double sootModel_MOMIC::MOMICCoagulationRate(const state& state, size_t r, vector<double>& M){

    if (M[0] <= 0.0)
        return 0;

    if (r == 1)    // m1 = 0.0 for coagulation by definition
        return 0;

    //---------- Knudsen number calculation

	const double mu_1 = M[1] / M[2];
	const double d_g = pow(6.*kb*state.T/state.P/M_PI, onethird);
	const double d_p = pow(6.*mu_1/rhoSoot/M_PI, onethird);
	const double lambda_g = kb*state.T/(root2*M_PI*d_g*d_g*state.P);
	const double Kn = lambda_g/d_p;

    //---------- continuum regime

    double Rate_C;

    const double K_C      = 2.*kb*state.T/(3.*state.muGas);
    const double K_Cprime = 1.257*lambda_g*pow(M_PI*rhoSoot/6., onethird);

	if (r == 0)
		Rate_C = -K_C*( M[0]*M[0] + MOMIC(onethird, M)*MOMIC(-onethird, M) +
                        K_Cprime*(3.*MOMIC(-onethird, M)*M[0] +
                                  MOMIC(twothird, M)*MOMIC(onethird, M)) );
	else {
		Rate_C = 0;
		for (size_t k=0; k<r; k++) {
			if (k <= r - k)
				Rate_C += binomial_coefficient(r, k)*( 
                          2.*M[k]*M[r-k] + MOMIC(k + onethird, M) * MOMIC(r - k - onethird, M) +
                          MOMIC(k - onethird, M)*MOMIC(r - k + onethird, M) +
                          2*K_Cprime*(2.*MOMIC(k - onethird, M)*M[r - k] +
                                      M[k]*MOMIC(r - k - onethird, M) +
                                      MOMIC(k - twothird, M) * MOMIC(r - k + onethird, M)) );
		}
		Rate_C *= 0.5*K_C;
	}

    //---------- free-molecular regime

	double Rate_F;

	const double K_f = 2.2*pow(3./(4.*M_PI*rhoSoot), twothird)*sqrt(8.*M_PI*kb*state.T);

	if (r == 0)
		Rate_F = -0.5 * K_f * f_grid(0, 0, M);
	else {
		Rate_F = 0;
		for (size_t k=1; k<r; k++) {
			if (k <= r - k)
				Rate_F += binomial_coefficient(r, k) * f_grid(k, r - k, M);
		}
		Rate_F *= 0.5*K_f;
	}

    //---------- return weighted average

	return Rate_F/(1.0 + 1./Kn) + Rate_C/(1. + Kn);

}

////////////////////////////////////////////////////////////////////////////////
/** lagrangeInterp function
 *
 *      Calculates the Lagrange interpolated value from whole order moments.
 *
 *      @param x_i  \input      x value of desired interpolation
 *      @param x    \input      vector of x values to interpolate amongst
 *      @param y    \input      vector of y values to interpolate amongst
 *      @param y_i  \output     interpolated y value
 *
 */

double sootModel_MOMIC::lagrangeInterp(double x_i, const vector<double>& x, const vector<double>& y)
{
	double y_i = 0;

	double L;
	for (size_t j=0; j<x.size(); j++) {
		L = 1;
		for (size_t m=0; m<x.size(); m++) {
			if (m != j) {
				L *= (x_i - x[m])/(x[j] - x[m]);
			}
		}
		y_i += y[j]*L;
	}

	return y_i;
}
////////////////////////////////////////////////////////////////////////////////
/** MOMIC function
 *
 *      Calculates the desired fractional moment by lagrange interpolation
 *      between whole order moments. Because it uses log moments, it will crash
 *      if any moment is less than or equal to zero.
 *
 *      @param p     \input     desired interpolation value
 *      @param M     \input     vector of whole order moments
 *
 */

double sootModel_MOMIC::MOMIC(double p, const vector<double>& M) {

    if (M[0] <= 0)
        return 0;

	if (p == 0)
		return M[0];

	size_t size = M.size();
	if (p < 0 && M.size() != 2)
		size = 3;

	vector<double> log_mu(size, 0);
	vector<double> x(size, 0);

	for (size_t i = 0; i < size; i++) {
		log_mu[i] = log10(M[i] / M[0]);
		x[i] =  i;
	}

	const double log_mu_p = lagrangeInterp(p, x, log_mu);

	return pow(10, log_mu_p) * M[0];
}
