#include "../nucleationModels/nucleationModel.h"
#include "../growthModels/growthModel.h"
#include "../oxidationModels/oxidationModel.h"
#include "../coagulationModels/coagulationModel.h"
#include "../tarModels/tarModel.h"
#include "../sootHeaders.h"
#include <vector>
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////

extern "C" {

    //------------------------------------------------------------------------------
    //---
    //--- Interface for nucleation models
    //---
    //------------------------------------------------------------------------------

    soot::nucleationModel *nucleationModel_LL_C_interface(){
        return new soot::nucleationModel_LL();
    }

    soot::nucleationModel *nucleationModel_LIN_C_interface(){
        return new soot::nucleationModel_LIN();
    }

    double getNucleationSootRate_C_interface(soot::nucleationModel *nucl_ptr,
                                             soot::state &state){

        return nucl_ptr->getNucleationSootRate(state);
    }

    void getNucleationGasRates_C_interface(soot::nucleationModel *nucl_ptr,
                                           const double &msootDotNucl,
                                           std::vector<double> &gasSourcesNucl){
        nucl_ptr->getNucleationGasRates(msootDotNucl, gasSourcesNucl);
    }

    void nucleation_delete_C_interface(soot::nucleationModel *nucl_ptr){
        delete nucl_ptr;
    }

    //------------------------------------------------------------------------------
    //---
    //--- Interface for growth models
    //---
    //------------------------------------------------------------------------------

    soot::growthModel *growthModel_LL_C_interface(){
        return new soot::growthModel_LL();
    }

    soot::growthModel *growthModel_LIN_C_interface(){
        return new soot::growthModel_LIN();
    }

    double getGrowthSootRate_C_interface(soot::growthModel *grow_ptr,
                                         soot::state &state){

        return grow_ptr->getGrowthSootRate(state);
    }

    void getGrowthGasRates_C_interface(soot::growthModel *grow_ptr,
                                       const double &msootDotGrow,
                                       std::vector<double> &gasSourcesGrow){
        grow_ptr->getGrowthGasRates(msootDotGrow, gasSourcesGrow);
    }
    void growth_delete_C_interface(soot::growthModel *grow_ptr){
        delete grow_ptr;
    }

    //------------------------------------------------------------------------------
    //---
    //--- Interface for oxidation models
    //---
    //------------------------------------------------------------------------------

    soot::oxidationModel *oxidationModel_LL_C_interface(){
        return new soot::oxidationModel_LL();
    }

    double getOxidationSootRate_C_interface(soot::oxidationModel *oxid_ptr,
                                            soot::state &state){

        return oxid_ptr->getOxidationSootRate(state);
    }

    void getOxidationGasRates_C_interface(soot::oxidationModel *oxid_ptr,
                                          const double &msootDotOxid,
                                          std::vector<double> &gasSourcesOxid){
        oxid_ptr->getOxidationGasRates(msootDotOxid, gasSourcesOxid);
    }
    void oxid_delete_C_interface(soot::oxidationModel *oxid_ptr){
        delete oxid_ptr;
    }

    //------------------------------------------------------------------------------
    //---
    //--- Interface for coagulation models
    //---
    //------------------------------------------------------------------------------

    soot::coagulationModel *coagulationModel_FM_C_interface(){
        return new soot::coagulationModel_FM();
    }

    double getCoagulationSootRate_C_interface(soot::coagulationModel *coag_ptr,
                                              soot::state &state,
                                              double m1, double m2){
        return coag_ptr->getCoagulationSootRate(state, m1, m2);
    }

    void set_FM_multiplier_C_interface(soot::coagulationModel *coag_ptr, 
                                       double FM_multiplier_) {
        coag_ptr->set_FM_multiplier(FM_multiplier_);
    }


    void coag_delete_C_interface(soot::coagulationModel *coag_ptr){
        delete coag_ptr;
    }

    //------------------------------------------------------------------------------
    //---
    //--- Interface for tar models 
    //---
    //---------------------------------:w------------------------------------------------------------------------------------------

    soot::tarModel *tarModel_NONE_C_interface(){
        return new soot::tarModel_NONE();
    }

    void tar_delete_C_interface(soot::tarModel *tar_ptr) {
        delete tar_ptr;
    }

    //------------------------------------------------------------------------------
    //---
    //--- Interface for soot models
    //---
    //------------------------------------------------------------------------------

    soot::sootModel *sootModel_MONO_C_interface(int                 nsoot_,
                                                soot::nucleationModel  *nucl_ptr,
                                                soot::growthModel      *grow_ptr,
                                                soot::oxidationModel   *oxid_ptr,
                                                soot::coagulationModel *coag_ptr,
                                                soot::tarModel         *tar_ptr){
        return new soot::sootModel_MONO(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr);
    }

    //void sootModel_delete_C_interface(soot::sootModel *SM_ptr){
    //    delete SM_ptr;
    //}

    void sootModel_delete_C_interface(soot::sootModel *SM_ptr, soot::nucleationModel *nucl_ptr, soot::growthModel *grow_ptr,
                                 soot::oxidationModel *oxid_ptr, soot::coagulationModel *coag_ptr, soot::tarModel *tar_ptr){
        delete SM_ptr;
        delete nucl_ptr;
        delete grow_ptr;
        delete oxid_ptr;
        delete coag_ptr;
        delete tar_ptr;
    }
    
    soot::sootModel *sootModel_QMOM_C_interface(size_t                 nsoot_,
                                                soot::nucleationModel  *nucl_ptr,
                                                soot::growthModel      *grow_ptr,
                                                soot::oxidationModel   *oxid_ptr,
                                                soot::coagulationModel *coag_ptr,
                                                soot::tarModel         *tar_ptr){
        return new soot::sootModel_QMOM(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr);
    }

    void setSourceTerms_C_interface(soot::sootModel *SM_ptr, soot::state &state){
        cout << "Made it to setSourceTerms_C_interface" << endl;
        SM_ptr->setSourceTerms(state);
    }

    /*void setSourceTerms_C_interface(soot::sootModel *SM_ptr, soot::state &state, size_t nsoot_){
        cout << "Made it to setSourceTerms_C_interface" << endl;
        (soot::sourceTerms(nsoot_));
        SM_ptr->setSourceTerms(state);
        cout << "Finished the function call" << endl;
    }*/

    //----------------------------------------------------------------------------
    //---
    //--- Interface for state functions
    //---
    //----------------------------------------------------------------------------
    soot::state *state_C_interface(size_t nsoot_){
        return new soot::state(nsoot_);
    }

    void state_delete_C_interface(soot::state *state_ptr){
        delete state_ptr;
    }

    /*void setState_C_interface(soot::state *state_ptr, double T_, double P_, 
                              double rhoGas_, double muGas_,
                              std::vector<double> &yGas_, std::vector<double> &yPAH_,
                              std::vector<double> &sootVar_, int nsoot_, double cMin_ = 100.0){
        cout << "Here" << endl;
        cout << nsoot_ << endl;
        cout << yGas_.size() << endl;
        state_ptr->setState(T_, P_, rhoGas_, muGas_, 
                            yGas_, yPAH_, sootVar_, nsoot_);
    }*/

    void setState_C_interface(soot::state *state_ptr, double T_, double P_, 
                              double rhoGas_, double muGas_, double Ntar_,
                              const double* yGas_, const double* yPAH_,
                              const double* yTar_, const double* yBio_,
                              const double* sootVar_, int nsoot_, double cMin_ = 100.0){
        std::vector<double> yGas(yGas_, yGas_ + 10);
        std::vector<double> yPAH(yPAH_, yPAH_ + 6);
        std::vector<double> yTar(yTar_, yTar_ + 4);
        std::vector<double> yBio(yBio_, yBio_ + 5);
        std::vector<double> sootVar(sootVar_, sootVar_ + nsoot_);
        state_ptr->setState(T_, P_, rhoGas_, muGas_, Ntar_, 
                            yGas, yPAH, yTar, yBio, sootVar, nsoot_);
    }
    double getGasSpC_C_interface(soot::state *state_ptr, soot::gasSp sp){
        return state_ptr->getGasSpC(soot::gasSp(sp));
    }

    double getGasSpP_C_interface(soot::state *state_ptr, soot::gasSp sp){
        return state_ptr->getGasSpP(soot::gasSp(sp));
    }

    double getGasMeanFreePath_C_interface(soot::state *state_ptr){
        return state_ptr->getGasMeanFreePath();
    }

    double get_pahSpC_C_interface(soot::state *state_ptr, soot::pahSp sp){
        return state_ptr->get_pahSpC(soot::pahSp(sp));
    }

    double get_pahSpP_C_interface(soot::state *state_ptr, soot::pahSp sp){
        return state_ptr->get_pahSpP(soot::pahSp(sp));
    }

    void setSootScales_C_interface(soot::state *state_ptr, std::vector<double> &sootScales_){
        state_ptr->setSootScales(sootScales_);
    }

}

