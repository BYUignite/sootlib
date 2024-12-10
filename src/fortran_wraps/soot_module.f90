module soot_module

    use, intrinsic :: ISO_C_Binding, only: C_int, C_double, C_ptr, C_NULL_ptr, C_char

    implicit none

    private

    !============================================================================
    ! declare the C interface

    interface

        !---------------------- Nucleation Models -------------------------------

        function nucleationModel_LL_C_interface() result(nucl_ptr) bind(C, name="nucleationModel_LL_C_interface")
            import
            type(C_ptr) :: nucl_ptr
        end function nucleationModel_LL_C_interface

        !------------------------------------------------------------------------

        function nucleationModel_LIN_C_interface() result(nucl_ptr) bind(C, name="nucleationModel_LIN_C_interface")
            import
            type(C_ptr) :: nucl_ptr
        end function nucleationModel_LIN_C_interface

        !------------------------------------------------------------------------

        function nucleationModel_LINA1_C_interface() result(nucl_ptr) bind(C, name="nucleationModel_LINA1_C_interface")
            import
            type(C_ptr) :: nucl_ptr
        end function nucleationModel_LINA1_C_interface

        !------------------------------------------------------------------------

        function nucleationModel_PAH_C_interface() result(nucl_ptr) bind(C, name="nucleationModel_PAH_C_interface")
            import
            type(C_ptr) :: nucl_ptr
        end function nucleationModel_PAH_C_interface

        !------------------------------------------------------------------------

        function nucleationModel_MB_C_interface() result(nucl_ptr) bind(C, name="nucleationModel_MB_C_interface")
            import
            type(C_ptr) :: nucl_ptr
        end function nucleationModel_MB_C_interface

        !------------------------------------------------------------------------

        function nucleationModel_FAIR_C_interface() result(nucl_ptr) bind(C, name="nucleationModel_FAIR_C_interface")
            import
            type(C_ptr) :: nucl_ptr
        end function nucleationModel_FAIR_C_interface

        !------------------------------------------------------------------------

        function nucleationModel_NONE_C_interface() result(nucl_ptr) bind(C, name="nucleationModel_NONE_C_interface")
            import
            type(C_ptr) :: nucl_ptr
        end function nucleationModel_NONE_C_interface

        !------------------------------------------------------------------------

        subroutine nucleation_delete_C_interface(nucl_ptr) bind(C, name="nucleation_delete_C_interface")
            import
            type(C_ptr), value :: nucl_ptr
        end subroutine nucleation_delete_C_interface

        !-------------------- Growth Models -------------------------------------

        function growthModel_LL_C_interface() result(grow_ptr) bind(C, name="growthModel_LL_C_interface")
            import
            type(C_ptr) :: grow_ptr
        end function growthModel_LL_C_interface

        !------------------------------------------------------------------------

        function growthModel_LIN_C_interface() result(grow_ptr) bind(C, name="growthModel_LIN_C_interface")
            import
            type(C_ptr) :: grow_ptr
        end function growthModel_LIN_C_interface

        !------------------------------------------------------------------------

        function growthModel_HACA_C_interface() result(grow_ptr) bind(C, name="growthModel_HACA_C_interface")
            import
            type(C_ptr) :: grow_ptr
        end function growthModel_HACA_C_interface

        !------------------------------------------------------------------------

        function growthModel_MB_C_interface() result(grow_ptr) bind(C, name="growthModel_MB_C_interface")
            import
            type(C_ptr) :: grow_ptr
        end function growthModel_MB_C_interface

        !------------------------------------------------------------------------

        function growthModel_FAIR_C_interface() result(grow_ptr) bind(C, name="growthModel_FAIR_C_interface")
            import
            type(C_ptr) :: grow_ptr
        end function growthModel_FAIR_C_interface

        !------------------------------------------------------------------------

        function growthModel_NONE_C_interface() result(grow_ptr) bind(C, name="growthModel_NONE_C_interface")
            import
            type(C_ptr) :: grow_ptr
        end function growthModel_NONE_C_interface

        !------------------------------------------------------------------------

        subroutine growth_delete_C_interface(grow_ptr) bind(C, name="growth_delete_C_interface")
            import
            type(C_ptr), value :: grow_ptr
        end subroutine growth_delete_C_interface

        !-------------------- Oxidation Models ----------------------------------

        function oxidationModel_LL_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_LL_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_LL_C_interface

        !------------------------------------------------------------------------

        function oxidationModel_LEE_NEOH_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_LEE_NEOH_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_LEE_NEOH_C_interface

        !------------------------------------------------------------------------

        function oxidationModel_NSC_NEOH_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_NSC_NEOH_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_NSC_NEOH_C_interface

        !------------------------------------------------------------------------

        function oxidationModel_HACA_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_HACA_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_HACA_C_interface

        !------------------------------------------------------------------------

        function oxidationModel_OPTJ_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_OPTJ_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_OPTJ_C_interface

        !------------------------------------------------------------------------

        function oxidationModel_OPTG_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_OPTG_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_OPTG_C_interface

        !------------------------------------------------------------------------

        function oxidationModel_MB_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_MB_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_MB_C_interface

        !------------------------------------------------------------------------

        function oxidationModel_FAIR_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_FAIR_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_FAIR_C_interface

        !------------------------------------------------------------------------

        function oxidationModel_NONE_C_interface() result(oxid_ptr) bind(C, name="oxidationModel_NONE_C_interface")
            import
            type(C_ptr) :: oxid_ptr
        end function oxidationModel_NONE_C_interface

        !------------------------------------------------------------------------

        subroutine oxid_delete_C_interface(oxid_ptr) bind(C, name="oxid_delete_C_interface")
            import
            type(C_ptr), value :: oxid_ptr
        end subroutine oxid_delete_C_interface

        !-------------------- Coagulation Models --------------------------------

        function coagulationModel_FM_C_interface() result(coag_ptr) bind(C, name="coagulationModel_FM_C_interface")
            import
            type(C_ptr) :: coag_ptr
        end function coagulationModel_FM_C_interface

        !------------------------------------------------------------------------

        function coagulationModel_CONTINUUM_C_interface() result(coag_ptr) bind(C, name="coagulationModel_CONTINUUM_C_interface")
            import
            type(C_ptr) :: coag_ptr
        end function coagulationModel_CONTINUUM_C_interface

        !------------------------------------------------------------------------

        function coagulationModel_HM_C_interface() result(coag_ptr) bind(C, name="coagulationModel_HM_C_interface")
            import
            type(C_ptr) :: coag_ptr
        end function coagulationModel_HM_C_interface

        !------------------------------------------------------------------------

        function coagulationModel_FUCHS_C_interface() result(coag_ptr) bind(C, name="coagulationModel_FUCHS_C_interface")
            import
            type(C_ptr) :: coag_ptr
        end function coagulationModel_FUCHS_C_interface

        !------------------------------------------------------------------------

        function coagulationModel_NONE_C_interface() result(coag_ptr) bind(C, name="coagulationModel_NONE_C_interface")
            import
            type(C_ptr) :: coag_ptr
        end function coagulationModel_NONE_C_interface

        !------------------------------------------------------------------------

        subroutine set_FM_multiplier_C_interface(coag_ptr, FM_multiplier_) &
                bind(C, name="set_FM_multiplier_C_interface")
            import 
            type(C_ptr),    value :: coag_ptr
            real(C_double), value :: FM_multiplier_
        end subroutine set_FM_multiplier_C_interface

        !------------------------------------------------------------------------

        subroutine coag_delete_C_interface(coag_ptr) bind(C, name="coag_delete_C_interface")
            import
            type(C_ptr), value :: coag_ptr
        end subroutine coag_delete_C_interface


        !-------------------- Soot Models ---------------------------------------

        function sootModel_MONO_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr) result(SM_ptr) &
                bind(C, name="sootModel_MONO_C_interface")
            import
            type(C_ptr)           :: SM_ptr
            integer(C_int), value :: nsoot_
            type(C_ptr), value           :: nucl_ptr
            type(C_ptr), value           :: grow_ptr
            type(C_ptr), value           :: oxid_ptr
            type(C_ptr), value           :: coag_ptr
        end function sootModel_MONO_C_interface

        !------------------------------------------------------------------------

        function sootModel_QMOM_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr) result(SM_ptr) &
                bind(C, name="sootModel_QMOM_C_interface")
            import
            type(C_ptr)           :: SM_ptr
            integer(C_int), value :: nsoot_
            type(C_ptr), value           :: nucl_ptr
            type(C_ptr), value           :: grow_ptr
            type(C_ptr), value           :: oxid_ptr
            type(C_ptr), value           :: coag_ptr
        end function sootModel_QMOM_C_interface

        !------------------------------------------------------------------------

        function sootModel_LOGN_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr) result(SM_ptr) &
                bind(C, name="sootModel_LOGN_C_interface")
            import
            type(C_ptr)           :: SM_ptr
            integer(C_int), value :: nsoot_
            type(C_ptr), value           :: nucl_ptr
            type(C_ptr), value           :: grow_ptr
            type(C_ptr), value           :: oxid_ptr
            type(C_ptr), value           :: coag_ptr
        end function sootModel_LOGN_C_interface

        !------------------------------------------------------------------------

        function sootModel_MOMIC_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr) result(SM_ptr) &
                bind(C, name="sootModel_MOMIC_C_interface")
            import
            type(C_ptr)           :: SM_ptr
            integer(C_int), value :: nsoot_
            type(C_ptr), value           :: nucl_ptr
            type(C_ptr), value           :: grow_ptr
            type(C_ptr), value           :: oxid_ptr
            type(C_ptr), value           :: coag_ptr
        end function sootModel_MOMIC_C_interface

        !------------------------------------------------------------------------

        function sootModel_SECT_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr) result(SM_ptr) &
                bind(C, name="sootModel_SECT_C_interface")
            import
            type(C_ptr)           :: SM_ptr
            integer(C_int), value :: nsoot_
            type(C_ptr), value           :: nucl_ptr
            type(C_ptr), value           :: grow_ptr
            type(C_ptr), value           :: oxid_ptr
            type(C_ptr), value           :: coag_ptr
        end function sootModel_SECT_C_interface

        !------------------------------------------------------------------------

        subroutine sootModel_delete_C_interface(SM_ptr, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr) &
                bind(C, name="sootModel_delete_C_interface")
            import
            type(C_ptr), value :: SM_ptr
            type(C_ptr), value :: nucl_ptr 
            type(C_ptr), value :: grow_ptr 
            type(C_ptr), value :: oxid_ptr 
            type(C_ptr), value :: coag_ptr
        end subroutine sootModel_delete_C_interface

        !-------------------- State ---------------------------------------------

        subroutine setSourceTerms_C_interface(SM_ptr, state_ptr) bind(C, name="setSourceTerms_C_interface")
            import
            type(C_ptr), value :: SM_ptr
            type(C_ptr), value :: state_ptr
        end subroutine setSourceTerms_C_interface
        
        !------------------------------------------------------------------------

        function state_C_interface(nsoot_) result(state_ptr) bind(C, name="state_C_interface")
            import
            type(C_ptr)           :: state_ptr
            integer(C_int), value :: nsoot_
        end function state_C_interface

        !------------------------------------------------------------------------

        subroutine state_delete_C_interface(state_ptr) bind(C, name="state_delete_C_interface")
            import
            type(C_ptr), value  :: state_ptr
        end subroutine state_delete_C_interface

        !------------------------------------------------------------------------

        subroutine setState_C_interface(state_ptr, T_, P_, rhoGas_, muGas_, yGas_, yPAH_, &
                                        sootVar_, nsoot_, cMin_) &
                                        bind(C, name="setState_C_interface")
            import
            type(C_ptr),    value        :: state_ptr
            real(C_double), value        :: T_
            real(C_double), value        :: P_
            real(C_double), value        :: rhoGas_
            real(C_double), value        :: muGas_
            real(C_double), dimension(*) :: yGas_
            real(C_double), dimension(*) :: yPAH_
            real(C_double), dimension(*) :: sootVar_
            integer(C_int), value        :: nsoot_
            real(C_double), value        :: cMin_
        end subroutine setState_C_interface

        !------------------------------------------------------------------------

        subroutine getGasSpC_C_interface(state_ptr, sp) bind(C, name="getGasSpC_C_interface")
            import
            type(C_ptr), value :: state_ptr
            type(C_ptr), value :: sp 
        end subroutine getGasSpC_C_interface

        !------------------------------------------------------------------------

        subroutine getGasSpP_C_interface(state_ptr, sp) bind(C, name="getGasSpP_C_interface")
            import
            type(C_ptr), value :: state_ptr
            type(C_ptr), value :: sp 
        end subroutine getGasSpP_C_interface

        !------------------------------------------------------------------------

        subroutine getGasMeanFreePath_C_interface(state_ptr) &
                bind(C, name="getGasMeanFreePath_C_interface")
            import
            type(C_ptr), value :: state_ptr
        end subroutine getGasMeanFreePath_C_interface

        !------------------------------------------------------------------------

        subroutine get_pahSpC_C_interface(state_ptr, sp) bind(C, name="get_pahSpC_C_interface")
            import
            type(C_ptr), value :: state_ptr
            type(C_ptr), value :: sp 
        end subroutine get_pahSpC_C_interface

        !------------------------------------------------------------------------

        subroutine get_pahSpP_C_interface(state_ptr, sp) bind(C, name="get_pahSpP_C_interface")
            import
            type(C_ptr), value :: state_ptr
            type(C_ptr), value :: sp 
        end subroutine get_pahSpP_C_interface

        !------------------------------------------------------------------------

        subroutine setSootScales_C_interface(state_ptr, sootScales_) &
                bind(C, name="setSootScales_C_interface")
            import
            type(C_ptr), value           :: state_ptr
            real(C_double), dimension(*) :: sootScales_
        end subroutine setSootScales_C_interface

        !------------------------------------------------------------------------
        
        subroutine get_T_interface(state_ptr) bind(C, name="get_T_interface")
            import
            type(C_ptr), value :: state_ptr
        end subroutine get_T_interface

        !------------------------------------------------------------------------

        subroutine get_rhoGas_interface(state_ptr) bind(C, name="get_rhoGas_interface")
            import
            type(C_ptr), value :: state_ptr
        end subroutine get_rhoGas_interface

        !------------------------------------------------------------------------

        subroutine get_yGas_interface(state_ptr, sp) bind(C, name="get_yGas_interface")
            import
            type(C_ptr), value :: state_ptr
            character(C_char)  :: sp 
        end subroutine get_yGas_interface

        !------------------------------------------------------------------------
        
        subroutine get_yPAH_interface(state_ptr, sp) bind(C, name="get_yPAH_interface")
            import
            type(C_ptr), value :: state_ptr
            character(C_char)  :: sp 
        end subroutine get_yPAH_interface

        !------------------------------------------------------------------------

        subroutine get_SootVar_interface(state_ptr, i) bind(C, name="get_SootVar_interface")
            import
            type(C_ptr)   , value :: state_ptr
            integer(C_int), value :: i 
        end subroutine get_SootVar_interface
    
        !------------------------------------------------------------------------

        subroutine getSootSources_interface(source, SM_ptr, nsoot_) bind(C, name="getSootSources_interface")
            import
            real(C_double), dimension(*) :: source
            type(C_ptr)   , value        :: SM_ptr
            integer(C_int), value        :: nsoot_
        end subroutine getSootSources_interface

        !------------------------------------------------------------------------

        subroutine getGasSources_interface(source, SM_ptr) bind(C, name="getGasSources_interface")
            import
            real(C_double), dimension(*) :: source
            type(C_ptr)   , value        :: SM_ptr
        end subroutine getGasSources_interface
    
    end interface

        !-------------------- Continue as needed for interface functions --------

    public :: nucleationModel_LL, nucleationModel_LIN, growthModel_LL, growthModel_LIN, nucleation_delete, &
        growth_delete, oxidationModel_LL, oxid_delete, coagulationModel_FM, set_FM_multiplier, coag_delete, &
        sootModel_MONO, sootModel_delete, sootModel_QMOM, setSourceTerms, state, state_delete, setState, &
        getGasSpC, getGasSpP, getGasMeanFreePath, get_pahSpC, get_pahSpP, setSootScales, get_T, get_rhoGas, &
        get_yGas, get_yPAH, get_SootVar, getSootSources, nucleationModel_LINA1, &
        nucleationModel_MB, nucleationModel_PAH, nucleationModel_FAIR, nucleationModel_NONE, &
        growthModel_HACA, growthModel_MB, growthModel_FAIR, growthModel_NONE, oxidationModel_LEE_NEOH, oxidationModel_NSC_NEOH, &
        oxidationModel_HACA, oxidationModel_OPTJ, oxidationModel_OPTG, oxidationModel_MB, oxidationModel_FAIR, &
        oxidationModel_NONE, coagulationModel_CONTINUUM, coagulationModel_HM, coagulationModel_FUCHS, &
        coagulationModel_NONE, sootModel_LOGN, sootModel_MOMIC, sootModel_SECT, getGasSources

    !============================================================================
    ! set fortran wrapper routines to the C interface functions

    contains

        !------------------------------------------------------------------------

        subroutine nucleationModel_LL(nucl_ptr)
            type(C_ptr), intent(out) :: nucl_ptr
            nucl_ptr = nucleationModel_LL_C_interface()
        end subroutine nucleationModel_LL

        !------------------------------------------------------------------------

        subroutine nucleationModel_LIN(nucl_ptr)
            type(C_ptr), intent(out) :: nucl_ptr
            nucl_ptr = nucleationModel_LIN_C_interface()
        end subroutine nucleationModel_LIN

        !------------------------------------------------------------------------

        subroutine nucleationModel_LINA1(nucl_ptr)
            type(C_ptr), intent(out) :: nucl_ptr
            nucl_ptr = nucleationModel_LINA1_C_interface()
        end subroutine nucleationModel_LINA1

        !------------------------------------------------------------------------

        subroutine nucleationModel_PAH(nucl_ptr)
            type(C_ptr), intent(out) :: nucl_ptr
            nucl_ptr = nucleationModel_PAH_C_interface()
        end subroutine nucleationModel_PAH

        !------------------------------------------------------------------------

        subroutine nucleationModel_MB(nucl_ptr)
            type(C_ptr), intent(out) :: nucl_ptr
            nucl_ptr = nucleationModel_MB_C_interface()
        end subroutine nucleationModel_MB

        !------------------------------------------------------------------------

        subroutine nucleationModel_FAIR(nucl_ptr)
            type(C_ptr), intent(out) :: nucl_ptr
            nucl_ptr = nucleationModel_FAIR_C_interface()
        end subroutine nucleationModel_FAIR

        !------------------------------------------------------------------------

        subroutine nucleationModel_NONE(nucl_ptr)
            type(C_ptr), intent(out) :: nucl_ptr
            nucl_ptr = nucleationModel_NONE_C_interface()
        end subroutine nucleationModel_NONE

        !------------------------------------------------------------------------

        subroutine nucleation_delete(nucl_ptr)
            type(C_ptr), intent(inout) :: nucl_ptr
            call nucleation_delete_C_interface(nucl_ptr)
            nucl_ptr = C_NULL_ptr
        end subroutine nucleation_delete

        !------------------------------------------------------------------------

        subroutine growthModel_LL(grow_ptr)
            type(C_ptr), intent(out) :: grow_ptr
            grow_ptr = growthModel_LL_C_interface()
        end subroutine growthModel_LL

        !------------------------------------------------------------------------

        subroutine growthModel_LIN(grow_ptr)
            type(C_ptr), intent(out) :: grow_ptr
            grow_ptr = growthModel_LIN_C_interface()
        end subroutine growthModel_LIN

        !------------------------------------------------------------------------

        subroutine growthModel_HACA(grow_ptr)
            type(C_ptr), intent(out) :: grow_ptr
            grow_ptr = growthModel_HACA_C_interface()
        end subroutine growthModel_HACA

        !------------------------------------------------------------------------

        subroutine growthModel_MB(grow_ptr)
            type(C_ptr), intent(out) :: grow_ptr
            grow_ptr = growthModel_MB_C_interface()
        end subroutine growthModel_MB

        !------------------------------------------------------------------------

        subroutine growthModel_FAIR(grow_ptr)
            type(C_ptr), intent(out) :: grow_ptr
            grow_ptr = growthModel_FAIR_C_interface()
        end subroutine growthModel_FAIR

        !------------------------------------------------------------------------

        subroutine growthModel_NONE(grow_ptr)
            type(C_ptr), intent(out) :: grow_ptr
            grow_ptr = growthModel_NONE_C_interface()
        end subroutine growthModel_NONE

        !------------------------------------------------------------------------

        subroutine growth_delete(grow_ptr)
            type(C_ptr), intent(inout) :: grow_ptr
            call growth_delete_C_interface(grow_ptr)
            grow_ptr = C_NULL_ptr
        end subroutine growth_delete

        !------------------------------------------------------------------------

        subroutine oxidationModel_LL(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_LL_C_interface()
        end subroutine oxidationModel_LL

        !------------------------------------------------------------------------

        subroutine oxidationModel_LEE_NEOH(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_LEE_NEOH_C_interface()
        end subroutine oxidationModel_LEE_NEOH

        !------------------------------------------------------------------------

        subroutine oxidationModel_NSC_NEOH(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_NSC_NEOH_C_interface()
        end subroutine oxidationModel_NSC_NEOH

        !------------------------------------------------------------------------

        subroutine oxidationModel_HACA(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_HACA_C_interface()
        end subroutine oxidationModel_HACA

        !------------------------------------------------------------------------

        subroutine oxidationModel_OPTJ(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_OPTJ_C_interface()
        end subroutine oxidationModel_OPTJ

        !------------------------------------------------------------------------

        subroutine oxidationModel_OPTG(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_OPTG_C_interface()
        end subroutine oxidationModel_OPTG

        !------------------------------------------------------------------------

        subroutine oxidationModel_MB(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_MB_C_interface()
        end subroutine oxidationModel_MB

        !------------------------------------------------------------------------

        subroutine oxidationModel_FAIR(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_FAIR_C_interface()
        end subroutine oxidationModel_FAIR

        !------------------------------------------------------------------------


        subroutine oxidationModel_NONE(oxid_ptr)
            type(C_ptr), intent(out) :: oxid_ptr
            oxid_ptr = oxidationModel_NONE_C_interface()
        end subroutine oxidationModel_NONE

        !------------------------------------------------------------------------

        subroutine oxid_delete(oxid_ptr)
            type(C_ptr), intent(inout) :: oxid_ptr
            call oxid_delete_C_interface(oxid_ptr)
            oxid_ptr = C_NULL_ptr
        end subroutine oxid_delete

        !------------------------------------------------------------------------

        subroutine coagulationModel_FM(coag_ptr)
            type(C_ptr), intent(out)   :: coag_ptr
            coag_ptr = coagulationModel_FM_C_interface()
        end subroutine coagulationModel_FM

        !------------------------------------------------------------------------

        subroutine coagulationModel_CONTINUUM(coag_ptr)
            type(C_ptr), intent(out)   :: coag_ptr
            coag_ptr = coagulationModel_CONTINUUM_C_interface()
        end subroutine coagulationModel_CONTINUUM

        !------------------------------------------------------------------------

        subroutine coagulationModel_HM(coag_ptr)
            type(C_ptr), intent(out)   :: coag_ptr
            coag_ptr = coagulationModel_HM_C_interface()
        end subroutine coagulationModel_HM

        !------------------------------------------------------------------------

        subroutine coagulationModel_FUCHS(coag_ptr)
            type(C_ptr), intent(out)   :: coag_ptr
            coag_ptr = coagulationModel_FUCHS_C_interface()
        end subroutine coagulationModel_FUCHS

        !------------------------------------------------------------------------

        subroutine coagulationModel_NONE(coag_ptr)
            type(C_ptr), intent(out)   :: coag_ptr
            coag_ptr = coagulationModel_NONE_C_interface()
        end subroutine coagulationModel_NONE

        !------------------------------------------------------------------------

        subroutine set_FM_multiplier(coag_ptr, FM_multiplier_)
            type(C_ptr)     , intent(in) :: coag_ptr
            double precision, intent(in) :: FM_multiplier_

            call set_FM_multiplier_C_interface(coag_ptr, FM_multiplier_)
        end subroutine set_FM_multiplier

        !------------------------------------------------------------------------

        subroutine coag_delete(coag_ptr)
            type(C_ptr), intent(inout) :: coag_ptr
            call coag_delete_C_interface(coag_ptr)
            coag_ptr = C_NULL_ptr
        end subroutine coag_delete

        !------------------------------------------------------------------------

        subroutine sootModel_MONO(SM_ptr, nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            integer(4),  intent(in)  :: nsoot_
            type(C_ptr), intent(in)  :: nucl_ptr
            type(C_ptr), intent(in)  :: grow_ptr
            type(C_ptr), intent(in)  :: oxid_ptr
            type(C_ptr), intent(in)  :: coag_ptr

            SM_ptr = sootModel_MONO_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
        end subroutine sootModel_MONO

        !------------------------------------------------------------------------

        subroutine sootModel_delete(SM_ptr, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
            type(C_ptr), intent(inout) :: SM_ptr
            type(C_ptr), intent(inout) :: nucl_ptr
            type(C_ptr), intent(inout) :: grow_ptr
            type(C_ptr), intent(inout) :: oxid_ptr
            type(C_ptr), intent(inout) :: coag_ptr
            
            call sootModel_delete_C_interface(SM_ptr, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
            SM_ptr   = C_NULL_ptr
            nucl_ptr = C_NULL_ptr
            grow_ptr = C_NULL_ptr
            oxid_ptr = C_NULL_ptr
            coag_ptr = C_NULL_ptr

        end subroutine sootModel_delete

        !------------------------------------------------------------------------

        subroutine sootModel_QMOM(SM_ptr, nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            integer    , intent(in)  :: nsoot_
            type(C_ptr), intent(in)  :: nucl_ptr
            type(C_ptr), intent(in)  :: grow_ptr
            type(C_ptr), intent(in)  :: oxid_ptr
            type(C_ptr), intent(in)  :: coag_ptr

            SM_ptr = sootModel_QMOM_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
        end subroutine sootModel_QMOM

        !------------------------------------------------------------------------

        subroutine sootModel_LOGN(SM_ptr, nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            integer    , intent(in)  :: nsoot_
            type(C_ptr), intent(in)  :: nucl_ptr
            type(C_ptr), intent(in)  :: grow_ptr
            type(C_ptr), intent(in)  :: oxid_ptr
            type(C_ptr), intent(in)  :: coag_ptr

            SM_ptr = sootModel_LOGN_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
        end subroutine sootModel_LOGN

        !------------------------------------------------------------------------

        subroutine sootModel_MOMIC(SM_ptr, nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            integer    , intent(in)  :: nsoot_
            type(C_ptr), intent(in)  :: nucl_ptr
            type(C_ptr), intent(in)  :: grow_ptr
            type(C_ptr), intent(in)  :: oxid_ptr
            type(C_ptr), intent(in)  :: coag_ptr

            SM_ptr = sootModel_MOMIC_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
        end subroutine sootModel_MOMIC

        !------------------------------------------------------------------------

        subroutine sootModel_SECT(SM_ptr, nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            integer    , intent(in)  :: nsoot_
            type(C_ptr), intent(in)  :: nucl_ptr
            type(C_ptr), intent(in)  :: grow_ptr
            type(C_ptr), intent(in)  :: oxid_ptr
            type(C_ptr), intent(in)  :: coag_ptr

            SM_ptr = sootModel_SECT_C_interface(nsoot_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr)
        end subroutine sootModel_SECT

        !------------------------------------------------------------------------
        
        subroutine state(state_ptr, nsoot_)
            type(C_ptr), intent(out)   :: state_ptr
            integer    , intent(in)    :: nsoot_

            state_ptr = state_C_interface(nsoot_)
        end subroutine state

        !------------------------------------------------------------------------

        subroutine state_delete(state_ptr)
            type(C_ptr), intent(inout) :: state_ptr
            call state_delete_C_interface(state_ptr)
            state_ptr = C_NULL_ptr
        end subroutine state_delete

        !------------------------------------------------------------------------

        subroutine setState(state_ptr, T_, P_, rhoGas_, muGas_, yGas_, yPAH_, &
                            sootVar_, nsoot_, cMin_)
            type(C_ptr)     , intent(in)               :: state_ptr
            double precision, intent(in)               :: T_
            double precision, intent(in)               :: P_
            double precision, intent(in)               :: rhoGas_
            double precision, intent(in)               :: muGas_
            double precision, intent(in), dimension(:) :: yGas_
            double precision, intent(in), dimension(:) :: yPAH_
            double precision, intent(in), dimension(:) :: sootVar_
            integer         , intent(in)               :: nsoot_
            double precision, intent(in)               :: cMin_

            call setState_C_interface(state_ptr, T_, P_, rhoGas_, muGas_, yGas_, yPAH_, &
                                      sootVar_, nsoot_, cMin_)
        end subroutine setState

        !------------------------------------------------------------------------

        subroutine setSourceTerms(SM_ptr, state_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            type(C_ptr), intent(in)  :: state_ptr

            call setSourceTerms_C_interface(SM_ptr, state_ptr)
        end subroutine setSourceTerms
        
        !------------------------------------------------------------------------

        subroutine getGasSpC(state_ptr, sp)
            type(C_ptr), intent(out) :: state_ptr
            type(C_ptr), intent(in)  :: sp

            call getGasSpC_C_interface(state_ptr, sp)
        end subroutine getGasSpC

        !------------------------------------------------------------------------

        subroutine getGasSpP(state_ptr, sp)
            type(C_ptr), intent(out) :: state_ptr
            type(C_ptr), intent(in)  :: sp 

            call getGasSpP_C_interface(state_ptr, sp)
        end subroutine getGasSpP

        !------------------------------------------------------------------------

        subroutine getGasMeanFreePath(state_ptr)
            type(C_ptr), intent(out) :: state_ptr
            call getGasMeanFreePath_C_interface(state_ptr)
        end subroutine getGasMeanFreePath

        !------------------------------------------------------------------------

        subroutine get_pahSpC(state_ptr, sp)
            type(C_ptr), intent(out) :: state_ptr
            type(C_ptr), intent(in)  :: sp 
            call get_pahSpC_C_interface(state_ptr, sp)
        end subroutine get_pahSpC

        !------------------------------------------------------------------------

        subroutine get_pahSpP(state_ptr, sp)
            type(C_ptr), intent(out) :: state_ptr
            type(C_ptr), intent(in)  :: sp 
            call get_pahSpP_C_interface(state_ptr, sp)
        end subroutine get_pahSpP

        !------------------------------------------------------------------------

        subroutine setSootScales(state_ptr, sootScales_)
            type(C_ptr)     , intent(out)               :: state_ptr
            double precision, intent(in) , dimension(:) :: sootScales_
            call setSootScales_C_interface(state_ptr, sootScales_)
        end subroutine setSootScales

        !------------------------------------------------------------------------

        subroutine get_T(state_ptr)
            type(C_ptr), intent(in) :: state_ptr
            call get_T_interface(state_ptr)
        end subroutine get_T

        !------------------------------------------------------------------------

        subroutine get_rhoGas(state_ptr)
            type(C_ptr), intent(in) :: state_ptr
            call get_rhoGas_interface(state_ptr)
        end subroutine get_rhoGas

        !------------------------------------------------------------------------

        subroutine get_yGas(state_ptr, sp)
            type(C_ptr), intent(in) :: state_ptr
            character, intent(in) :: sp 
            call get_yGas_interface(state_ptr, sp)
        end subroutine get_yGas

        !------------------------------------------------------------------------

        subroutine get_yPAH(state_ptr, sp)
            type(C_ptr), intent(in) :: state_ptr
            character, intent(in) :: sp 
            call get_yPAH_interface(state_ptr, sp)
        end subroutine get_yPAH

        !------------------------------------------------------------------------

        subroutine get_SootVar(state_ptr, i)
            type(C_ptr), intent(in) :: state_ptr
            integer    , intent(in) :: i
            call get_SootVar_interface(state_ptr, i)
        end subroutine get_SootVar

        !------------------------------------------------------------------------

        subroutine getSootSources(source, SM_ptr, nsoot_)
            double precision, intent(out), dimension(:)        :: source 
            type(C_ptr)     , intent(in)                       :: SM_ptr
            integer         , intent(in)                       :: nsoot_

            !source = getSootSources_interface(SM_ptr, nsoot_)
            call getSootSources_interface(source, SM_ptr, nsoot_)
        end subroutine getSootSources

        !------------------------------------------------------------------------

        subroutine getGasSources(source, SM_ptr)
            double precision, intent(out), dimension(:) :: source
            type(C_ptr)     , intent(in)                :: SM_ptr

            call getGasSources_interface(source, SM_ptr)
        end subroutine getGasSources

    !============================================================================

end module soot_module
