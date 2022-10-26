#include "sootModels/sootChemistry/coagulationModels/coagulationModel_FUCHS.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

double coagulationModel_FUCHS::getCoagulationSootRate(const state& state,
                                                      double m1,
                                                      double m2) const {

    if (m1 <= mmin || m2 <= mmin) return 0.0;

    double d1 = pow(6.*m1/(M_PI*rhoSoot), onethird);
    double d2 = pow(6.*m1/(M_PI*rhoSoot), onethird);

    double mfp = state.getGasMeanFreePath();
    double Kn1 = 2*mfp/d1;
    double Kn2 = 2*mfp/d2;

    double Cc1 = 1 + Kn1 * (1.257 + 0.4*exp(-1.1/Kn1));   // Seinfeld p. 372 eq. 9.34. This is for air at 298 K, 1 atm
    double Cc2 = 1 + Kn2 * (1.257 + 0.4*exp(-1.1/Kn2));   // for D<<mfp_g, Cc = 1 + 1.657*Kn; Seinfeld p. 380: 10% error at Kn=1, 0% at Kn=0.01, 100

    double D1 = kb*state.T/(3.*M_PI*state.muGas) * Cc1/d1;
    double D2 = kb*state.T/(3.*M_PI*state.muGas) * Cc2/d2;

    double c1 = sqrt(8.*kb*state.T/(M_PI * m1));
    double c2 = sqrt(8.*kb*state.T/(M_PI * m2));

    double l1 = 8.*D1/(M_PI*c1);
    double l2 = 8.*D2/(M_PI*c2);

    double g1 = root2/(3.*d1*l1) * ( pow(d1+l1, 3.0) - pow(d1*d1 + l1*l1, 1.5) ) - root2*d1;
    double g2 = root2/(3.*d2*l2) * ( pow(d2+l2, 3.0) - pow(d2*d2 + l2*l2, 1.5) ) - root2*d2;

    double K12 = 2.*M_PI*(D1 + D2)*(d1 + d2) / 
                 ( (d1 + d2)/(d1 + d2 + 2.*sqrt(g1*g1 + g2*g2)) + 
                   8./(eps_c*FM_multiplier)*(D1 + D2)/(sqrt(c1*c1 + c2*c2)*(d1 + d2)) 
                 );
    return K12;
}
