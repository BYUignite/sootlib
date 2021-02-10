#ifndef MOMENTSOOTSTATE_H
#define MOMENTSOOTSTATE_H

#include <sstream>
#include <vector>

namespace soot
{
class MomentSootState
{
public:
	/* Constructor sets values to 0 */
	MomentSootState();

	/* Getters and setters */
	[[nodiscard]] double getRho() const;
	void setRhoSoot(double rhoSoot);
	[[nodiscard]] double getCmin() const;
	void setCmin(double cmin);
	[[nodiscard]] double getDimer() const;
	void setDimer(double dimer);
	[[nodiscard]] double getMDimer() const;
	void setMDimer(double mDimer);
	[[nodiscard]] size_t getNumMoments() const;
	void setNumMoments(size_t n);
	[[nodiscard]] double getMoment(size_t i) const;
	void setMoment(size_t i, double value);

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
	// soot moments
	// Units: UNKNOWN
	std::vector<double> moments;
};
}

#endif //MOMENTSOOTSTATE_H
