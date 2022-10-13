#include "sootModels/psdModels/psdModel_MOMIC.h"
#include "sootModels/psdModels/binomial.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

 psdModel_MOMIC::psdModel_MOMIC(sourceTermStruct* sourceTerms, int nsoot_, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C)
         : psdModel(sourceTerms, nsoot_, N, G, X, C) {

     if (nsoot_ < 1)
         throw runtime_error("Invalid number of soot moments requested");

     nsoot = nsoot_;

     // initialize sourceTerms soot variable
     sourceTerms->sootSourceTerms.resize(nsoot, 0);

    mechType = psdMech::MOMIC;
}

////////////////////////////////////////////////////////////////////////////////

void psdModel_MOMIC::setSourceTerms(state& state, sourceTermStruct *sourceTerms) const {

    //---------- get moment values
    vector<double> Mtemp(nsoot,0);
    for (int i=0; i<nsoot; i++)
        Mtemp.at(i) = state.sootVar.at(i);

    downselectIfNeeded(Mtemp);
    int N = Mtemp.size();

    //---------- get chemical rates

    double Jnuc = nuc->getNucleationSootRate(state);
    double Kgrw = grw->getGrowthSootRate(state);
    double Koxi = oxi->getOxidationSootRate(state);

    //---------- nucleation terms

    vector<double> Mnuc(N, 0);

    double m_nuc = state.cMin * gasSpMW[(int)gasSp::C] / Na;
    for (size_t i = 0; i < N; i++)
        Mnuc.at(i) = pow(m_nuc, i) * Jnuc;

    //---------- PAH condensation terms

    vector<double> Mcnd(N, 0);

    if (nuc->mechType == nucleationMech::PAH) {
        for (size_t i = 1; i < N; i++)
            Mcnd.at(i) = MOMICCoagulationRate(state, (int) i, Mtemp) * nuc->DIMER.nDimer * nuc->DIMER.mDimer * i;
    }

    //---------- growth terms

    vector<double> Mgrw(N, 0);

    const double Acoef = M_PI * pow(abs( 6 / M_PI / rhoSoot), 2.0 / 3);
    for (size_t i = 1; i < N; i++)
        Mgrw.at(i) = Kgrw * Acoef * i * MOMIC(i - 1.0 / 3, Mtemp);

    //---------- oxidation terms

    vector<double> Moxi(N, 0);

    for (size_t i = 1; i < N; i++)
        Moxi.at(i) = Koxi * Acoef *  i * MOMIC(i - 1.0 / 3, Mtemp);

    //---------- coagulation terms

    vector<double> Mcoa(N, 0);

    if (coa->mechType != coagulationMech::NONE) {
        for (size_t i = 0; i < N; i++)
            Mcoa.at(i) = MOMICCoagulationRate(state, i, Mtemp);
    }

    //---------- combine to make soot source terms

    for (size_t i = 0; i < N; i++)
        sourceTerms->sootSourceTerms.at(i) = (Mnuc.at(i) + Mcnd.at(i) + Mgrw.at(i) + Moxi.at(i) + Mcoa.at(i));

    //---------- get gas source terms

    // dummy variables
    map<gasSp, double> nucGasSrc = {{gasSp::C2H2,0},
                                    {gasSp::O,   0},
                                    {gasSp::O2,  0},
                                    {gasSp::H,   0},
                                    {gasSp::H2,  0},
                                    {gasSp::OH,  0},
                                    {gasSp::H2O, 0},
                                    {gasSp::CO,  0},
                                    {gasSp::C,   0},
                                    {gasSp::C6H6,0}};

    map<gasSp, double> grwGasSrc= {{gasSp::C2H2,0},
                                   {gasSp::O,   0},
                                   {gasSp::O2,  0},
                                   {gasSp::H,   0},
                                   {gasSp::H2,  0},
                                   {gasSp::OH,  0},
                                   {gasSp::H2O, 0},
                                   {gasSp::CO,  0},
                                   {gasSp::C,   0},
                                   {gasSp::C6H6,0}};

    map<gasSp, double> oxiGasSrc= {{gasSp::C2H2,0},
                                   {gasSp::O,   0},
                                   {gasSp::O2,  0},
                                   {gasSp::H,   0},
                                   {gasSp::H2,  0},
                                   {gasSp::OH,  0},
                                   {gasSp::H2O, 0},
                                   {gasSp::CO,  0},
                                   {gasSp::C,   0},
                                   {gasSp::C6H6,0}};
    // coagulation does not contribute to gas sources/sinks

    for (auto const& x : sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        if (sp != gasSp::C) {
            nucGasSrc.at(sp) = nuc->getNucleationGasRates(state, Mnuc[1]).gasSourceTerms.at(sp);
            grwGasSrc.at(sp) = grw->getGrowthGasRates(state, Mgrw[1]).gasSourceTerms.at(sp);
            oxiGasSrc.at(sp) = oxi->getOxidationGasRates(state, Moxi[1]).gasSourceTerms.at(sp);
            sourceTerms->gasSourceTerms.at(sp) = nucGasSrc.at(sp) + grwGasSrc.at(sp) + oxiGasSrc.at(sp);
        }
    }

	//---------- get PAH source terms

    if(nuc->mechType == nucleationMech::PAH)
        for (int sp=0; sp<(int)pahSp::size; sp++)
            sourceTerms->pahSourceTerms[sp] = nuc->getNucleationPahRates(state).pahSourceTerms[sp];

}

