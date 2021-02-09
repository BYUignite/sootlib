#ifndef GASSTATE_H
#define GASSTATE_H

#include <map>

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

class GasState
{
public:
	/* Getters and Setters */
	[[nodiscard]] double getT() const;
	void setT(double t);
	[[nodiscard]] double getP() const;
	void setP(double p);
	[[nodiscard]] double getRho() const;
	void setRho(double rho);
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
	[[nodiscard]] double getOhFrac() const;
	void setOhFrac(double ohFrac);
	[[nodiscard]] double getH2OFrac() const;
	void setH2OFrac(double h2OFrac);
	[[nodiscard]] double getCoFrac() const;
	void setCoFrac(double coFrac);
	[[nodiscard]] double getElementalCFrac() const;
	void setElementalCFrac(double elementalCFrac);
	[[nodiscard]] double getElementalHFrac() const;
	void setElementalHFrac(double elementalHFrac);

private:
	/* Total Gas */
	// temperature
	// Units: K
	double T;
	// pressure
	// Units: Pa
	double P;
	// density
	// Units: kg/m3
	double rho;
	// mean molecular weight
	// Units: kg/mol
	double MW;
	// coefficient of friction
	// Units: kg/m*s
	double mu;

	/* Gas Species */
	double C2H2_frac;
	double O2_frac;
	double H_frac;
	double H2_frac;
	double OH_frac;
	double H2O_frac;
	double CO_frac;
	double elementalC_frac;
	double elementalH_frac;

	/* Polycyclic Aromatic Hydrocarbons */
	// key: number of carbons in PAH
	// value: GasState of that species
	std::map<size_t, GasComponent> PAHs;
};
}

#endif //GASSTATE_H
