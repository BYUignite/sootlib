#include "CoagulationModel_LL.h"
soot::CoagulationModel_LL::CoagulationModel_LL(double m1, double m2)
{
	this->m1 = m1;
	this->m2 = m2;
}
double soot::CoagulationModel_LL::getCoagulationRate() const
{
	const double Ca = 9.0;

	// TODO don't know why we aren't using this method
	//--------- Free molecular form from Fuchs and/or Frenklack below.
	//double Dp1 = pow(6.0*abs(m1)/M_PI/rhoSoot, 1.0/3.0);
	//double Dp2 = pow(6.0*abs(m2)/M_PI/rhoSoot, 1.0/3.0);
	//double m12 = abs(m1*m2/(m1+m2));
	//return Ca/2.0*sqrt(M_PI*kb*T*0.5/m12) * pow(Dp1+Dp2, 2.0);

	// TODO don't know exactly where these members are coming from
	//--------- Equivalent L&L form assuming m1 = m2
	double Dp1 = std::pow(6.0 * std::abs(m1) / M_PI / rhoSoot, 1.0 / 3.0);
	return 2.0 * Ca * sqrt(Dp1 * 6 * kb * T / rhoSoot);

}