////////////////////////////////////////////////////////////////////////////////

void psdModel_MOMIC::downselectIfNeeded(vector<double> &M) const {

    // lognormal distribution constants

    const double sigL = 3.0;
    const double mavg = 1.0E-21;

    // CHECK: M0 <= 0.0

     if (M[0] <= 0)
		return;

    // CHECK: M1 <= 0.0

    if (M[1] <= 0.0)
        M[1] = M[0] * mavg * exp(0.5 * pow(sigL,2.0));     // estimate an M1 value based on M0 and lognormal distribution

    // CHECK: M2 <= 0.0

    if (M[2] <= 0.0)
        M[2] = M[0] * pow(mavg,2) * exp(0.5 * 4 * pow(sigL,2.0));     // estimate an M2 value based on M0 and lognormal distribution

    // CHECK: all remaining moments <= 0.0

	size_t N = M.size();
	bool zeros = false;

	do {

	    zeros = false;                                      // reset flag

        for (int i=0; i<N; i++)
            if (M[i] <= 0.0) { zeros = true; N = N - 1; }   // if value <= 0.0 found, throw flag and downselect by one

	} while (N > 3 && zeros);                               // will not downselect below 3 moments

    M.resize(N);

	return;
}

////////////////////////////////////////////////////////////////////////////////


double  psdModel_MOMIC::f_grid(int x, int y, const vector<double>& M) {

	// repeated values of MOMIC calculation
	const double M_Xn12  = MOMIC(x - 1.0  / 2, M);
	const double M_Yp16  = MOMIC(y + 1.0  / 6, M);
	const double M_Xn16  = MOMIC(x - 1.0  / 6, M);
	const double M_Yn16  = MOMIC(y - 1.0  / 6, M);
	const double M_Xp16  = MOMIC(x + 1.0  / 6, M);
	const double M_Yn12  = MOMIC(y - 1.0  / 2, M);
	const double M_Yp76  = MOMIC(y + 7.0  / 6, M);
	const double M_Yp56  = MOMIC(y + 5.0  / 6, M);
	const double M_Yp12  = MOMIC(y + 1.0  / 2, M);
	const double M_Xp12  = MOMIC(x + 1.0  / 2, M);
	const double M_Xp56  = MOMIC(x + 5.0  / 6, M);
	const double M_Xp76  = MOMIC(x + 7.0  / 6, M);
	const double M_Yp136 = MOMIC(y + 13.0 / 6, M);
	const double M_Yp116 = MOMIC(y + 11.0 / 6, M);
	const double M_Yp32  = MOMIC(y + 3.0  / 2, M);
	const double M_Xp32  = MOMIC(x + 3.0  / 2, M);
	const double M_Xp116 = MOMIC(x + 11.0 / 6, M);
	const double M_Xp136 = MOMIC(x + 13.0 / 6, M);
    const double M_Yp196 = MOMIC(y + 19.0 / 6, M);
    const double M_Yp176 = MOMIC(y + 17.0 / 6, M);
    const double M_Yp52  = MOMIC(y + 5.0  / 2, M);
    const double M_Xp52  = MOMIC(x + 5.0  / 2, M);
    const double M_Xp176 = MOMIC(x + 17.0 / 6, M);
    const double M_Xp196 = MOMIC(x + 19.0 / 6, M);

	const double f1_0 = M_Xn12 * M_Yp16 + 2 * M_Xn16 * M_Yn16 + M_Xp16 * M_Yn12;
	const double f1_1 = M_Xn12 * M_Yp76 + 2 * M_Xn16 * M_Yp56 + M_Xp16 * M_Yp12 +
                        M_Xp12 * M_Yp16 + 2 * M_Xp56 * M_Yn16 + M_Xp76 * M_Yn12;

	vector<double> temp_x;
	vector<double> temp_y;
	double value;

	if (y >= 4) {
		temp_x = {0, 1};
		temp_y = {log10(f1_0), log10(f1_1)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);
		return pow(10, value);
	}

	double f1_2 = M_Xn12 * M_Yp136 + 2 * M_Xn16 * M_Yp116 + M_Xp16 * M_Yp32 + 2 * M_Xp12  * M_Yp76 +
              4 * M_Xp56 * M_Yp56  + 2 * M_Xp76 * M_Yp12  + M_Xp32 * M_Yp16 + 2 * M_Xp116 * M_Yn16 + M_Xp136 * M_Yn12;

	if (y >= 3) {
		temp_x = {0, 1, 2};
		temp_y = {log10(f1_0), log10(f1_1), log10(f1_2)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);

		return pow(10, value);
	}

    double f1_3 = M_Xn12 * M_Yp196 + 2 * M_Xn16 * M_Yp176 +    M_Xp16 * M_Yp52 + 3 * M_Xp12 * M_Yp136 +
              6 * M_Xp56 * M_Yp116 + 3 * M_Xp76 * M_Yp32 + 3 * M_Xp32 * M_Yp76 + 6 * M_Xp116 * M_Yp56 +
              3 * M_Xp136 * M_Yp12 +     M_Xp52 * M_Yp16 + 2 * M_Xp176 * M_Yn16 +    M_Xp196 * M_Yn12;

	temp_x = {0, 1, 2, 3};
	temp_y = {log10(f1_0), log10(f1_1), log10(f1_2), log10(f1_3)};

	value = lagrangeInterp(1.0 / 2, temp_x, temp_y);

	return pow(10, value);
}

