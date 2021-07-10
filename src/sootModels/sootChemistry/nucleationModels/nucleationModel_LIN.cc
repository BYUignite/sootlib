#include "nucleationModel_LIN.h"

using namespace std;
using namespace soot;

nucleationModel_LIN::nucleationModel_LIN() {

    nucleationRxnRatios->at(gasSp::C2H2) = -1;
    nucleationRxnRatios->at(gasSp::H2)   =  1;
    nucleationRxnRatios->at(gasSp::C)    =  2;

}

double nucleationModel_LIN::getNucleationSootRate(const state& state, const vector<double> &mi, const vector<double> &wi) const {

    //TODO consider second reaction?
    return 0.63E4 * exp(-21100 / state.T) * state.getGasSpeciesC(gasSp::C2H2) * 2 * Na / state.cMin;

}
