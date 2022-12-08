\page chemistry Chemistry

# Nucleation

Soot nucleation arises from gas phase species reacting into a smallest soot particle size.
The rate (\f$\#/\f$m\f$^3\f$kg s) is written as
$$R_n(m) = J_n\delta(m-m_n),$$
where \f$J_n\,(=)\,\#/\f$m\f$^3\f$s and \f$m_n\f$ is mass of the soot nucleate.

For moment methods (e.g., MONO, QMOM, LOGN, MOMIC), the moment \f$r\f$ source term is
$$R_{r,n} = \int m^kR_n(m)dm = \int m^kJ_n\delta(m-m_n)dm,$$
$$
\color{blue} {
R_{r,n} = m_n^kJ_n.
}
$$

## Nucleation chemistry

\f$J_n\f$ is written in terms of the gas state \f$T\f$, \f$P\f$, and \f$y_i\f$ and various models are available.

# Growth

For a continuous particle size distribution (assumed here), the growth rate (\f$\#/\f$m\f$^3\f$kg s) is given by
$$R_g(m) = -\frac{\partial}{\partial m}(v_gn(m)),$$
where \f$v_g\f$ is a velocity in the mass coordinate (the so-called internal coordinate) of the PSD and has units of kg/s. \f$v_g\f$ is given by
$$v_g = k_sS(m),$$
where \f$k_s\f$ is the mass growth rate per surface area \f$k_s\,(=)\,\f$kg/m\f$^2\f$s, and \f$S(m)\f$ is the soot surface area per particle. The expression for \f$R_g(m)\f$ follows from
$$R_g(m) = \lim_{\Delta m\rightarrow 0}\frac{k_s}{\Delta m}(N_{i-1}S_{i-1}-N_iS_i),$$
where \f$N_i\f$ is a discrete particle number density \f$\#/\f$m\f$^3\f$, and \f$S_i=S(m_i)\f$.

The moment source term is 
$$R_{r,g} = \int m^kR_n(R)dm = -\int m^k\frac{\partial}{\partial m}(v_gn(m))dm.$$
Integrating by parts and noting that \f$n(m)=0\f$ at the bounds of the integration gives
$$R_{r,g} = k\int_0^\infty v_gm^{k-1}n(m)dm.$$
Now, use \f$v_g = k_sS(m)\f$ with \f$S = \pi d^2\f$, \f$m=\rho_s\pi d^3/6\f$, or
$$S(m) = \pi\left(\frac{6}{\pi\rho_s}\right)^{2/3}m^{2/3}.$$
Then we have
$$
\color{blue} {
R_{r,g} = k_s\pi\left(\frac{6}{\pi\rho_s}\right)^{2/3}kM_{k-1/3}.
}
$$
Here, the \f$M_{k-1/3}\f$ makes it clear that we will need expressions for fractional moments, and evaluation of such moments requires moment *closure*.

# Oxidation

Oxidation follows the same form as growth but the positive \f$k_s\f$ is replaced with the negatively signed \f$k_o\f$.

# Coagulation

Particle coagulation between two particles of masses \f$m\f$ and \f$\mu\f$ results in the rate (\f$\#/\f$m\f$^3\f$kg s)
$$R_c(m) = \frac{1}{2}\int_0^m\beta(\mu, m-\mu)n(\mu)n(m)d\mu - \int_0^\infty\beta(m,\mu)n(\mu)n(m)d\mu.$$
The first term represents creation of particles of size \f$m\f$ by particles smaller than size \f$m\f$, and the second term represents destruction of particles of size \f$m\f$ by collision of size \f$m\f$ particles with all particles \f$\mu\f$. \f$\beta\f$ is the coagulation coefficient.

The coagulation rate for a moment \f$M_r\f$ is 
$$
R_{r,c} = \frac{1}{2}\iint\beta(m,\mu)n(m)n(\mu)\left[-2m^k+\sum_{j=0}^r\left(r\atop j\right)m^j\mu^{r-j}\right]dmd\mu.
$$ 
This simplifies to
$$
\color{blue} {
\begin{align}
&R_{0,c} = -\frac{1}{2}\iint\beta(m,\mu)n(m)n(\mu)dmd\mu, \\\\
&R_{1,c} = 0,  \\\\
&R_{r\ge 2,c} = \frac{1}{2}\iint\beta(m,\mu)n(m)n(\mu)\sum_{j=1}^{r-1}\left(r\atop j\right)m^j\mu^{r-j}dmd\mu.
\end{align}
}
$$

The coagulation coefficient \f$\beta\f$ is generally written for two regimes: free molecular, and continuum, depending on ratio of the mean free path of the particles to the particle diameter (particle Knudsen number). 

## Free molecular (FM)

The coagulation coefficient in the free molecular regime (large Knudsen number) is given by
$$
\color{blue} {
\beta^{FM}(m,\mu) = \epsilon_c\left(\frac{\pi k_BT}{2}\right)\left(\frac{6}{\pi\rho_s}\right)^{2/3}\left(\frac{1}{m}+\frac{1}{\mu}\right)^{1/2}(m^{1/3}+\mu^{1/3})^2.
}
$$
Here, \f$k_B\f$ is the Boltzmann constant, \f$\rho_s\f$ is the soot particle density, and \f$\epsilon_c\f$ is a van der Waals enhancement factor (\f$\epsilon_c = 2.2\f$). The term \f$(1/m+1/\mu)^{1/2}\f$ is the reduced mass \f$m_1m_2/(m_1+m_2)\f$, and \f$(6/\pi\rho_s)^{2/3}(m^{1/3}+\mu^{1/3})^2 = (d_m+d_\mu)^2\f$, where \f$d_m\f$ and \f$d_\mu\f$ are the diameters of particles with masses \f$m\f$ and \f$\mu\f$, respectively.

## Continuum \(C\)

The coagulation coefficient in the continuum regime (small Knudsen number) is given by 
$$
\color{blue} {
\beta^C(m,\mu) = \frac{2k_BT}{3\mu_v}\left(\frac{C_m}{m^{1/3}}\frac{C_\mu}{\mu^{1/3}}\right)(m^{1/3}+\mu^{1/3}),
}
$$
where \f$\mu_v\f$ is the gas dynamic viscosity, and \f$c_m\f$ (and similarly for \f$c_\mu\f$) is
$$
\color{blue} {
C_m = 1+1.657Kn_m,
}
$$
$$
\color{blue} {
Kn_m = 2\lambda_g/d_m,
}
$$
$$
\color{blue} {
\lambda_g = \nu\left(\frac{\pi M}{2RT}\right)^{1/2},
}
$$
where \f$C_m\f$ is the Cunningham slip correction factor, \f$\lambda_g\f$ is the gas mean free path, \f$\nu\f$ is the kinematic viscosity, \f$M\f$ is the gas mean molecular weight, and \f$R\f$ is the gas constant. 

## Transition region

### Harmonic mean
A harmonic mean can be used to transition between the FM and C regimes:
$$
\color{blue} {
\beta^{HM} = \frac{\beta^{FM}\beta^C}{\beta^{FM}+\beta^C}.
}
$$

### Fuchs

Fuchs uses the following form that transitions between the FM and C regime.
$$
\color{blue} {
\beta^{F}(m,\mu) = 2\pi(D_m+D_\mu)(d_m+d_\mu)\left(
\frac{d_m+d_\mu}{d_m+d_\mu+2(g_m^2+g_\mu^2)^{1/2}} +
\frac{8(D_m+D_\mu)/\epsilon_c}{(\bar{c}_m^2+\bar{c}_\mu^2)^{1/2}(d_m+d_\mu)}
\right)^{-1},
}
$$
$$
\color{blue} {
\bar{c}_m = \left(\frac{8k_BT}{\pi m}\right)^{1/2},
}
$$
$$
\color{blue}{
g_m = \frac{\sqrt{2}}{3d_ml}\left[(d_m+l_m)^3-(d_m^2+l_m^2)^{3/2}\right] - \sqrt{2}d_m,
}
$$
$$
\color{blue} {
l_m = \frac{8D_m}{\pi\bar{c}_m},
}
$$
$$
\color{blue} {
D_m = \frac{k_BTC_c}{3\pi\mu_vd_m},
}
$$
where \f$D_m\f$ is particle diffusivity, \f$l_m\f$ is a particle mean free path, \f$\bar{c}_m\f$ is the mean particle velocity, and \f$g_m\f$ is defined in The Mechanics of Aerosols by Fuchs page 291. (Note that Seinfeld erroneously lea leaves off the \f$\sqrt{2}\f$ in the second term of \f$g_m\f$.)

