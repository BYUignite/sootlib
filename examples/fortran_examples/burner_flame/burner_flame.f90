program burner_flame

    use soot_module

    use, intrinsic :: ISO_C_Binding, only: C_ptr, C_double

    implicit none

    !============================================================================

    !----------------------------------------------------------------------------

    double precision, dimension(35) :: z_prof
    double precision, dimension(35) :: v_prof
    double precision, dimension(35) :: T_prof
    double precision, dimension(35) :: rho_prof
    double precision, dimension(35) :: mu_prof
    double precision, dimension(35) :: yH_prof
    double precision, dimension(35) :: yH2_prof
    double precision, dimension(35) :: yO_prof
    double precision, dimension(35) :: yO2_prof
    double precision, dimension(35) :: yOH_prof
    double precision, dimension(35) :: yH2O_prof
    double precision, dimension(35) :: yCO_prof
    double precision, dimension(35) :: yC2H2_prof

    integer i 

    open(1, file = 'burner_profiles.inp', status = 'old')
    read(1,*)
    do i = 1,35
        read(1,*) z_prof(i), v_prof(i), T_prof(i), rho_prof(i), mu_prof(i), yH_prof(i), yH2_prof(i), yO_prof(i), &
            yO2_prof(i), yOH_prof(i), yH2O_prof(i), yCO_prof(i), yC2H2_prof(i)
    end do
    close(1)

    do i = 1,35
        write(*,*) z_prof(i), yC2H2_prof(i)
    end do

end program burner_flame
