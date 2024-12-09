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
    type(C_ptr) :: SM
    type(C_ptr) :: S
    real(8)     :: FM_multiplier = 9.0/2.0/2.2;

    integer(4), PARAMETER  :: nsoot = 2
    real(C_double)         :: T_value
    !--------------- set state parameters
    double precision               :: T      = 2100.0;
    double precision               :: P      = 101325.0;
    double precision               :: rhoGas = 0.1;
    double precision               :: muGas  = 0.00001;
    double precision               :: cMin   = 100.0;

    double precision, dimension(11)    :: yGas   = (/0.05, 0.001, 0.002, 0.0003, 0.003, 0.07, 0.1, 0.002, 0.0, 0.0, 0.0/);
    character(4), dimension(11)   :: keys   = (/"O2  ","O   ","H2  ","H   ","OH  ","H2O ","CO  ","C2H2","C6H6","C   ","CO2 "/);
    double precision, dimension(6)     :: yPAH   = (/0.0, 0.0, 0.0, 0.0, 0.0, 0.0/);
    double precision, dimension(nsoot) :: Msoot  = (/0.003, 1.5e-5/);
    double precision, dimension(nsoot) :: sootS  = (/0.0,0.0/);

    character(len=100) :: fmt1, fmt2

    integer :: i


    call nucleationModel_LL(nucl)
    call growthModel_LL(grow)
    call oxidationModel_LL(oxid)
    call coagulationModel_FM(coag)
    

    !call sootModel_QMOM(SM, nsoot, Ntar, nucl, grow, oxid, coag)
    call sootModel_MONO(SM, nsoot, nucl, grow, oxid, coag)
    
    call set_FM_multiplier(coag, FM_multiplier)

    call state(S, nsoot)
    
    call setState(S, T, P, rhoGas, muGas, yGas, yPAH, Msoot, nsoot, cMin)

    !call setSourceTerms(SM, S, nsoot)
    call setSourceTerms(SM, S)

    fmt1 = "(A9, F14.3)"
    fmt2 = "(2F14.8)"

    write(*,*)
    write(*,fmt1) " T (K)  = ", T
    write(*,fmt1) " P (Pa) = ", P 
    write(*,*) "   yGas   "
    do i = 1, 11 
        print *, trim(keys(i)) 
        write(*,fmt2) yGas(i)
    enddo
    
    call getSootSources(sootS, SM, nsoot)
    do i = 1, 2 
        write(*,*) sootS(i)
    enddo


    !call nucleation_delete(nucl)
    !call growth_delete(grow)
    !call oxid_delete(oxid)
    !call coag_delete(coag)



end program simple_example_fort

