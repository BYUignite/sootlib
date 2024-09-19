module soot_module

    use, intrinsic :: ISO_C_Binding, only: C_int, C_double, C_ptr, C_NULL_ptr

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

        subroutine getNucleationSootRate_C_interface(nucl_ptr, state) &
                bind(C, name="getNucleationSootRate_C_interface")
            import
            type(C_ptr), value     :: nucl_ptr
            type(C_ptr), value     :: state
        end subroutine getNucleationSootRate_C_interface

        !------------------------------------------------------------------------

        subroutine getNucleationGasRates_C_interface(nucl_ptr, msootDotNucl, gasSourcesNucl) &
                bind(C, name="getNucleationGasRates_C_interface")
            import
            type(C_ptr), value           :: nucl_ptr
            real(C_double)               :: msootDotNucl
            real(C_double), dimension(*) :: gasSourcesNucl
        end subroutine getNucleationGasRates_C_interface

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

        subroutine getGrowthSootRate_C_interface(grow_ptr, state) &
                bind(C, name="getGrowthSootRate_C_interface")
            import
            type(C_ptr), value :: grow_ptr
            type(C_ptr), value :: state
        end subroutine getGrowthSootRate_C_interface

        !------------------------------------------------------------------------

        subroutine getGrowthGasRates_C_interface(grow_ptr, msootDotGrow, gasSourcesGrow) &
                bind(C, name="getGrowthGasRates_C_interface")
            import
            type(C_ptr), value           :: grow_ptr
            real(C_double), value        :: msootDotGrow
            real(C_double), dimension(*) :: gasSourcesGrow
        end subroutine getGrowthGasRates_C_interface

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

        subroutine getOxidationSootRate_C_interface(oxid_ptr, state) &
                bind(C, name="getOxidationSootRate_C_interface")
            import
            type(C_ptr), value :: oxid_ptr
            type(C_ptr), value :: state
        end subroutine getOxidationSootRate_C_interface

        !------------------------------------------------------------------------

        subroutine getOxidationGasRates_C_interface(oxid_ptr, msootDotOxid, gasSourcesOxid) &
                bind(C, name="getOxidationGasRates_C_interface")
            import
            type(C_ptr), value           :: oxid_ptr
            real(C_double)               :: msootDotOxid
            real(C_double), dimension(*) :: gasSourcesOxid
        end subroutine getOxidationGasRates_C_interface

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

        subroutine getCoagulationSootRate_C_interface(coag_ptr, state, m1, m2) &
                bind(C, name="getCoagulationSootRate_C_interface")
            import
            type(C_ptr), value :: coag_ptr
            type(C_ptr), value :: state
            real(C_double)     :: m1
            real(C_double)     :: m2
        end subroutine getCoagulationSootRate_C_interface

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

        !-------------------- Tar Models  ---------------------------------------

        function tarModel_NONE_C_interface() result(tar_ptr) bind(C, name="tarModel_NONE_C_interface")
            import
            type(C_ptr) :: tar_ptr
        end function tarModel_NONE_C_interface

        !------------------------------------------------------------------------

        subroutine tar_delete_C_interface(tar_ptr) bind(C, name="tar_delete_C_interface")
            import
            type(C_ptr) :: tar_ptr
        end subroutine tar_delete_C_interface

        !-------------------- Soot Models ---------------------------------------

        function sootModel_MONO_C_interface(nsoot_, Ntar_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr) result(SM_ptr) &
                bind(C, name="sootModel_MONO_C_interface")
            import
            type(C_ptr)           :: SM_ptr
            integer(C_int), value :: nsoot_
            integer(C_int), value :: Ntar_
            type(C_ptr)           :: nucl_ptr
            type(C_ptr)           :: grow_ptr
            type(C_ptr)           :: oxid_ptr
            type(C_ptr)           :: coag_ptr
            type(C_ptr)           :: tar_ptr
        end function sootModel_MONO_C_interface

        !------------------------------------------------------------------------

        function sootModel_QMOM_C_interface(nsoot_, Ntar_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr) result(SM_ptr) &
                bind(C, name="sootModel_QMOM_C_interface")
            import
            type(C_ptr)           :: SM_ptr
            integer(C_int), value :: nsoot_
            integer(C_int), value :: Ntar_
            type(C_ptr)           :: nucl_ptr
            type(C_ptr)           :: grow_ptr
            type(C_ptr)           :: oxid_ptr
            type(C_ptr)           :: coag_ptr
            type(C_ptr)           :: tar_ptr
        end function sootModel_QMOM_C_interface

        !------------------------------------------------------------------------

        subroutine sootModel_delete_C_interface(SM_ptr, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr) &
                bind(C, name="sootModel_delete_C_interface")
            import
            type(C_ptr), value :: SM_ptr
            type(C_ptr), value :: nucl_ptr 
            type(C_ptr), value :: grow_ptr 
            type(C_ptr), value :: oxid_ptr 
            type(C_ptr), value :: coag_ptr
            type(C_ptr), value :: tar_ptr
        end subroutine sootModel_delete_C_interface

        !------------------------------------------------------------------------

        !subroutine setSourceTerms_C_interface(SM_ptr, state_ptr, nsoot_) bind(C, name="setSourceTerms_C_interface")
        !    import
        !    type(C_ptr) :: SM_ptr
        !    type(C_ptr), value :: state_ptr
        !    integer(C_int), value :: nsoot_
        !end subroutine setSourceTerms_C_interface

        !-------------------- State ---------------------------------------------

        subroutine setSourceTerms_C_interface(SM_ptr, state_ptr) bind(C, name="setSourceTerms_C_interface")
            import
            type(C_ptr)        :: SM_ptr
            type(C_ptr), value :: state_ptr
        end subroutine setSourceTerms_C_interface

        function state_C_interface(nsoot_, Ntar_) result(state_ptr) bind(C, name="state_C_interface")
            import
            type(C_ptr)           :: state_ptr
            integer(C_int), value :: nsoot_
            integer(C_int), value :: Ntar_
        end function state_C_interface

        !------------------------------------------------------------------------

        subroutine state_delete_C_interface(state_ptr) bind(C, name="state_delete_C_interface")
            import
            type(C_ptr), value  :: state_ptr
        end subroutine state_delete_C_interface

        !------------------------------------------------------------------------

        subroutine setState_C_interface(state_ptr, T_, P_, rhoGas_, muGas_, yGas_, yPAH_, &
                                        yTar_, yBio_, sootVar_, tarVar_, nsoot_, Ntar_, cMin_) &
                                        bind(C, name="setState_C_interface")
            import
            type(C_ptr),    value        :: state_ptr
            real(C_double), value        :: T_
            real(C_double), value        :: P_
            real(C_double), value        :: rhoGas_
            real(C_double), value        :: muGas_
            real(C_double), dimension(*) :: yGas_
            real(C_double), dimension(*) :: yPAH_
            real(C_double), dimension(*) :: yTar_
            real(C_double), dimension(*) :: yBio_
            real(C_double), dimension(*) :: sootVar_
            real(C_double), dimension(*) :: tarVar_
            integer(C_int), value        :: nsoot_
            integer(C_int), value        :: Ntar_
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

    end interface

        !-------------------- Continue as needed for interface functions --------

    public :: nucleationModel_LL, nucleationModel_LIN, getNucleationSootRate, getNucleationGasRates, &
        growthModel_LL, growthModel_LIN, getGrowthSootRate, nucleation_delete, getGrowthGasRates, &
        growth_delete, oxidationModel_LL, getOxidationSootRate, getOxidationGasRates, oxid_delete, &
        coagulationModel_FM, getCoagulationSootRate, set_FM_multiplier, coag_delete, tarModel_NONE, tar_delete, &
        sootModel_MONO, sootModel_delete, sootModel_QMOM, setSourceTerms, state, state_delete, setState, &
        getGasSpC, getGasSpP, getGasMeanFreePath, get_pahSpC, get_pahSpP, setSootScales 

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

        subroutine getNucleationSootRate(nucl_ptr, state)
            type(C_ptr), intent(in) :: nucl_ptr
            type(C_ptr), intent(in) :: state

            call getNucleationSootRate_C_interface(nucl_ptr, state)
        end subroutine getNucleationSootRate

        !------------------------------------------------------------------------

        subroutine getNucleationGasRates(nucl_ptr, msootDotNucl, gasSourcesNucl)
            type(C_ptr)     , intent(in)               :: nucl_ptr
            double precision, intent(in)               :: msootDotNucl
            double precision, intent(in), dimension(:) :: gasSourcesNucl

            call getNucleationGasRates_C_interface(nucl_ptr, msootDotNucl, gasSourcesNucl)
        end subroutine getNucleationGasRates

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

        subroutine getGrowthSootRate(grow_ptr, state)
            type(C_ptr), intent(in) :: grow_ptr
            type(C_ptr), intent(in) :: state

            call getGrowthSootRate_C_interface(grow_ptr, state)
        end subroutine getGrowthSootRate

        !------------------------------------------------------------------------

        subroutine getGrowthGasRates(grow_ptr, msootDotGrow, gasSourcesGrow)
            type(C_ptr)     , intent(in)               :: grow_ptr
            double precision, intent(in)               :: msootDotGrow
            double precision, intent(in), dimension(:) :: gasSourcesGrow

            call getGrowthGasRates_C_interface(grow_ptr, msootDotGrow, gasSourcesGrow)
        end subroutine getGrowthGasRates

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

        subroutine getOxidationSootRate(oxid_ptr, state)
            type(C_ptr), intent(in) :: oxid_ptr
            type(C_ptr), intent(in) :: state

            call getOxidationSootRate_C_interface(oxid_ptr, state)
        end subroutine getOxidationSootRate

        !------------------------------------------------------------------------

        subroutine getOxidationGasRates(oxid_ptr, msootDotOxid, gasSourcesOxid)
            type(C_ptr)     , intent(in)               :: oxid_ptr
            double precision, intent(in)               :: msootDotOxid
            double precision, intent(in), dimension(:) :: gasSourcesOxid

            call getOxidationGasRates_C_interface(oxid_ptr, msootDotOxid, gasSourcesOxid)
        end subroutine getOxidationGasRates

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

        subroutine getCoagulationSootRate(coag_ptr, state, m1, m2)
            type(C_ptr)     , intent(in) :: coag_ptr
            type(C_ptr)     , intent(in) :: state
            double precision, intent(in) :: m1
            double precision, intent(in) :: m2

            call getCoagulationSootRate_C_interface(coag_ptr, state, m1, m2)
        end subroutine getCoagulationSootRate

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

        subroutine tarModel_NONE(tar_ptr)
            type(C_ptr), intent(out) :: tar_ptr
            tar_ptr = tarModel_NONE_C_interface()
        end subroutine tarModel_NONE

        !------------------------------------------------------------------------

        subroutine tar_delete(tar_ptr)
            type(C_ptr), intent(inout) :: tar_ptr
            call tar_delete_C_interface(tar_ptr)
            tar_ptr = C_NULL_ptr
        end subroutine tar_delete

        !------------------------------------------------------------------------

        subroutine sootModel_MONO(SM_ptr, nsoot_, Ntar_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            integer(4),  intent(in)  :: nsoot_
            integer(4),  intent(in)  :: Ntar_
            type(C_ptr), intent(in)  :: nucl_ptr
            type(C_ptr), intent(in)  :: grow_ptr
            type(C_ptr), intent(in)  :: oxid_ptr
            type(C_ptr), intent(in)  :: coag_ptr
            type(C_ptr), intent(in)  :: tar_ptr

            SM_ptr = sootModel_MONO_C_interface(nsoot_, Ntar_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr)
        end subroutine sootModel_MONO

        !------------------------------------------------------------------------

        subroutine sootModel_delete(SM_ptr, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr)
            type(C_ptr), intent(inout) :: SM_ptr
            type(C_ptr), intent(inout) :: nucl_ptr
            type(C_ptr), intent(inout) :: grow_ptr
            type(C_ptr), intent(inout) :: oxid_ptr
            type(C_ptr), intent(inout) :: coag_ptr
            type(C_ptr), intent(inout) :: tar_ptr
            
            call sootModel_delete_C_interface(SM_ptr, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr)
            SM_ptr   = C_NULL_ptr
            nucl_ptr = C_NULL_ptr
            grow_ptr = C_NULL_ptr
            oxid_ptr = C_NULL_ptr
            coag_ptr = C_NULL_ptr
            tar_ptr  = C_NULL_ptr

        end subroutine sootModel_delete

        !subroutine sootModel_delete(SM_ptr)
        !    type(C_ptr), intent(inout) :: SM_ptr
            
        !    call sootModel_delete_C_interface(SM_ptr)
        !    SM_ptr   = C_NULL_ptr

        !end subroutine sootModel_delete
        !------------------------------------------------------------------------

        subroutine sootModel_QMOM(SM_ptr, nsoot_, Ntar_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            integer    , intent(in)  :: nsoot_
            integer    , intent(in)  :: Ntar_
            type(C_ptr), intent(in)  :: nucl_ptr
            type(C_ptr), intent(in)  :: grow_ptr
            type(C_ptr), intent(in)  :: oxid_ptr
            type(C_ptr), intent(in)  :: coag_ptr
            type(C_ptr), intent(in)  :: tar_ptr

            SM_ptr = sootModel_QMOM_C_interface(nsoot_, Ntar_, nucl_ptr, grow_ptr, oxid_ptr, coag_ptr, tar_ptr)
        end subroutine sootModel_QMOM

        !------------------------------------------------------------------------

        !subroutine setSourceTerms(SM_ptr, state_ptr, nsoot_)
        !    type(C_ptr), intent(out)    :: SM_ptr
        !    type(C_ptr), intent(in)     :: state_ptr
        !    integer    , intent(in)     :: nsoot_

        !    call setSourceTerms_C_interface(SM_ptr, state_ptr, nsoot_)
        !end subroutine setSourceTerms

        !------------------------------------------------------------------------

        subroutine setSourceTerms(SM_ptr, state_ptr)
            type(C_ptr), intent(out) :: SM_ptr
            type(C_ptr), intent(in)  :: state_ptr

            call setSourceTerms_C_interface(SM_ptr, state_ptr)
        end subroutine setSourceTerms

        !------------------------------------------------------------------------

        subroutine state(state_ptr, nsoot_, Ntar_)
            type(C_ptr), intent(out)   :: state_ptr
            integer    , intent(in)    :: nsoot_
            integer    , intent(in)    :: Ntar_

            state_ptr = state_C_interface(nsoot_, Ntar_)
        end subroutine state

        !------------------------------------------------------------------------

        subroutine state_delete(state_ptr)
            type(C_ptr), intent(inout) :: state_ptr
            call state_delete_C_interface(state_ptr)
            state_ptr = C_NULL_ptr
        end subroutine state_delete

        !------------------------------------------------------------------------

        subroutine setState(state_ptr, T_, P_, rhoGas_, muGas_, yGas_, yPAH_, &
                            yTar_, yBio_, sootVar_, tarVar_, nsoot_, Ntar_, cMin_)
            type(C_ptr)     , intent(inout)               :: state_ptr
            double precision, intent(inout)               :: T_
            double precision, intent(inout)               :: P_
            double precision, intent(inout)               :: rhoGas_
            double precision, intent(inout)               :: muGas_
            double precision, intent(inout), dimension(:) :: yGas_
            double precision, intent(inout), dimension(:) :: yPAH_
            double precision, intent(inout), dimension(:) :: yTar_
            double precision, intent(inout), dimension(:) :: yBio_
            double precision, intent(inout), dimension(:) :: sootVar_
            double precision, intent(inout), dimension(:) :: tarVar_
            integer         , intent(in)               :: nsoot_
            integer         , intent(in)               :: Ntar_
            double precision, intent(in)               :: cMin_

            call setState_C_interface(state_ptr, T_, P_, rhoGas_, muGas_, yGas_, yPAH_, &
                                      yTar_, yBio_, sootVar_, tarVar_, nsoot_, Ntar_, cMin_)
        end subroutine setState

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

    !============================================================================

end module soot_module
