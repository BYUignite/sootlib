program simple_example_fort

    use soot_module

    use, intrinsic :: ISO_C_Binding, only: C_ptr, C_double

    implicit none

    !============================================================================

    !----------------------------------------------------------------------------

    type(C_ptr) :: nucl 
    type(C_ptr) :: grow 
    type(C_ptr) :: oxid 
    type(C_ptr) :: coag
    type(C_ptr) :: tar
    type(C_ptr) :: SM
    type(C_ptr) :: S
    real(8)     :: FM_multiplier = 9.0/2.0/2.2;

    integer(4), PARAMETER  :: nsoot = 2
    integer(4), PARAMETER  :: Ntar  = 1
    real(C_double)         :: T_value
    !--------------- set state parameters
    double precision               :: T      = 2100.0;
    double precision               :: P      = 101325.0;
    double precision               :: rhoGas = 0.1;
    double precision               :: muGas  = 0.00001;
    double precision               :: cMin   = 100.0;

    double precision, dimension(11)    :: yGas   = (/0.05, 0.001, 0.002, 0.0003, 0.003, 0.07, 0.1, 0.002, 0.18, 0.0, 0.0/);
    character(4), dimension(11)   :: keys   = (/"O2  ","O   ","H2  ","H   ","OH  ","H2O ","CO  ","C2H2","C6H6","C   ","CO2 "/);
    character(2), dimension(2)    :: keys2  = (/"M0", "M1"/)
    double precision, dimension(6)     :: yPAH   = (/0.0, 0.0, 0.0, 0.0, 0.0, 0.0/);
    double precision, dimension(5)     :: yBio   = (/1.0, 0.0, 0.0, 0.0, 0.0/);
    double precision, dimension(nsoot) :: Msoot  = (/0.003, 1.5e-5/);
    double precision, dimension(Ntar)  :: Mtar   = (/0.002/);
    double precision, dimension(nsoot) :: sootS  = (/0.0,0.0/);
    double precision, dimension(11)    :: gasS   = 0.0 

    character(len=100) :: fmt1, fmt2

    integer :: i


    call nucleationModel_LL(nucl)
    call growthModel_LL(grow)
    call oxidationModel_LL(oxid)
    call coagulationModel_FM(coag)
    call tarModel_NONE(tar)
    

    !call sootModel_QMOM(SM, nsoot, Ntar, nucl, grow, oxid, coag)
    call sootModel_MONO(SM, nsoot, nucl, grow, oxid, coag, Ntar, tar)
    
    call set_FM_multiplier(coag, FM_multiplier)

    call state(S, nsoot, Ntar)
    
    call getyBio(S, yBio)
    call get_mtar_ytar(S)

    call setState(S, T, P, rhoGas, muGas, yGas, yPAH, Msoot, nsoot, Mtar, Ntar, cMin)

    !call setSourceTerms(SM, S, nsoot)
    call setSourceTerms(SM, S)

    fmt1 = "(A9, 2ES14.6)"
    fmt2 = "(A9, 2ES14.8)"

    write(*,*)
    write(*,fmt1) " T (K)  = ", T
    write(*,fmt1) " P (Pa) = ", P 
    write(*,fmt1) "            Gas Source Terms   "
    
    call getGasSources(gasS, SM)

    do i = 1, 11 
        !print *, trim(keys(i)) 
        write(*,fmt1) trim(keys(i)), gasS(i)
    enddo
    
    write(*,*)

    call getSootSources(sootS, SM, nsoot)

    write(*,fmt2) " M0 = ", sootS(1)
    write(*,fmt2) " M1 = ", sootS(2)

    call nucleation_delete(nucl)
    call growth_delete(grow)
    call oxid_delete(oxid)
    call coag_delete(coag)
    !call tar_delete(tar)



end program simple_example_fort