////////////////////////////////////////////////////////////////////////////////

double psdModel_MOMIC::MOMICCoagulationRate(const state& state, size_t r, vector<double>& M){

     if (M[0] <= 0.0)
         return 0;

    // M1 = 0.0 for coagulation by definition
	if (r == 1)
		return 0;

    //---------- Knudsen number calculation

	const double mu_1 = M[1] / M[2];
	const double d_g = pow(6 * kb * state.T / state.P / M_PI, 1.0 / 3);
	const double d_p = pow(6 * mu_1 / rhoSoot / M_PI, 1.0 / 3);
	const double lambda_g = kb * state.T / (pow(2, 0.5) * M_PI * pow(d_g, 2) * state.P);
	const double Kn = lambda_g / d_p;

    //---------- continuum regime

    double Rate_C;

    const double K_C = 2 * kb * state.T / (3 * state.muGas);
    const double K_Cprime = 1.257 * lambda_g * pow(M_PI * rhoSoot / 6, 1.0 / 3);

	if (r == 0) {
		Rate_C = -K_C * (pow(M[0], 2) + MOMIC(1.0 / 3, M) * MOMIC(-1.0 / 3, M) +
                         K_Cprime * (3 * MOMIC(-1.0 / 3, M) * M[0] +
                                     MOMIC( 2.0 / 3, M) * MOMIC(1.0 / 3, M) ) );
	}
	else {
		Rate_C = 0;
		for (size_t k = 0; k < r; k++) {
			if (k <= r - k)
				Rate_C += binomial_coefficient(r, k) * (2 * M[k] * M[r - k] +
                                                        MOMIC(k + 1.0 / 3, M) * MOMIC(r - k - 1.0 / 3, M) +
                                                        MOMIC(k - 1.0 / 3, M) * MOMIC(r - k + 1.0 / 3, M) +
                          2 * K_Cprime * (2 * MOMIC(k - 1.0 / 3, M) * M[r - k] +
                                          M[k] * MOMIC(r - k - 1.0 / 3, M) +
                                          MOMIC(k - 2.0 / 3, M) * MOMIC(r - k + 1.0 / 3, M) ) );
		}
		Rate_C *= 0.5 * K_C;
	}

    //---------- free-molecular regime

	double Rate_F;

	const double K_f = 2.2 * pow(3 / (4 * M_PI * rhoSoot), 2.0 / 3) * pow(8 * M_PI * kb * state.T, 1.0 / 2);

	if (r == 0) {
		Rate_F = -0.5 * K_f * f_grid(0, 0, M);
	}
	else {
		Rate_F = 0;
		for (size_t k = 1; k < r; k++) {
			if (k <= r - k)
				Rate_F += binomial_coefficient(r, k) * f_grid(k, r - k, M);
		}
		Rate_F *= 0.5 * K_f;
	}

    //---------- return weighted average

	return Rate_F / (1.0 + 1 / Kn) + Rate_C / (1 + Kn);

}

////////////////////////////////////////////////////////////////////////////////

double psdModel_MOMIC::lagrangeInterp(double x_i, const vector<double>& x, const vector<double>& y)
{
	double y_i = 0;

	double L;
	for (size_t j = 0; j < x.size(); j++) {
		L = 1;
		for (size_t m = 0; m < x.size(); m++) {
			if (m != j) {
				L *= (x_i - x.at(m)) / (x.at(j) - x.at(m));
			}
		}
		y_i += y.at(j) * L;
	}

	return y_i;
}

////////////////////////////////////////////////////////////////////////////////

double psdModel_MOMIC::MOMIC(double p, const vector<double>& M) {

    if (M.at(0) <= 0)
        return 0;

	if (p == 0)
		return M.at(0);

	size_t size = M.size();
	if (p < 0 && M.size() != 2)
		size = 3;

	vector<double> log_mu(size, 0);
	vector<double> x(size, 0);

	for (size_t i = 0; i < size; i++) {
		log_mu.at(i) = log10(M.at(i) / M.at(0));
		x.at(i) =  i;
	}

	const double log_mu_p = lagrangeInterp(p, x, log_mu);

	return pow(10, log_mu_p) * M.at(0);
}
