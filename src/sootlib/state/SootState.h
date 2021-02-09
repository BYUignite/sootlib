#ifndef SOOTSTATE_H
#define SOOTSTATE_H

namespace soot
{
class SootState
{
public:
	/* Constructor sets values to 0 */
	SootState();

	/* Getters and setters */
	[[nodiscard]] double getRho() const;
	void setRhoSoot(double rhoSoot);
	[[nodiscard]] double getCmin() const;
	void setCmin(double cmin);
	[[nodiscard]] double getDimer() const;
	void setDimer(double dimer);
	[[nodiscard]] double getMDimer() const;
	void setMDimer(double mDimer);

private:
	/* Soot properties */

	// soot density
	// Units: kg/m3
	double rhoSoot;
	// number of carbons in soot nucleation size
	// Units: #
	// TODO figure out these units
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
