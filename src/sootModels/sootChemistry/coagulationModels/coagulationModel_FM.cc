#include "sootModels/sootChemistry/coagulationModels/coagulationModel_FM.h"
#include "constants.h"

using namespace std;
using namespace soot;

double coagulationModel_FM::getCoagulationSootRate(const state& state,
                                                   double m1,
                                                   double m2) const {

    if (m1 <= mmin || m2 <= mmin) return 0.0;

    double Ca = 9;

    double mR  = m1*m2/(m1+m2);       // reduced mass
    double d1 = pow(6.*m1/(M_PI*rhoSoot), onethird);
    double d2 = pow(6.*m1/(M_PI*rhoSoot), onethird);
    double ds = d1 + d2;

    double K12 = sqrt(M_PI*kb*state.T*0.5/mR) * ds*ds; 
            // = 4.*sqrt(6.*d1*kb*state.T/rhoSoot);  // if d1=d2, m1=m2

    return eps_c * K12;
    //return Ca/2.0 * K12;        // LL
}
