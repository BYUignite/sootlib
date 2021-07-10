#include "psdModel_MOMIC.h"

using namespace std;
using namespace soot;

 psdModel_MOMIC:: psdModel_MOMIC(size_t n) {
    this->nMom = n;     // TODO error message for unusable values
}

sourceTermStruct  psdModel_MOMIC::getSourceTermsImplementation(state& state, std::ostream* out) const {

    if (out) {
        *out << " === [SootModel MOMIC] ===" << endl;
        *out << endl;
    }

    const size_t N = downselectIfNeeded(state.getMoments());

    if (out) {
        *out << "N: " << N << endl;
        *out << endl;
    }

    MassRateRatios massRateRatios;

    // FIXME it looks like these guys are trying to trigger optional parts of the supporting psdModels with negative values
    // this does not work well with what I have set up now :( there needs to be some explicit arguments for that
    const double Jnuc = sootChemistry.nucleationModel->getNucleationRate(state, {}, {}, massRateRatios);
    const double Kgrw = sootChemistry.growthModel->getGrowthRate(state, massRateRatios);
    const double Koxi = sootChemistry.oxidationModel->getOxidationRate(state, massRateRatios);

    if (out) {
        *out << "Jnuc: " << Jnuc << endl;
        *out << "Kgrw: " << Kgrw << endl;
        *out << "Koxi: " << Koxi << endl;
        *out << endl;
    }

    vector<double> Mnuc(state.getNumMoments(), 0);

    double m_nuc = cMin * MW_C / Na;
    for (size_t i = 0; i < N; i++)
        Mnuc.at(i) = pow(m_nuc, i) * Jnuc;

    if (out) {
        *out << "Mnuc (" << Mnuc.size() << ")" << endl;
        for (size_t i = 0; i < Mnuc.size(); i++)
            *out << i << ": " << Mnuc.at(i) << endl;
        *out << endl;
    }

    vector<double> Mcnd(state.getNumMoments(), 0);

    if (sootChemistry.nucleationModel->getMechanism() == nucleationMech::PAH) {
        for (size_t i = 1; i < N; i++)
            Mcnd.at(i) = MOMICCoagulationRate(state, (int) i) * state.getDimer() * state.getMDimer() * (double) i;
    }

    if (out) {
        *out << "Mcnd (" << Mcnd.size() << ")" << endl;
        for (size_t i = 0; i < Mcnd.size(); i++)
            *out << i << ": " << Mcnd.at(i) << endl;
        *out << endl;
    }

    vector<double> Mgrw(state.getNumMoments(), 0);

    const double Acoef = M_PI * pow(abs(6 / M_PI / state.getRhoSoot()), 2.0 / 3);
    for (size_t i = 1; i < N; i++)
        Mgrw.at(i) = Kgrw * Acoef * (double) i * MOMIC((double) i - 1.0 / 3, state.getMomentsConst());

    if (out) {
        *out << "Mgrw (" << Mgrw.size() << ")" << endl;
        for (size_t i = 0; i < Mgrw.size(); i++)
            *out << i << ": " << Mgrw.at(i) << endl;
        *out << endl;
    }

    vector<double> Moxi(state.getNumMoments(), 0);

    for (size_t i = 1; i < N; i++)
        Moxi.at(i) = Koxi * Acoef * (double) i * MOMIC((double) i - 1.0 / 3, state.getMomentsConst());

    if (out) {
        *out << "Moxi (" << Moxi.size() << ")" << endl;
        for (size_t i = 0; i < Moxi.size(); i++)
            *out << i << ": " << Moxi.at(i) << endl;
        *out << endl;
    }

    vector<double> Mcoa(state.getNumMoments(), 0);

    if (sootChemistry.coagulationModel->getMechanism() != coagulationMech::NONE) {
        for (size_t i = 0; i < N; i++)
            Mcoa.at(i) = MOMICCoagulationRate(state, (int) i);
    }

    if (out) {
        *out << "Mcoa (" << Mcoa.size() << ")" << endl;
        for (size_t i = 0; i < Mcoa.size(); i++)
            *out << i << ": " << Mcoa.at(i) << endl;
        *out << endl;
    }

    vector<double> sootSourceTerms(state.getNumMoments(), 0);
    for (size_t i = 0; i < state.getNumMoments(); i++)
        sootSourceTerms.at(i) = Mnuc.at(i) + Mcnd.at(i) + Mgrw.at(i) + Moxi.at(i) + Mcoa.at(i);

    if (out) {
        *out << "Soot Source Terms (" << sootSourceTerms.size() << ")" << endl;
        for (size_t i = 0; i < sootSourceTerms.size(); i++)
            *out << i << ": " << sootSourceTerms.at(i) << endl;
        *out << endl;
    }

    //---------- get gas source terms
    // FIXME in the old code these were hardcoded to use index 1, but it looks like this depends on the number of moments which supposedly might be only 1
    map<gasSp, double> gasSourceTerms = SootChemistry::getGasSourceTerms(state, massRateRatios, Mnuc.at(1), Mgrw.at(1), Moxi.at(1), Mcnd.at(1));
    map<size_t, double> PAHSourceTerms = SootChemistry::getPAHSourceTerms(state, massRateRatios, Mnuc.at(1), 0, Moxi.at(1), Mcnd.at(1));

    if (out) {
        *out << "Gas Source Terms (" << gasSourceTerms.size() << ")" << endl;
        for (const auto& [g, t] : gasSourceTerms)
            *out << (int) g << ": " << t << endl;
        *out << "PAH Source Terms (" << PAHSourceTerms.size() << ")" << endl;
        for (const auto& [s, t] : PAHSourceTerms)
            *out << s << ": " << t << endl;
        *out << endl;
    }

    return sourceTermStruct(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
size_t  psdModel_MOMIC::downselectIfNeeded(vector<double>& M)
{
	if (M.at(0) <= 0)
		return 0;

	// FIXME I changed this to do a size check nut I'm not sure that's what should happen
	if (M.size() > 1 && M.at(1) <= 0) {
		const double M0 = 1;
		const double sigL = 3;
		const double mavg = 1.0E-21;
		M.at(1) = M0 * mavg * exp(0.5 * pow(sigL, 2));
	}

	size_t N = M.size();
	bool zeros = true;
	while (N <= 2 && zeros) {
		zeros = std::find(M.begin(), M.begin() + (long) N, 0) != M.end();
		N -= 1;
	}

	M.resize(N);
	return N;
}
////////////////////////////////////////////////////////////////////////////////
/*! f_grid function
 *
 *      Calculates the grid function described in Frenklach 2002 MOMIC paper
 *      using lagrange interpolation between whole order moments
 *
 *      @param x     \input x grid point
 *      @param y     \input y grid point
 *      @param M     \input vector of whole order moments
 *
 */
double  psdModel_MOMIC::f_grid(int x, int y, const vector<double>& M)
{
	// any MOMIC calculation that is reused is calculated once here
	const double temp0 = MOMIC(x - 1.0 / 2, M);
	const double temp1 = MOMIC(y + 1.0 / 6, M);
	const double temp2 = MOMIC(x - 1.0 / 6, M);
	const double temp3 = MOMIC(y - 1.0 / 6, M);
	const double temp4 = MOMIC(x + 1.0 / 6, M);
	const double temp5 = MOMIC(y - 1.0 / 2, M);
	const double temp6 = MOMIC(y + 7.0 / 6, M);
	const double temp7 = MOMIC(y + 5.0 / 6, M);
	const double temp8 = MOMIC(y + 1.0 / 2, M);
	const double temp9 = MOMIC(x + 1.0 / 2, M);
	const double temp10 = MOMIC(x + 5.0 / 6, M);
	const double temp11 = MOMIC(x + 7.0 / 6, M);
	const double temp12 = MOMIC(y + 13.0 / 6, M);
	const double temp13 = MOMIC(y + 11.0 / 6, M);
	const double temp14 = MOMIC(y + 3.0 / 2, M);
	const double temp15 = MOMIC(x + 3.0 / 2, M);
	const double temp16 = MOMIC(x + 11.0 / 6, M);
	const double temp17 = MOMIC(x + 13.0 / 6, M);

	const double f1_0 = temp0 * temp1
	    + 2 * temp2 * temp3
	    + temp4 * temp5;
	const double f1_1 = temp0 * temp6
	    + 2 * temp2 * temp7
	    + temp4 * temp8
	    + temp9 * temp1
	    + 2 * temp10 * temp3
	    + temp11 * temp5;

	vector<double> temp_x;
	vector<double> temp_y;
	double value;

	if (y >= 4) {
		temp_x = {0, 1};
		temp_y = {log10(f1_0), log10(f1_1)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);
		return pow(10, value);
	}

	double f1_2 = temp0 * temp12
	    + 2 * temp2 * temp13
	    + temp4 * temp14
	    + 2 * temp9 * temp6
	    + 4 * temp10 * temp7
	    + 2 * temp11 * temp8
	    + temp15 * temp1
	    + 2 * temp16 * temp3
	    + temp17 * temp5;

	if (y >= 3) {
		temp_x = {0, 1, 2};
		temp_y = {log10(f1_0), log10(f1_1), log10(f1_2)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);

		return pow(10, value);
	}

	double f1_3 = temp0 * MOMIC(y + 19.0 / 6, M)
	    + 2 * temp2 * MOMIC(y + 17.0 / 6, M)
	    + temp4 * MOMIC(y + 5.0 / 2, M)
	    + 3 * temp9 * temp12
	    + 6 * temp10 * temp13
	    + 3 * temp11 * temp14
	    + 3 * temp15 * temp6
	    + 6 * temp16 * temp7
	    + 3 * temp17 * temp8
	    + MOMIC(x + 5.0 / 2, M) * temp1
	    + 2 * MOMIC(x + 17.0 / 6, M) * temp3
	    + MOMIC(x + 19.0 / 6, M) * temp5;

	temp_x = {0, 1, 2, 3};
	temp_y = {log10(f1_0), log10(f1_1), log10(f1_2), log10(f1_3)};

	value = lagrangeInterp(1.0 / 2, temp_x, temp_y);

	return pow(10, value);
}
double  psdModel_MOMIC::MOMICCoagulationRate(const state& state, size_t r){
    // the converions between signed and unsigned with r and k is midly concerning, but as far as I can see shouldn't be a problem

	if (r == 1)
		return 0;

	const double mu_1 = state.getMoment(1) / state.getMoment(0);
	const double d_g = pow(6 * kb * state.T / state.P / M_PI, 1.0 / 3);
	const double d_p = pow(6 * mu_1 / rhoSoot / M_PI, 1.0 / 3);
	const double lambda_g = kb * state.T / (pow(2, 0.5) * M_PI * pow(d_g, 2) * state.getP());
	const double Kn = lambda_g / d_p;

	double Rate_C;

	const double K_C = 2 * kb * state.T / (3 * state.getMuGas());
	const double K_Cprime = 1.257 * lambda_g * pow(M_PI * rhoSoot / 6, 1.0 / 3);

	if (r == 0) {
		Rate_C = -K_C * (pow(state.getMoment(0), 2)
			+ MOMIC(1.0 / 3, state.getMomentsConst()) * MOMIC(-1.0 / 3, state.getMomentsConst())
			+ K_Cprime * (3 * MOMIC(-1.0 / 3, state.getMomentsConst()) * state.getMoment(0)
				+ MOMIC(2.0 / 3, state.getMomentsConst()) * MOMIC(1.0 / 3, state.getMomentsConst())));
	}
	else {
		Rate_C = 0;
		for (size_t k = 0; k < r; k++) {
			if (k <= r - k)
				Rate_C += binomial_coefficient(r, k) * (2 * state.getMoment(k) * state.getMoment(r - k)
					+ MOMIC((double) k + 1.0 / 3, state.getMomentsConst()) * MOMIC((double) r - (double) k - 1.0 / 3, state.getMomentsConst())
					+ MOMIC((double) k - 1.0 / 3, state.getMomentsConst()) * MOMIC((double) r - (double) k + 1.0 / 3, state.getMomentsConst())
					+ 2 * K_Cprime * (2 * MOMIC((double) k - 1.0 / 3, state.getMomentsConst()) * state.getMoment(r - k)
						+ state.getMoment(k) * MOMIC((double) r - (double) k - 1.0 / 3, state.getMomentsConst())
						+ MOMIC((double) k - 2.0 / 3, state.getMomentsConst()) * MOMIC((double) r - (double) k + 1.0 / 3, state.getMomentsConst())));
		}
		Rate_C *= 0.5 * K_C;
	}

	double Rate_F;
	const double K_f = 2.2 * pow(3 / (4 * M_PI * state.getRhoSoot()), 2.0 / 3) * pow(8 * M_PI * kb * state.T, 1.0 / 2);

	if (r == 0) {
		Rate_F = -0.5 * K_f * f_grid(0, 0, state.getMomentsConst());
	}
	else {
		Rate_F = 0;
		for (size_t k = 1; k < r; k++) {
			if (k <= r - k)
				Rate_F += binomial_coefficient(r, k) * f_grid((int) k, (int) r - (int) k, state.getMomentsConst());
		}
		Rate_F *= 0.5 * K_f;
	}

	return Rate_F / (1.0 + 1 / Kn) + Rate_C / (1 + Kn);
}
////////////////////////////////////////////////////////////////////////////////
/*! lagrangeInterp function
 *
 *      Calculates the Lagrange interpolated value from whole order moments.
 *
 *      @param x_i  \input      x value of desired interpolation
 *      @param x    \input      vector of x values to interpolate amongst
 *      @param y    \input      vector of y values to interpolate amongst
 *      @param y_i  \output     interpolated y value
 *
 */
double  psdModel_MOMIC::lagrangeInterp(double x_i, const vector<double>& x, const vector<double>& y)
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
/*! MOMIC function
 *
 *      Calculates the desired fractional moment by lagrange interpolation
 *      between whole order moments. Because it uses log moments, it will crash
 *      if any moment is less than or equal to zero.
 *
 *      @param p     \input     desired interpolation value
 *      @param M     \input     vector of whole order moments
 *
 */
double  psdModel_MOMIC::MOMIC(double p, const vector<double>& M)
{
	if (p == 0)
		return M.at(0);

	size_t size = M.size();
	if (p < 0 && M.size() != 2)
		size = 3;

	vector<double> log_mu(size, 0);
	vector<double> x(size, 0);

	for (size_t i = 0; i < size; i++) {
		log_mu.at(i) = log10(M.at(i) / M.at(0));
		x.at(i) = (double) i;
	}

	const double log_mu_p = lagrangeInterp(p, x, log_mu);

	return pow(10, log_mu_p) * M.at(0);
}
void  psdModel_MOMIC::checkState(const state& state) const {
    if (state.getNumMoments() < 1)
        throw runtime_error("MOMIC soot model requires 1-8 soot moments");
    if (state.getNumMoments() > 8)
        cerr << "MOMIC soot model requires 1-8 soot moments, got " << state.getNumMoments() << endl;
}
