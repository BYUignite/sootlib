#ifndef SOOTSTATE_H
#define SOOTSTATE_H

namespace soot
{
class SootState
{
public:
	[[nodiscard]] double getRhoSoot() const;
	void setRhoSoot(double rhoSoot);
	[[nodiscard]] double getCmin() const;
	void setCmin(double cmin);
	[[nodiscard]] double getDimer() const;
	void setDimer(double dimer);
	[[nodiscard]] double getMDimer() const;
	void setMDimer(double mDimer);

private:
	// soot density
	// Units: kg/m3
	double rhoSoot;
	// number of carbons in soot nucleation size
	// Units: #
	double Cmin;
	// dimer concentration
	// Units: UNKNOWN
	double dimer;
	// dimer mass
	// Units: UNKNOWN
	double m_dimer;
};
}

#endif //SOOTSTATE_H
