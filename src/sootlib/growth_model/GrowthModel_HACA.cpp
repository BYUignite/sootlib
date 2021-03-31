//////////////////////////////////////////////////////////////////////////////////
/*! Growth by HACA
 *
 *      See Appel, Bockhorn, & Frenklach (2000), Comb. & Flame 121:122-136.
 *      For details, see Franklach and Wang (1990), 23rd Symposium, pp. 1559-1566.
 *
 *      Parameters for steric factor alpha updated to those given in Balthasar
 *      and Franklach (2005) Comb. & Flame 140:130-145.
 *
 *      Returns the chemical soot growth rate in kg/m2*s.
 *
 *      @param MomentState&     /input      local moment state; need M0 and M1
 *      @param rSoot            /output     soot growth rate (kg/m2*s)
 */

#include "GrowthModel_HACA.h"

using namespace soot;

double GrowthModel_HACA::getGrowthRate(const MomentState& state) const {

	const double M0 = state.getMoment(0);                           // #/m3
	const double M1 = state.getMoment(1);                           // kg/m3

	const double cC2H2 = state.getGasSpeciesC(GasSpecies::C2H2);    // kmol/m3
	const double cO2   = state.getGasSpeciesC(GasSpecies::O2);      // kmol/m3
	const double cH    = state.getGasSpeciesC(GasSpecies::H);       // kmol/m3
	const double cH2   = state.getGasSpeciesC(GasSpecies::H2);      // kmol/m3
	const double cOH   = state.getGasSpeciesC(GasSpecies::OH);      // kmol/m3
	const double cH2O  = state.getGasSpeciesC(GasSpecies::H2O);     // kmol/m3

	//---------- calculate alpha, other constants

	const double RT       = 1.9872036E-3 * state.getT();            // R (=) kcal/mol
	const double chi_soot = 2.3E15;                                 // (=) sites/cm^2
	const double a_param  = 33.167 - 0.0154 * state.getT();         // a parameter for calculating alpha
	const double b_param  = -2.5786 + 0.00112 * state.getT();       // b parameter for calculating alpha

	//---------- calculate raw HACA reaction rates
	
    const double fR1 = 4.2E13 * exp(-13.0 / RT) * cH / 1000;
	const double rR1 = 3.9E12 * exp(-11.0 / RT) * cH2 / 1000;
	const double fR2 = 1.0E10 * pow(state.getT(), 0.734) * exp(-1.43 / RT) * cOH / 1000;
	const double rR2 = 3.68E8 * pow(state.getT(), 1.139) * exp(-17.1 / RT) * cH2O /1000;
	const double fR3 = 2.0E13 * cH / 1000;
	const double fR4 = 8.00E7 * pow(state.getT(), 1.56) * exp(-3.8 / RT) * cC2H2 / 1000;
	const double fR5 = 2.2E12 * exp(-7.5 / RT) * cO2 / 1000;
	const double fR6 = 1290.0 * 0.13 * state.getP() * (cOH / state.getRhoGas() * MW_OH) / sqrt(state.getT());    // gamma = 0.13 from Neoh et al.

	//---------- Steady state calculation of chi for soot radical; see Frenklach 1990 pg. 1561
	const double denom = rR1 + rR2 + fR3 + fR4 + fR5;
	double chi_rad = 0.0;
	if (denom != 0.0)
		chi_rad = 2 * chi_soot * (fR1 + fR2 + fR6) / denom;        // sites/cm^2

	double alpha = 1.0;                                            // alpha = fraction of available surface sites
	if (M0 > 0.0)
		alpha = tanh(a_param / log10(M1 / M0) + b_param);
	if (alpha < 0.0)
		alpha = 1.0;

	const double c_soot_H   = alpha * chi_soot * 1E4;              // sites/m2-mixture
	const double c_soot_rad = alpha * chi_rad  * 1E4;              // sites/m2-mixture

	return (fR5 * c_soot_rad + fR6 * c_soot_H) / Na * 2 * MW_C;    // kg/m2*s
}
