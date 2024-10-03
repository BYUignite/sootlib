#include "../nucleationModels/nucleationModel.h"
#include "../growthModels/growthModel.h"
#include "../oxidationModels/oxidationModel.h"
#include "../coagulationModels/coagulationModel.h"
#include "../tarModels/tarModel.h"
#include "../sootHeaders.h"
#include "../sootDefs.h"
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

    soot::sootModel *sootModel_MONO_C_interface(size_t                 nsoot_,
                                                size_t                 Ntar_,
                                                soot::nucleationModel  *nucl_ptr,
                                                soot::growthModel      *grow_ptr,
                                                soot::oxidationModel   *oxid_ptr,
                                                soot::coagulationModel *coag_ptr,
                                                soot::tarModel         *tar_ptr){
        return new soot::sootModel_MONO(nsoot_, Ntar_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr);
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
                                                size_t                 Ntar_,
                                                soot::nucleationModel  *nucl_ptr,
                                                soot::growthModel      *grow_ptr,
                                                soot::oxidationModel   *oxid_ptr,
                                                soot::coagulationModel *coag_ptr,
                                                soot::tarModel         *tar_ptr) {
        return new soot::sootModel_QMOM(nsoot_, Ntar_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr);
    }

    /*soot::sourceTerms sourceTerms_C_interface(size_t nsoot_, size_t Ntar_) {
        return soot::sourceTerms(nsoot_, Ntar_);
    }*/

    void setSourceTerms_C_interface(soot::sootModel *SM_ptr, soot::state *state_ptr) {
        cout << "Made it to setSourceTerms_C_interface" << endl;
        //cout << SM_ptr->sources.sootSources[0] << endl;
        //cout << state_ptr->T << endl;
        SM_ptr->setSourceTerms(*state_ptr);
    }

    //----------------------------------------------------------------------------
    //---
    //--- Interface for state functions
    //---
    //----------------------------------------------------------------------------
    soot::state *state_C_interface(size_t nsoot_, size_t Ntar_){
        return new soot::state(nsoot_, Ntar_);
    }

    void state_delete_C_interface(soot::state *state_ptr){
        delete state_ptr;
    }

    void setState_C_interface(soot::state *state_ptr, double T_, double P_, 
                              double rhoGas_, double muGas_,
                              const double* yGas_, const double* yPAH_,
                              const double* yTar_, const double* yBio_, const double* sootVar_, 
                              const double* tarVar_, int nsoot_, int Ntar_, double cMin_ = 100.0){
        std::vector<double> yGas(yGas_, yGas_ + 10);
        std::vector<double> yPAH(yPAH_, yPAH_ + 6);
        std::vector<double> yTar(yTar_, yTar_ + 4);
        std::vector<double> yBio(yBio_, yBio_ + 5);
        std::vector<double> sootVar(sootVar_, sootVar_ + nsoot_);
        std::vector<double> tarVar(tarVar_, tarVar_ + Ntar_);
        state_ptr->setState(T_, P_, rhoGas_, muGas_, 
                            yGas, yPAH, yTar, yBio, sootVar, tarVar, nsoot_, Ntar_);
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

    double get_T_interface(soot::state *state_ptr) {
        cout << state_ptr->T << endl;
        return state_ptr->T;
    }

    double get_rhoGas_interface(soot::state *state_ptr) {
        return state_ptr->rhoGas;
    }

    double get_yGas_interface(soot::state *state_ptr, soot::gasSp sp) {
        return state_ptr->yGas[(int)sp];
    }

    double get_yPAH_interface(soot::state *state_ptr, soot::pahSp sp) {
        return state_ptr->yPah[(int)sp];
    }
    
    double get_yTar_interface(soot::state *state_ptr, soot::tarSp sp) {
        return state_ptr->yTar[(int)sp];
    }

    double get_yBio_interface(soot::state *state_ptr, soot::bioSp sp) {
        return state_ptr->yBio[(int)sp];
    }

    double get_SootVar_interface(soot::state *state_ptr, int i) {
        return state_ptr->sootVar[i];
    }

    double get_TarVar_interface(soot::state *state_ptr, int i) {
        return state_ptr->tarVar[i];
    }


}

