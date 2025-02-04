#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "sootHeaders.h"
#include "interp_linear.h"

using namespace std;
using namespace soot;

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

    vector<double> z_prof;
    vector<double> v_prof;
    vector<double> T_prof;
    vector<double> rho_prof;
    vector<double> mu_prof;
    vector<double> yH_prof;
    vector<double> yH2_prof;
    vector<double> yO_prof;
    vector<double> yO2_prof;
    vector<double> yOH_prof;
    vector<double> yH2O_prof;
    vector<double> yCO_prof;
    vector<double> yC2H2_prof;

    ifstream ifile("burner_profiles.inp");
    string line;
    std::getline(ifile, line);                     // header

    double d;
    for(int i=0; i<35; i++) {
        ifile >> d; z_prof.push_back(d);
        ifile >> d; v_prof.push_back(d);
        ifile >> d; T_prof.push_back(d);
        ifile >> d; rho_prof.push_back(d);
        ifile >> d; mu_prof.push_back(d);
        ifile >> d; yO2_prof.push_back(d);
        ifile >> d; yO_prof.push_back(d);
        ifile >> d; yH2_prof.push_back(d);
        ifile >> d; yH_prof.push_back(d);
        ifile >> d; yOH_prof.push_back(d);
        ifile >> d; yH2O_prof.push_back(d);
        ifile >> d; yCO_prof.push_back(d);
        ifile >> d; yC2H2_prof.push_back(d);
        ifile >> d;                                 // soot
        ifile >> d;                                 // soot
    }

    Linear_interp LI_v(z_prof,     v_prof);         // interpolate v to some t with LI_T(some_t);
    Linear_interp LI_T(z_prof,     T_prof);
    Linear_interp LI_rho(z_prof,   rho_prof);
    Linear_interp LI_mu(z_prof,    mu_prof);
    Linear_interp LI_yO2(z_prof,   yO2_prof);
    Linear_interp LI_yO(z_prof,    yO_prof);
    Linear_interp LI_yH2(z_prof,   yH2_prof);
    Linear_interp LI_yH(z_prof,    yH_prof);
    Linear_interp LI_yOH(z_prof,   yOH_prof);
    Linear_interp LI_yH2O(z_prof,  yH2O_prof);
    Linear_interp LI_yCO(z_prof,   yCO_prof);
    Linear_interp LI_yC2H2(z_prof, yC2H2_prof);

    //---------- set up and create a soot model

    nucleationModel  *nucl = new soot::nucleationModel_BROWN();
    growthModel      *grow = new soot::growthModel_NONE();
    oxidationModel   *oxid = new soot::oxidationModel_BROWN();
    coagulationModel *coag = new soot::coagulationModel_FM();
    tarModel         *tar  = new soot::tarModel_BROWN();

    size_t nsoot = 2;
    //size_t nsoot = 40;
    size_t Ntar  = 1;

    sootModel_MONO SM(nsoot, nucl, grow, oxid, coag, Ntar, tar);
    //sootModel_LOGN SM(nsoot, Ntar, nucl, grow, oxid, coag, tar);
    //sootModel_QMOM SM(nsoot, Ntar, nucl, grow, oxid, coag, tar);
    //sootModel_MOMIC SM(nsoot, Ntar, nucl, grow, oxid, coag, tar);
    //sootModel_SECT SM(nsoot, Ntar, nucl, grow, oxid, coag, tar);

    SM.coag->set_FM_multiplier(9.0/2.0/2.2);

    //---------- set up thermodynamic state variables

    state  S = state(nsoot, Ntar);
    double P = 101325;                               // pressure in Pa

    vector<double> yGas(size_t(gasSp::size), 0.0);   // y_O2, O, H2, H, OH, H2O, CO, C2H2
    vector<double> yPAH(size_t(pahSp::size), 0.0);
    vector<double> yBio(size_t(bioSp::size), 0.0);
    vector<double> bio_inputs{0.46, 0.16, 0.16, 0.11, 0.11};

    vector<double> Mhat(nsoot, 0.0);                 // M/rho; main variable solved
    vector<double> Mhath(nsoot, 0.0);                // M/rho at half step for midpoint method
    vector<double> M(nsoot, 0.0);                    // M = Mhat * rho
    vector<double> TVhat(Ntar, 0.0);
    vector<double> TVhath(Ntar, 0.0);
    vector<double> TV(Ntar, 0.0);                    // Tar variables
    for (int i=0; i<size_t(bioSp::size); i++)
        yBio[i] = bio_inputs[i];

    S.getyBio(yBio);

    double zstart = z_prof[0];
    double zend   = z_prof.back();
    int    nsteps = 20000;
    double dz     = (zend-zstart)/nsteps;

    ofstream ofile("burner.out");

    //---------- integrate: second order midpoint method

    cout << endl << "********* Writing output to burner.out" << endl;

    ofile << setprecision(2) << fixed;
    ofile << setprecision(4) << scientific;
    ofile << "# z(m), M0(#/m3), M1(kg/m3), ...";

    ofile << endl << setw(14) << zstart;
    for(int k=0; k<nsoot; k++)
        ofile << setw(14) << Mhat[k]*LI_rho(zstart);

    double z = zstart;
    double zh;
    for(int istep = 0; istep < nsteps; istep++, z+=dz) {

        yGas = {LI_yO2(z), LI_yO(z), LI_yH2(z), LI_yH(z), LI_yOH(z), LI_yH2O(z), LI_yCO(z), LI_yC2H2(z)};
        for(int i=0; i<nsoot; i++)
            M[i] = Mhat[i]*LI_rho(z);
        TV[0] = TVhat[0]*LI_rho(z);
        S.setState(LI_T(z), P, LI_rho(z), LI_mu(z), yGas, yPAH, M, nsoot, TV, Ntar);
        S.get_mtar_ytar();
        SM.setSourceTerms(S);

        for(int k=0; k<nsoot; k++)
            Mhath[k] = Mhat[k] + 0.5*dz*SM.sources.sootSources[k]/LI_rho(z)/LI_v(z);
        TVhath[0] = TVhat[0] + 0.5*dz*SM.sources.tarSources[0]/LI_rho(z)/LI_v(z);

        zh = z+dz/2;
        yGas = {LI_yH(zh), LI_yH2(zh), LI_yO(zh), LI_yO2(zh), LI_yOH(zh), LI_yH2O(zh), LI_yCO(zh), LI_yC2H2(zh)};
        for(int i=0; i<nsoot; i++)
            M[i] = Mhath[i]*LI_rho(zh);
        TV[0] = TVhath[0]*LI_rho(zh);
        S.setState(LI_T(zh), P, LI_rho(zh), LI_mu(zh), yGas, yPAH, M, nsoot, TV, Ntar);
        S.get_mtar_ytar();
        SM.setSourceTerms(S);

        for(int k=0; k<nsoot; k++)
            Mhat[k] += dz*SM.sources.sootSources[k]/LI_rho(zh)/LI_v(zh);
        TVhat[0] += dz*SM.sources.tarSources[0]/LI_rho(zh)/LI_v(zh);

        if(istep % 200 == 0) {
            ofile << endl << setw(14) << z+dz;
            for(int k=0; k<nsoot; k++)
                ofile << setw(14) << Mhat[k]*LI_rho(z+dz);
        }

    }
    ofile << endl;
    ofile.close();

    //-----------------

    delete(nucl);
    delete(grow);
    delete(oxid);
    delete(coag);
    delete(tar);

    return 0;
}
