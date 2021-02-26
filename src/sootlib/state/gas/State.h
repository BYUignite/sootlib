#ifndef STATE_H
#define STATE_H

#include <map>
#include <set>

#include "sootlib/static.h"

namespace soot
{
struct GasComponent
{
	// mass fraction
	// Units: -
	double y;
	// molecular weight
	// Units: kg/kmol
	double MW;
};

class State
{
public:
	State() = default;

	/* Getters and setters */
	[[nodiscard]] double getT() const;
	void setT(double t);
	[[nodiscard]] double getP() const;
	void setP(double p);
	[[nodiscard]] double getGasRho() const;
	void setGasRho(double rho);
	[[nodiscard]] double getMw() const;
	void setMw(double mw);
	[[nodiscard]] double getMu() const;
	void setMu(double mu);
	GasComponent& PAH(size_t numC);
	[[nodiscard]] double getC2H2Frac() const;
	void setC2H2Frac(double c2H2Frac);
	[[nodiscard]] double getO2Frac() const;
	void setO2Frac(double o2Frac);
	[[nodiscard]] double getHFrac() const;
	void setHFrac(double hFrac);
	[[nodiscard]] double getH2Frac() const;
	void setH2Frac(double h2Frac);
	[[nodiscard]] double getOHFrac() const;
	void setOHFrac(double ohFrac);
	[[nodiscard]] double getH2OFrac() const;
	void setH2OFrac(double h2OFrac);
	[[nodiscard]] double getCOFrac() const;
	void setCOFrac(double coFrac);
	[[nodiscard]] double getElementalCFrac() const;
	void setElementalCFrac(double elementalCFrac);
	[[nodiscard]] double getElementalHFrac() const;
	void setElementalHFrac(double elementalHFrac);

	[[nodiscard]] double getC_C2H2() const;
	[[nodiscard]] double getC_O2() const;
	[[nodiscard]] double getC_H() const;
	[[nodiscard]] double getC_H2() const;
	[[nodiscard]] double getC_OH() const;
	[[nodiscard]] double getC_H2O() const;
	[[nodiscard]] double getC_CO() const;
	[[nodiscard]] double getC_elementalC() const;
	[[nodiscard]] double getC_elementalH() const;

	[[nodiscard]] double getP_C2H2() const;
	[[nodiscard]] double getP_O2() const;
	[[nodiscard]] double getP_H() const;
	[[nodiscard]] double getP_H2() const;
	[[nodiscard]] double getP_OH() const;
	[[nodiscard]] double getP_H2O() const;
	[[nodiscard]] double getP_CO() const;
	[[nodiscard]] double getP_elementalC() const;
	[[nodiscard]] double getP_elementalH() const;

	[[nodiscard]] double getGasMeanFreePath() const;

	[[nodiscard]] GasComponent getPAH(size_t n, GasComponent def={0, 0}) const;
	[[nodiscard]] double getPAHFrac(size_t n, double def=0) const;
	[[nodiscard]] double getPAHMW(size_t n, double def=0) const;
	[[nodiscard]] double getC_PAH(size_t n, double def=0) const;
	[[nodiscard]] double getP_PAH(size_t n, double def=0) const;
	[[nodiscard]] double getM_PAH(size_t n, double def=0) const;
	[[nodiscard]] double getGammai(size_t n, double def=0) const;
	[[nodiscard]] double getNi(size_t n, double def=0) const;
	void setPAH(size_t n, GasComponent comp);
	void setPAH(size_t n, double frac, double MW);
	[[nodiscard]] size_t getNumPAH() const;
	[[nodiscard]] const std::set<size_t>& getPAHSpecies() const;

private:
	/* Overall gas properties */

	// temperature
	// Units: K
	double T = 0;
	// pressure
	// Units: Pa
	double P = 0;
	// density
	// Units: kg/m3
	double gasRho = 0;
	// mean molecular weight
	// Units: kg/mol
	double MW = 0;
	// coefficient of friction
	// Units: kg/m*s
	double mu = 0;

	/* Gas Species */
	double C2H2_frac = 0;
	double O2_frac = 0;
	double H_frac = 0;
	double H2_frac = 0;
	double OH_frac = 0;
	double H2O_frac = 0;
	double CO_frac = 0;
	double elementalC_frac = 0;
	double elementalH_frac = 0;

	/* Polycyclic Aromatic Hydrocarbons */
	// key: number of carbons in PAH
	// value: GasState of that species
	std::map<size_t, GasComponent> PAHdata;
	std::set<size_t> PAHspecies;

	double sootRho = 0;
	double cMin = 0;
	double dimer = 0;
	double mDimer = 0;
	double wdotD = 0;
	bool goodMDimerValue = true;
	bool goodDimerValue = true;
	void calculateDimer();

	// TODO these don't quite replicate the functionality in set_m_dimer and set_Ndimer yet
	[[nodiscard]] double getSootRho() const;
	void setSootRho(double rho);
	[[nodiscard]] double getCMin() const;
	[[nodiscard]] double getDimer() const;
	[[nodiscard]] double getMDimer();
	[[nodiscard]] double getWDotD();
};
}

#endif //STATE_H
