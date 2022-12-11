#include "sootModel_LOGN.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking pointers to chemistry models as input.
/// User creates these pointers nominally by "new-ing" them.
///
/// @param nsoot_ \input number of soot moments (should be 3).
/// @param nucl_  \input pointer to nucleation model.
/// @param grow_  \input pointer to growth model.
/// @param oxid_  \input pointer to oxidation model.
/// @param coag_  \input pointer to coagulation model.
///
////////////////////////////////////////////////////////////////////////////////

sootModel_LOGN::sootModel_LOGN(size_t            nsoot_,
                               nucleationModel  *nucl_,
                               growthModel      *grow_,
                               oxidationModel   *oxid_,
                               coagulationModel *coag_) :
        sootModel(nsoot_, nucl_, grow_, oxid_, coag_) {

    if (nsoot_ != 3)
        throw runtime_error("LOGN requires nsoot=3");

    psdMechType = psdMech::LOGN;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking enumerations names as input.
/// Chemistry pointers are created (new-ed) here based on those enumerations.
///
/// @param nsoot_ \input number of soot moments (should be 3).
/// @param Nmech  \input one of enum class nucleationMech in sootDefs.h
/// @param Gmech  \input one of enum class growthMech in sootDefs.h
/// @param Omech  \input one of enum class oxidationMech in sootDefs.h
/// @param Cmech  \input one of enum class coagulationMech in sootDefs.h
///
////////////////////////////////////////////////////////////////////////////////

sootModel_LOGN::sootModel_LOGN(size_t          nsoot_,
                               nucleationMech  Nmech,
                               growthMech      Gmech,
                               oxidationMech   Omech,
                               coagulationMech Cmech) :
        sootModel(nsoot_, Nmech, Gmech, Omech, Cmech) {

    if (nsoot_ != 3)
        throw runtime_error("LOGN requires nsoot=3");

    psdMechType = psdMech::LOGN;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Compute PAH condensation terms for LOGN model.
/// Function split out from getSourceTerms so that it can be called in nucleationModel_PAH
/// for computing the pah dimer concentration.
///
/// Function only called if nucleationMech::PAH.
/// Function called by nucleationModel_PAH::getNucleationSootRate
///
/// @param state  \input gas and soot state, set by user.
/// @param mDimer \input  dimer mass (kg)
/// @return pah/soot sollision rate per dimer. Call it I. I*mDimer*nDimer = Cnd1 (=) kg/m3*s
///
////////////////////////////////////////////////////////////////////////////////

double sootModel_LOGN::pahSootCollisionRatePerDimer(const state &state, const double mDimer) const {

    if (nucl->mechType != nucleationMech::PAH)
        return 0.0;

    //-----------  get moment values

    const double M0 = state.sootVar[0];
    const double M1 = state.sootVar[1];
    const double M2 = state.sootVar[2];

    //-----------  calculate coagulation constants

    const double Kfm = eps_c * sqrt(0.5*M_PI*kb*state.T) * pow(6./(M_PI*rhoSoot), twothird);
    const double Kc  = 2.*kb*state.T/(3./state.muGas);
    const double Kcp = 2.*1.657*state.getGasMeanFreePath()*pow(M_PI*rhoSoot/6., onethird);

    //----------- reused Mr values

    const double M26  = Mr( 2.0/6.0, M0, M1, M2);
    const double M46  = Mr( 4.0/6.0, M0, M1, M2);
    const double Mn36 = Mr(-3.0/6.0, M0, M1, M2);
    const double Mn16 = Mr(-1.0/6.0, M0, M1, M2);
    const double Mn26 = Mr(-2.0/6.0, M0, M1, M2);
    const double Mn46 = Mr(-4.0/6.0, M0, M1, M2);
    const double M16  = Mr( 1.0/6.0, M0, M1, M2);

    const double mD16  = pow(mDimer,  1./6.);
    const double mDn16 = pow(mDimer, -1./6.);
    const double mDn36 = pow(mDimer, -0.5);
    const double mD26  = pow(mDimer,  onethird);
    const double mDn26 = pow(mDimer, -onethird);
    const double mD46  = pow(mDimer,  twothird);
    const double mDn46 = pow(mDimer, -twothird);

    //----------- FM (variable name: I for integrated, as in moment)

    const double Ifm1 = Kfm*bCoag * (M0  *mD16  + 2.*M26*mDn16 +
                                     M46 *mDn36 + 2.*Mn16*mD26 +
                                     Mn36*mD46  + M16);

    //----------- continuum

    const double Ic1 = Kc * ( 2.*M0 + Mn26*mD26 + M26*mDn26    +
                              Kcp*(M0*mDn26 + Mn26 + M26*mDn46 + Mn46*mD26) );

    //---------- return harmonic mean

    return Ifm1*Ic1/(Ifm1 + Ic1);
}

////////////////////////////////////////////////////////////////////////////////
///
/// Primary user interface.
/// 
/// @param state       \input  gas and soot state, set by user.
/// @param sootSources \output soot moment (r) sources (kg^r/m3*s).
/// @param gasSources  \output vector of gas species rates (kg/m3*s)
/// @param pahSources  \output vector of gas PAH species rates (kg/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_LOGN::getSourceTerms(state &state, 
                                    std::vector<double> &sootSources,
                                    std::vector<double> &gasSources,
                                    std::vector<double> &pahSources) const {

    double N0   = 0, N1   = 0, N2   = 0;
    double G0   = 0, G1   = 0, G2   = 0;
    double X0   = 0, X1   = 0, X2   = 0;
    double C0   = 0, C1   = 0, C2   = 0;
    double Cnd0 = 0, Cnd1 = 0, Cnd2 = 0;

    //-----------  get moment values

    const double M0 = state.sootVar[0];
    const double M1 = state.sootVar[1];
    const double M2 = state.sootVar[2];

    //-----------  calculate coagulation constants

    const double Kfm = eps_c * sqrt(0.5*M_PI*kb*state.T) * pow(6./(M_PI*rhoSoot), twothird);
    const double Kc  = 2.*kb*state.T/(3./state.muGas);
    const double Kcp = 2.*1.657*state.getGasMeanFreePath()*pow(M_PI*rhoSoot/6., onethird);

    //----------- reused Mr values

    const double M26 =  Mr( 2.0/6.0, M0, M1, M2);
    const double M46 =  Mr( 4.0/6.0, M0, M1, M2);
    const double Mn36 = Mr(-3.0/6.0, M0, M1, M2);
    const double Mn16 = Mr(-1.0/6.0, M0, M1, M2);
    const double Mn26 = Mr(-2.0/6.0, M0, M1, M2);
    const double Mn46 = Mr(-4.0/6.0, M0, M1, M2);
    const double M86 =  Mr( 8.0/6.0, M0, M1, M2);
    const double M106=  Mr(10.0/6.0, M0, M1, M2);
    const double M36 =  Mr( 3.0/6.0, M0, M1, M2);
    const double M56 =  Mr( 5.0/6.0, M0, M1, M2);
    const double M76 =  Mr( 7.0/6.0, M0, M1, M2);
    const double M16 =  Mr( 1.0/6.0, M0, M1, M2);

    //---------- nucleation terms

    double Jnuc = nucl->getNucleationSootRate(state);    // #/m3*s

    const double mMin = state.cMin*gasSpMW[(int)gasSp::C]/Na;

    N0 = Jnuc;                 // #/m3*s
    N1 = Jnuc * mMin;          // kg_soot/m3*s
    N2 = Jnuc * mMin * mMin;

    //---------- PAH condensation

    if (nucl->mechType == nucleationMech::PAH) {

        double mDimer = nucl->DIMER.mDimer;
        double nDimer = nucl->DIMER.nDimer;

        const double mD16  = pow(mDimer,  1./6.);
        const double mDn16 = pow(mDimer, -1./6.);
        const double mDn36 = pow(mDimer, -0.5);
        const double mD26  = pow(mDimer,  onethird);
        const double mDn26 = pow(mDimer, -onethird);
        const double mD46  = pow(mDimer,  twothird);
        const double mDn46 = pow(mDimer, -twothird);

        //----------- FM (variable name: I for integrated, as in moment)

        const double Ifm1 =    Kfm*bCoag * (M0  *mD16  + 2.*M26*mDn16 +
                                            M46 *mDn36 + 2.*Mn16*mD26 +
                                            Mn36*mD46  + M16);

        const double Ifm2 = 2.*Kfm*bCoag * (M1  *mD16  + 2.*M86*mDn16 +
                                            M106*mDn36 + 2.*M56*mD26  +
                                            M36 *mD46  + M76);

        //----------- continuum

        const double Ic1 = Kc    * ( 2.*M0 + Mn26*mD26 + M26*mDn26    +
                                     Kcp*(M0*mDn26 + Mn26 + M26*mDn46 + Mn46*mD26) );


        const double Ic2 = 2.*Kc * ( 2.*M1 + M46 *mD26 + M86*mDn26    +
                                     Kcp*(M1*mDn26 + M46  + M86*mDn46 + M26*mD26) );

        //----------- source terms (harmonic mean)

        Cnd0 = 0.0;
        Cnd1 = mDimer*nDimer*(Ifm1*Ic1)/(Ifm1 + Ic1);
        Cnd2 = mDimer*nDimer*(Ifm2*Ic2)/(Ifm2 + Ic2);
    }

    //---------- growth terms

    double Kgrw = grow->getGrowthSootRate(state);

    G0 = 0;
    G1 = Kgrw*M_PI*pow(6./(M_PI*rhoSoot), twothird)*M46;
    G2 = Kgrw*M_PI*pow(6./(M_PI*rhoSoot), twothird)*M106* 2.0;

    //---------- oxidation terms

    double Koxi = oxid->getOxidationSootRate(state);

    X0 =  0;
    X1 = -Koxi*M_PI*pow(6.0/(M_PI*rhoSoot), twothird)*M46;
    X2 = -Koxi*M_PI*pow(6.0/(M_PI*rhoSoot), twothird)*M106* 2.0;

    //---------- coagulation terms \todo: LOGN coagulation doesnt fit in the pattern (not using coag)

    double C0_fm =   -Kfm*bCoag*(M0*M16 + 2.*M26*Mn16 + M46*Mn36);       // free molecular
    double C2_fm = 2.*Kfm*bCoag*(M1*M76 + 2.*M86*M56  + M106*M36);

    double C0_c = -Kc*( M0*M0 + M26*Mn26 + Kcp*(M0*Mn26 + M26*Mn46));    // continuum
    double C2_c = 2.*Kc*(M1*M1 + M46*M86 + Kcp*(M1*M46 + M26*M86));

    C0 = C0_fm*C0_c/(C0_fm + C0_c);                                      // harmonic mean
    C1 = 0;
    C2 = C2_fm*C2_c/(C2_fm + C2_c);

    // \todo choose fm, c, hm based on user inputs; also account for FM_multiplier

    //---------- combine to make soot source terms

    sootSources[0] = (N0 + G0 + Cnd0 - X0 + C0);    // #/m3*s
	sootSources[1] = (N1 + G1 + Cnd1 - X1 + C1);    // kg/m3*s
	sootSources[2] = (N2 + G2 + Cnd2 - X2 + C2);

	//---------- set gas source terms

    vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

    nucl->getNucleationGasRates(N1, nucl_gasSources);
    grow->getGrowthGasRates(    G1, grow_gasSources);
    oxid->getOxidationGasRates( X1, oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

    //---------- set PAH source terms

    if(nucl->mechType == nucleationMech::PAH)
        pahSources = nucl->nucleationPahRxnRates;

}

////////////////////////////////////////////////////////////////////////////////
///
/// Compute fractional moment Mr for integer fraction r
///
/// @param r  \input fraction of the moment.
/// @param M0 \input moment 0 (\#/m3)
/// @param M1 \input moment 1 (kg_soot/m3)
/// @param M2 \input moment 2 (kg^2/m3)
///
////////////////////////////////////////////////////////////////////////////////

double sootModel_LOGN::Mr(double r, double M0, double M1, double M2) const {

    double M0_exp = 1. + 0.5*r*(r - 3.);
    double M1_exp = r*(2. - r);
    double M2_exp = 0.5*r*(r - 1.);

    if (M2 == 0 && M2_exp < 0)
        M2_exp = 0;

    return pow(M0, M0_exp) * pow(M1, M1_exp) * pow(M2, M2_exp);
}
