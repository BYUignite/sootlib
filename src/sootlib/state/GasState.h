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
	[[nodiscard]] const GasComponent& getC2H2() const;
	void setC2H2(const GasComponent& c2H2);
	[[nodiscard]] const GasComponent& getO2() const;
	void setO2(const GasComponent& o2);
	[[nodiscard]] const GasComponent& getH() const;
	void setH(const GasComponent& h);
	[[nodiscard]] const GasComponent& getH2() const;
	void setH2(const GasComponent& h2);
	[[nodiscard]] const GasComponent& getOH() const;
	void setOH(const GasComponent& oh);
	[[nodiscard]] const GasComponent& getH2O() const;
	void setH2O(const GasComponent& h2O);
	[[nodiscard]] const GasComponent& getCO() const;
	void setCO(const GasComponent& co);
	[[nodiscard]] const GasComponent& getElementalC() const;
	void setElementalC(const GasComponent& elementalC);
	[[nodiscard]] const GasComponent& getElementalH() const;
	void setElementalH(const GasComponent& elementalH);
	GasComponent& PAH(size_t numC);

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
	GasComponent C2H2;
	GasComponent O2;
	GasComponent H;
	GasComponent H2;
	GasComponent OH;
	GasComponent H2O;
	GasComponent CO;
	GasComponent elementalC;
	GasComponent elementalH;

	/* Polycyclic Aromatic Hydrocarbons */
	// key: number of carbons in PAH
	// value: GasState of that species
	std::map<size_t, GasComponent> PAHs;
};
}

#endif //GASSTATE_H
