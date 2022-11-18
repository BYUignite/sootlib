#include "sootModel_LOGN.h"

using namespace std;
using namespace soot;

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
/** Compute pah condensation terms for LOGN model.
 *  Function split out from getSourceTerms so that it can be called in nucleationModel_PAH
 *  for computing the pah dimer concentration.
 *  Return value is the pah/soot collision rate per dimer. Call it I.
 *  I*mDimer*nDimer = Cnd1 (=) kg/m3*s 
 */

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

    //----------- reused Mk values

    const double M13 =  Mk( 1.0/3.0, M0, M1, M2);
    const double M23 =  Mk( 2.0/3.0, M0, M1, M2);
    const double Mn12 = Mk(-1.0/2.0, M0, M1, M2);
    const double Mn16 = Mk(-1.0/6.0, M0, M1, M2);
    const double Mn13 = Mk(-1.0/3.0, M0, M1, M2);
    const double Mn23 = Mk(-2.0/3.0, M0, M1, M2);
    const double M16 =  Mk( 1.0/6.0, M0, M1, M2);

    const double mD16  = pow(mDimer,  1./6.);
    const double mDn16 = pow(mDimer, -1./6.);
    const double mDn12 = pow(mDimer, -0.5);
    const double mD13  = pow(mDimer,  onethird);
    const double mDn13 = pow(mDimer, -onethird);
    const double mD23  = pow(mDimer,  twothird);
    const double mDn23 = pow(mDimer, -twothird);

    //----------- FM (variable name: I for integrated, as in moment)

    const double Ifm1 =    Kfm*bCoag * (M0  *mD16  + 2.*M13*mDn16 +
        M23 *mDn12 + 2.*Mn16*mD13 +
        Mn12*mD23  + M16);

    //----------- continuum

    const double Ic1 = Kc    * ( 2.*M0 + Mn13*mD13 + M13*mDn13    +
        Kcp*(M0*mDn13 + Mn13 + M13*mDn23 + Mn23*mD13) );

    //-----------

    return (Ifm1*Ic1)/(Ifm1 + Ic1);
}

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

    //----------- reused Mk values

    const double M13 =  Mk( 1.0/3.0, M0, M1, M2);
    const double M23 =  Mk( 2.0/3.0, M0, M1, M2);
    const double Mn12 = Mk(-1.0/2.0, M0, M1, M2);
    const double Mn16 = Mk(-1.0/6.0, M0, M1, M2);
    const double Mn13 = Mk(-1.0/3.0, M0, M1, M2);
    const double Mn23 = Mk(-2.0/3.0, M0, M1, M2);
    const double M43 =  Mk( 4.0/3.0, M0, M1, M2);
    const double M53 =  Mk( 5.0/3.0, M0, M1, M2);
    const double M12 =  Mk( 1.0/2.0, M0, M1, M2);
    const double M56 =  Mk( 5.0/6.0, M0, M1, M2);
    const double M76 =  Mk( 7.0/6.0, M0, M1, M2);
    const double M16 =  Mk( 1.0/6.0, M0, M1, M2);

    //---------- nucleation terms

    double Jnuc = nucl->getNucleationSootRate(state);    // #/m3*s

    const double mMin = state.cMin*gasSpMW[(int)gasSp::C]/Na;

    N0 = Jnuc;                 // #/m3*s
    N1 = Jnuc * mMin;          // kg_soot/m3*s
    N2 = Jnuc * mMin * mMin;

    //-----------  PAH condensation

    if (nucl->mechType == nucleationMech::PAH) {

        double mDimer = nucl->DIMER.mDimer;
        double nDimer = nucl->DIMER.nDimer;

        const double mD16  = pow(mDimer,  1./6.);
        const double mDn16 = pow(mDimer, -1./6.);
        const double mDn12 = pow(mDimer, -0.5);
        const double mD13  = pow(mDimer,  onethird);
        const double mDn13 = pow(mDimer, -onethird);
        const double mD23  = pow(mDimer,  twothird);
        const double mDn23 = pow(mDimer, -twothird);

        //----------- FM (variable name: I for integrated, as in moment)

        const double Ifm1 =    Kfm*bCoag * (M0  *mD16  + 2.*M13*mDn16 +
                                            M23 *mDn12 + 2.*Mn16*mD13 +
                                            Mn12*mD23  + M16);

        const double Ifm2 = 2.*Kfm*bCoag * (M1  *mD16  + 2.*M43*mDn16 +
                                            M53 *mDn12 + 2.*M56*mD13  +
                                            M12 *mD23  + M76);

        //----------- continuum

        const double Ic1 = Kc    * ( 2.*M0 + Mn13*mD13 + M13*mDn13    +
                                     Kcp*(M0*mDn13 + Mn13 + M13*mDn23 + Mn23*mD13) );


        const double Ic2 = 2.*Kc * ( 2.*M1 + M23 *mD13 + M43*mDn13    +
                                     Kcp*(M1*mDn13 + M23  + M43*mDn23 + M13*mD13) );

        //----------- source terms (harmonic mean)

        Cnd0 = 0.0;
        Cnd1 = mDimer*nDimer*(Ifm1*Ic1)/(Ifm1 + Ic1);
        Cnd2 = mDimer*nDimer*(Ifm2*Ic2)/(Ifm2 + Ic2);
    }

    //---------- growth terms

    double Kgrw = grow->getGrowthSootRate(state);

    G0 = 0;
    G1 = Kgrw*M_PI*pow(6./(M_PI*rhoSoot), twothird)*M23;
    G2 = Kgrw*M_PI*pow(6./(M_PI*rhoSoot), twothird)*M53 * 2.0;

    //---------- oxidation terms

    double Koxi = oxid->getOxidationSootRate(state);

    X0 =  0;
    X1 = -Koxi*M_PI*pow(6.0/(M_PI*rhoSoot), twothird)*M23;
    X2 = -Koxi*M_PI*pow(6.0/(M_PI*rhoSoot), twothird)*M53 * 2.0;

    //---------- coagulation terms todo: LOGN coagulation doesnt fit in the pattern (not using coag!, except for pah, but then can be arb. which doesnt make sense for diamers)

    double C0_fm =   -Kfm*bCoag*(M0*M16 + 2.*M13*Mn16 + M23*Mn12);       // free molecular
    double C2_fm = 2.*Kfm*bCoag*(M1*M76 + 2.*M43*M56  + M53*M12);

    double C0_c = -Kc*( M0*M0 + M13*Mn13 + Kcp*(M0*Mn13 + M13*Mn23));    // continuum
    double C2_c = 2.*Kc*(M1*M1 + M23*M43 + Kcp*(M1*M23 + M13*M43));

    C0 = C0_fm*C0_c/(C0_fm + C0_c);                                      // harmonic mean
    C1 = 0;
    C2 = C2_fm*C2_c/(C2_fm + C2_c);

    //---------- combine to make soot source terms

    sootSources[0] = (N0 + G0 + Cnd0 - X0 + C0);    // #/m3*s
	sootSources[1] = (N1 + G1 + Cnd1 - X1 + C1);    // kg/m3*s
	sootSources[2] = (N2 + G2 + Cnd2 - X2 + C2);

	//---------- set gas source terms

    vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

    nucl->getNucleationGasRates(state, N1, nucl_gasSources);
    grow->getGrowthGasRates(    state, G1, grow_gasSources);
    oxid->getOxidationGasRates( state, X1, oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

    //---------- set PAH source terms

    if(nucl->mechType == nucleationMech::PAH)
        pahSources = nucl->nucleationPahRxnRates;

    //todo: what about pah condensation? (here and in other models)

}

////////////////////////////////////////////////////////////////////////////////

double sootModel_LOGN::Mk(double k, double M0, double M1, double M2) const {

    double M0_exp = 1. + 0.5*k*(k - 3.);
    double M1_exp = k*(2. - k);
    double M2_exp = 0.5*k*(k - 1.);

    if (M2 == 0 && M2_exp < 0)
        M2_exp = 0;

    return pow(M0, M0_exp) * pow(M1, M1_exp) * pow(M2, M2_exp);
}
