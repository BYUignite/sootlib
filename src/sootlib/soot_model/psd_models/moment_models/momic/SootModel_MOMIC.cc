#include <algorithm>
#include "SootModel_MOMIC.h"
#include "lib/binomial/binomial.h"

using namespace std;
using namespace soot;

SootModel_MOMIC* SootModel_MOMIC::getInstance(unique_ptr<CoagulationModel> coagulationModel,
                                              unique_ptr<GrowthModel> growthModel,
                                              unique_ptr<NucleationModel> nucleationModel,
                                              unique_ptr<OxidationModel> oxidationModel) {
    return new SootModel_MOMIC(move(coagulationModel),
                               move(growthModel),
                               move(nucleationModel),
                               move(oxidationModel));
}
SootModel_MOMIC::SootModel_MOMIC(unique_ptr<CoagulationModel> coagulationModel,
                                 unique_ptr<GrowthModel> growthModel,
                                 unique_ptr<NucleationModel> nucleationModel,
                                 unique_ptr<OxidationModel> oxidationModel) : SootChemistry(move(coagulationModel),
                                                                                            move(growthModel),
                                                                                            move(nucleationModel),
                                                                                            move(oxidationModel)) {
}
SourceTerms SootModel_MOMIC::getSourceTerms(State& state) const {
    const size_t N = downselectIfNeeded(state.getMoments());
    MassRateRatios massRateRatios;

    // FIXME it looks like these guys are trying to trigger optional parts of the supporting psd_models with negative values
    // this does not work well with what I have set up now :( there needs to be some explicit arguments for that
    const double Jnuc = nucleationModel->getNucleationRate(state, {}, {}, massRateRatios);
    const double Kgrw = growthModel->getGrowthRate(state, massRateRatios);
    const double Koxi = oxidationModel->getOxidationRate(state, massRateRatios);

    vector<double> Mnuc(state.getNumMoments(), 0);

    double m_nuc = state.getCMin() * MW_C / Na;
    for (size_t i = 0; i < N; i++)
        Mnuc.at(i) = pow(m_nuc, i) * Jnuc;

    vector<double> Mcnd(state.getNumMoments(), 0);

    if (nucleationModel->getMechanism() == NucleationMechanism::PAH) {
        for (size_t i = 1; i < N; i++)
            Mcnd.at(i) = MOMICCoagulationRate(state, (int) i) * state.getDimer() * state.getMDimer() * (double) i;
    }

    vector<double> Mgrw(state.getNumMoments(), 0);

    const double Acoef = M_PI * pow(abs(6 / M_PI / state.getRhoSoot()), 2.0 / 3);
    for (size_t i = 1; i < N; i++)
        Mgrw.at(i) = Kgrw * Acoef * (double) i * MOMIC((double) i - 1.0 / 3, state.getMomentsConst());

    vector<double> Moxi(state.getNumMoments(), 0);

    for (size_t i = 1; i < N; i++)
        Moxi.at(i) = Koxi * Acoef * (double) i * MOMIC((double) i - 1.0 / 3, state.getMomentsConst());

    vector<double> Mcoa(state.getNumMoments(), 0);

    if (coagulationModel->getMechanism() != CoagulationMechanism::NONE) {
        for (size_t i = 0; i < N; i++)
            Mcoa.at(i) = MOMICCoagulationRate(state, (int) i);
    }

    vector<double> sootSourceTerms(state.getNumMoments(), 0);
    for (size_t i = 0; i < state.getNumMoments(); i++)
        sootSourceTerms.at(i) = Mnuc.at(i) + Mcnd.at(i) + Mgrw.at(i) + Moxi.at(i) + Mcoa.at(i);

    //---------- get gas source terms

    map<GasSpecies, double> gasSourceTerms = getGasSourceTerms(state, massRateRatios, Mnuc.at(1), Mgrw.at(1), Moxi.at(1), Mcnd.at(1));
    map<size_t, double> PAHSourceTerms = getPAHSourceTerms(state, massRateRatios, Mnuc.at(1), 0, Moxi.at(1), Mcnd.at(1));

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
size_t SootModel_MOMIC::downselectIfNeeded(vector<double>& M)
{
	if (M.at(0) <= 0)
		return 0;

	if (M.at(1) <= 0) {
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
double SootModel_MOMIC::f_grid(int x, int y, const vector<double>& M)
{
	// TODO save duplicate calculations in this function
	const double f1_0 = MOMIC(x - 1.0 / 2, M) * MOMIC(y + 1.0 / 6, M) + 2 * MOMIC(x - 1.0 / 6, M) * MOMIC(y - 1.0 / 6, M) + MOMIC(x + 1.0 / 6, M) * MOMIC(y - 1.0 / 2, M);
	const double f1_1 = MOMIC(x - 1.0 / 2, M) * MOMIC(y + 7.0 / 6, M) + 2 * MOMIC(x - 1.0 / 6, M) * MOMIC(y + 5.0 / 6, M) + MOMIC(x + 1.0 / 6, M) * MOMIC(y + 1.0 / 2, M) + MOMIC(x + 1.0 / 2, M) * MOMIC(y + 1.0 / 6, M) + 2 * MOMIC(x + 5.0 / 6, M) * MOMIC(y - 1.0 / 6, M) + MOMIC(x + 7.0 / 6, M) * MOMIC(y - 1.0 / 2, M);

	vector<double> temp_x;
	vector<double> temp_y;
	double value;

	if (y >= 4) {
		temp_x = {0, 1};
		temp_y = {log10(f1_0), log10(f1_1)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);
		return pow(10, value);
	}

	double f1_2 = MOMIC(x - 1.0 / 2, M) * MOMIC(y + 13.0 / 6, M) + 2 * MOMIC(x - 1.0 / 6, M) * MOMIC(y + 11.0 / 6, M) + MOMIC(x + 1.0 / 6, M) * MOMIC(y + 3.0 / 2, M) + 2 * MOMIC(x + 1.0 / 2, M) * MOMIC(y + 7.0 / 6, M) + 4 * MOMIC(x + 5.0 / 6, M) * MOMIC(y + 5.0 / 6, M) + 2 * MOMIC(x + 7.0 / 6, M) * MOMIC(y + 1.0 / 2, M) + MOMIC(x + 3.0 / 2, M) * MOMIC(y + 1.0 / 6, M) + 2 * MOMIC(x + 11.0 / 6, M) * MOMIC(y - 1.0 / 6, M) + MOMIC(x + 13.0 / 6, M) * MOMIC(y - 1.0 / 2, M);

	if (y >= 3) {
		temp_x = {0, 1, 2};
		temp_y = {log10(f1_0), log10(f1_1), log10(f1_2)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);

		return pow(10, value);
	}

	double f1_3 = MOMIC(x - 1.0 / 2, M) * MOMIC(y + 19.0 / 6, M) + 2 * MOMIC(x - 1.0 / 6, M) * MOMIC(y + 17.0 / 6, M) + MOMIC(x + 1.0 / 6, M) * MOMIC(y + 5.0 / 2, M) + 3 * MOMIC(x + 1.0 / 2, M) * MOMIC(y + 13.0 / 6, M) + 6 * MOMIC(x + 5.0 / 6, M) * MOMIC(y + 11.0 / 6, M) + 3 * MOMIC(x + 7.0 / 6, M) * MOMIC(y + 3.0 / 2, M) + 3 *MOMIC(x + 3.0 / 2, M) * MOMIC(y + 7.0 / 6, M) + 6 * MOMIC(x + 11.0 / 6, M) * MOMIC(y + 5.0 / 6, M) + 3 * MOMIC(x + 13.0 / 6, M) * MOMIC(y + 1.0 / 2, M) + MOMIC(x + 5.0 / 2, M) * MOMIC(y + 1.0 / 6, M) + 2 * MOMIC(x + 17.0 / 6, M) * MOMIC(y - 1.0 / 6, M) + MOMIC(x + 19.0 / 6, M) * MOMIC(y - 1.0 / 2, M);

	temp_x = {0, 1, 2, 3};
	temp_y = {log10(f1_0), log10(f1_1), log10(f1_2), log10(f1_3)};

	value = lagrangeInterp(1.0 / 2, temp_x, temp_y);

	return pow(10, value);
}
double SootModel_MOMIC::MOMICCoagulationRate(const State& state, int r)
{
	if (r == 1)
		return 0;

	const double mu_1 = state.getMoment(1) / state.getMoment(0);
	const double d_g = pow(6 * kb * state.getT() / state.getP() / M_PI, 1.0 / 3);
	const double d_p = pow(6 * mu_1 / state.getRhoSoot() / M_PI, 1.0 / 3);
	const double lambda_g = kb * state.getT() / (pow(2, 0.5) * M_PI * pow(d_g, 2) * state.getP());
	const double Kn = lambda_g / d_p;

	double Rate_C;

	double K_C = 2 * kb * state.getT() / (3 * state.getMuGas());
	double K_Cprime = 1.257 * lambda_g * pow(M_PI * state.getRhoSoot() / 6, 1.0 / 3);

	if (r == 0) {
		Rate_C = -K_C * (pow(state.getMoment(0), 2)
			+ MOMIC(1.0 / 3, state.getMomentsConst()) * MOMIC(-1.0 / 3, state.getMomentsConst())
			+ K_Cprime * (3 * MOMIC(-1.0 / 3, state.getMomentsConst()) * state.getMoment(0)
				+ MOMIC(2.0 / 3, state.getMomentsConst()) * MOMIC(1.0 / 3, state.getMomentsConst())));
	}
	else {
		Rate_C = 0;
		for (int k = 0; k < r; k++) {
			if (k <= r - k)
				Rate_C += binomial_coefficient(r, k) * (2 * state.getMoment(k) * state.getMoment(r - k)
					+ MOMIC(k + 1.0 / 3, state.getMomentsConst()) * MOMIC(r - k - 1.0 / 3, state.getMomentsConst())
					+ MOMIC(k - 1.0 / 3, state.getMomentsConst()) * MOMIC(r - k + 1.0 / 3, state.getMomentsConst())
					+ 2 * K_Cprime * (2 * MOMIC(k - 1.0 / 3, state.getMomentsConst()) * state.getMoment(r - k)
						+ state.getMoment(k) * MOMIC(r - k - 1.0 / 3, state.getMomentsConst())
						+ MOMIC(k - 2.0 / 3, state.getMomentsConst()) * MOMIC(r - k + 1.0 / 3, state.getMomentsConst())));
		}
		Rate_C *= 0.5 * K_C;
	}

	double Rate_F;
	const double K_f = 2.2 * pow(3.0 / (4 * M_PI * state.getRhoSoot()), 2.0 / 3) * pow(8 * M_PI * kb * state.getT(), 1.0 / 2);

	if (r == 0) {
		Rate_F = -0.5 * K_f * f_grid(0, 0, state.getMomentsConst());
	}
	else {
		Rate_F = 0;
		for (int k = 1; k < r; k++) {
			if (k <= r - k)
				Rate_F += binomial_coefficient(r, k) * f_grid(k, r - k, state.getMomentsConst());
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
double SootModel_MOMIC::lagrangeInterp(double x_i, const vector<double>& x, const vector<double>& y)
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
double SootModel_MOMIC::MOMIC(double p, const vector<double>& M)
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
