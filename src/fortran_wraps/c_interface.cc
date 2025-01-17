#include "../nucleationModels/nucleationModel.h"
#include "../growthModels/growthModel.h"
#include "../oxidationModels/oxidationModel.h"
#include "../coagulationModels/coagulationModel.h"
#include "../tarModels/tarModel.h"
#include "../sootHeaders.h"
#include "../sootDefs.h"
#include "../../examples/burner_flame/interp_linear.h"
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
    
    soot::nucleationModel *nucleationModel_LINA1_C_interface(){
        return new soot::nucleationModel_LINA1();
    }
    
    soot::nucleationModel *nucleationModel_PAH_C_interface(){
        return new soot::nucleationModel_PAH();
    }
    
    soot::nucleationModel *nucleationModel_MB_C_interface(){
        return new soot::nucleationModel_MB();
    }
    
    soot::nucleationModel *nucleationModel_FAIR_C_interface(){
        return new soot::nucleationModel_FAIR();
    }
    
    soot::nucleationModel *nucleationModel_AJ_RED_C_interface(){
        return new soot::nucleationModel_AJ_RED();
    }

    soot::nucleationModel *nucleationModel_BROWN_C_interface(){
        return new soot::nucleationModel_BROWN();
    }

    soot::nucleationModel *nucleationModel_NONE_C_interface(){
        return new soot::nucleationModel_NONE();
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
    
    soot::growthModel *growthModel_HACA_C_interface(){
        return new soot::growthModel_HACA();
    }

    soot::growthModel *growthModel_MB_C_interface(){
        return new soot::growthModel_MB();
    }

    soot::growthModel *growthModel_FAIR_C_interface(){
        return new soot::growthModel_FAIR();
    }

    soot::growthModel *growthModel_NONE_C_interface(){
        return new soot::growthModel_NONE();
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

    soot::oxidationModel *oxidationModel_LEE_NEOH_C_interface(){
        return new soot::oxidationModel_LEE_NEOH();
    }

    soot::oxidationModel *oxidationModel_NSC_NEOH_C_interface(){
        return new soot::oxidationModel_NSC_NEOH();
    }

    soot::oxidationModel *oxidationModel_HACA_C_interface(){
        return new soot::oxidationModel_HACA();
    }

    soot::oxidationModel *oxidationModel_OPTJ_C_interface(){
        return new soot::oxidationModel_OPTJ();
    }

    soot::oxidationModel *oxidationModel_OPTG_C_interface(){
        return new soot::oxidationModel_OPTG();
    }

    soot::oxidationModel *oxidationModel_MB_C_interface(){
        return new soot::oxidationModel_MB();
    }

    soot::oxidationModel *oxidationModel_FAIR_C_interface(){
        return new soot::oxidationModel_FAIR();
    }
    
    soot::oxidationModel *oxidationModel_AJ_RED_C_interface(){
        return new soot::oxidationModel_AJ_RED();
    }
    
    soot::oxidationModel *oxidationModel_BROWN_C_interface(){
        return new soot::oxidationModel_BROWN();
    }

    soot::oxidationModel *oxidationModel_NONE_C_interface(){
        return new soot::oxidationModel_NONE();
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

    soot::coagulationModel *coagulationModel_CONTINUUM_C_interface(){
        return new soot::coagulationModel_CONTINUUM();
    }

    soot::coagulationModel *coagulationModel_HM_C_interface(){
        return new soot::coagulationModel_HM();
    }

    soot::coagulationModel *coagulationModel_FUCHS_C_interface(){
        return new soot::coagulationModel_FUCHS();
    }

    soot::coagulationModel *coagulationModel_NONE_C_interface(){
        return new soot::coagulationModel_NONE();
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

    soot::tarModel *tarModel_AJ_RED_C_interface(){
        return new soot::tarModel_AJ_RED();
    }

    soot::tarModel *tarModel_BROWN_C_interface(){
        return new soot::tarModel_BROWN();
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
                                                soot::nucleationModel  *nucl_ptr,
                                                soot::growthModel      *grow_ptr,
                                                soot::oxidationModel   *oxid_ptr,
                                                soot::coagulationModel *coag_ptr,
                                                size_t                 Ntar_    = 0,
                                                soot::tarModel         *tar_ptr = new soot::tarModel_NONE){
        return new soot::sootModel_MONO(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, Ntar_, tar_ptr);
    }


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
                                                size_t                 Ntar_    = 0,
                                                soot::tarModel         *tar_ptr = new soot::tarModel_NONE) {
        return new soot::sootModel_QMOM(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, Ntar_, tar_ptr);
    }

    soot::sootModel *sootModel_LOGN_C_interface(size_t                 nsoot_,
                                                soot::nucleationModel  *nucl_ptr,
                                                soot::growthModel      *grow_ptr,
                                                soot::oxidationModel   *oxid_ptr,
                                                soot::coagulationModel *coag_ptr,
                                                size_t                 Ntar_    = 0,
                                                soot::tarModel         *tar_ptr = new soot::tarModel_NONE) {
        return new soot::sootModel_LOGN(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, Ntar_, tar_ptr);
    }

    soot::sootModel *sootModel_MOMIC_C_interface(size_t                 nsoot_,
                                                soot::nucleationModel  *nucl_ptr,
                                                soot::growthModel      *grow_ptr,
                                                soot::oxidationModel   *oxid_ptr,
                                                soot::coagulationModel *coag_ptr,
                                                size_t                    Ntar_ = 0,
                                                soot::tarModel         *tar_ptr = new soot::tarModel_NONE) {
        return new soot::sootModel_MOMIC(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, Ntar_, tar_ptr);
    }

    soot::sootModel *sootModel_SECT_C_interface(size_t                 nsoot_,
                                                soot::nucleationModel  *nucl_ptr,
                                                soot::growthModel      *grow_ptr,
                                                soot::oxidationModel   *oxid_ptr,
                                                soot::coagulationModel *coag_ptr,
                                                size_t                    Ntar_ = 0,
                                                soot::tarModel         *tar_ptr = new soot::tarModel_NONE) {
        return new soot::sootModel_SECT(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, Ntar_, tar_ptr);
    }

    void setSourceTerms_C_interface(soot::sootModel *SM_ptr, soot::state *state_ptr) {
        SM_ptr->setSourceTerms(*state_ptr);
    }

    //----------------------------------------------------------------------------
    //---
    //--- Interface for state functions
    //---
    //----------------------------------------------------------------------------
    soot::state *state_C_interface(size_t nsoot_, size_t Ntar_ = 0){
        return new soot::state(nsoot_, Ntar_);
    }

    void state_delete_C_interface(soot::state *state_ptr){
        delete state_ptr;
    }

    void setState_C_interface(soot::state *state_ptr, double T_, double P_, 
                              double rhoGas_, double muGas_,
                              const double* yGas_, const double* yPAH_,
                              const double* sootVar_, int nsoot_ = 2, 
                              const double* tarVar_ = 0, int Ntar_ = 0, double cMin_ = 100.0){
        std::vector<double> yGas(yGas_, yGas_ + 10);
        std::vector<double> yPAH(yPAH_, yPAH_ + 6);
        std::vector<double> sootVar(sootVar_, sootVar_ + nsoot_);
        std::vector<double> tarVar(tarVar_, tarVar_ + Ntar_);
        state_ptr->setState(T_, P_, rhoGas_, muGas_, 
                            yGas, yPAH, sootVar, nsoot_, tarVar, Ntar_);
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
    
    /*double get_yTar_interface(soot::state *state_ptr, soot::tarSp sp) {
        return state_ptr->yTar[(int)sp];
    }*/

    double get_SootVar_interface(soot::state *state_ptr, int i) {
        return state_ptr->sootVar[i];
    }

    void getSootSources_interface(double *source, soot::sootModel *SM_ptr, int nsoot_) {
        //vector<double> source(nsoot_, 0.0);
        for (int i=0; i<nsoot_; i++) {
            source[i] = SM_ptr->sources.sootSources[i];
        }
        //cout<< SM_ptr->sources.sootSources[i-1] << endl;
    }

}

