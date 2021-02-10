#ifndef BASESOOTSTATE_H
#define BASESOOTSTATE_H

namespace soot
{
class BaseSootState
{
public:
	/* Getters and setters */

	[[nodiscard]] double getRho() const;
	void setRho(double rho);
	[[nodiscard]] double getCMin() const;
	void setCMin(double cMin);
	[[nodiscard]] double getDimer() const;
	void setDimer(double dimer);
	[[nodiscard]] double getMDimer() const;
	void setMDimer(double mDimer);

protected:
	/* Protected constructor initializes values to 0 and prevents base class instantiation */
	BaseSootState();

private:
	/* Soot properties */

	// soot density
	// Units: kg/m3
	double rho;
	// number of carbons in soot nucleation size
	// Units: #
	double cMin;
	// TODO figure out these units
	// dimer concentration
	// Units: UNKNOWN
	double dimer;
	// dimer mass
	// Units: UNKNOWN
	double mDimer;
};
}

#endif //BASESOOTSTATE_H
