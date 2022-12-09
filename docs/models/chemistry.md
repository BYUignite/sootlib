\page chemistry Chemistry

# Nucleation

Soot nucleation arises from gas phase species reacting to form the smallest soot particles.
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

### Leung & Lindstedt (LL)

SootLib's most basic chemistry model is the simplified kinetic mechanism presented by Leung and Lindstedt (``LL``), which consists of four Arrhenius-style rate expressions: one each for soot nucleation, surface growth, oxidation, and coagulation \cite Leung_1991. The ``LL`` nucleation rate depends only on the concentration of gaseous acetylene, the gas temperature, and an empirically-determined rate constant: $$R_{nuc} = 0.1\times 10^5 e^{-21100/T} [\text{C}_2\text{H}_2].$$.

### Lindstedt (LIN)
Lindstedt later proposed an alteration to the ``LL`` nucleation step's pre-exponential factor to increase accuracy without changing the expression's form (``LIN``) \cite Lindstedt_2005 , giving the following expression:
$$R_{nuc} = 0.1\times 10^{-11} e^{-12100/T} [\text{C}_2\text{H}_2].$$

### PAH nucleation (PAH)
SootLib implements the PAH nucleation model presented by Blanquart and Pitsch, in which nascent soot particles are created by the collision of two PAH dimers, themselves created by the collision of two PAH molecules \cite Blanquart_2009c. For a given PAH molecule, the self-collision rate derived from the kinetic molecular theory of gases is
$$\omega_{\text{dimer}} = \sum_i 4\gamma_i \left( \frac{\pi k T}{m_i} \right)^{1/2} \left( \frac{6m_i}{\pi \rho_s} \right)^{2/3} [\text{PAH}]^2$$,
where \f$k\f$ is the Boltzmann constant, \f$T\f$ is gas temperature, \f$m_i\f$ is the mass of PAH species \f$i\f$, and \f$\rho_s\f$ is the solid soot density. The sticking coefficient \f$\gamma\f$, which scales with \f$m_i^4\f$, accounts for the difference between the observed self-collision rate and the rate predicted by kinetic molecular theory. The following table lists the PAH species considered by this PAH nucleation model, their masses \f$m_i\f$, and their sticking coefficients \f$\gamma_i\f$:
| PAH species       | Formula | \f$m_i\f$ (amu) | \f$\gamma_i\f$ |
|-------------------|---------|-----------------|----------------|
| Naphthalene       | C\f$_{10}\f$H\f$_8\f$ | 128 | 0.0010 |
| Acenaphthylene    | C\f$_{12}\f$H\f$_8\f$ | 152 | 0.0030 |  
| Biphenyl          | C\f$_{12}\f$H\f$_{10}\f$ | 154 | 0.0085 | 
| Phenathrene       | C\f$_{14}\f$H\f$_{10}\f$ | 178 | 0.0150 | 
| Acephenanthrylene | C\f$_{16}\f$H\f$_{10}\f$ | 202 | 0.0250 | 
| Pyrene            | C\f$_{16}\f$H\f$_{10}\f$ | 202 | 0.0250 | 
| Fluoranthene      | C\f$_{16}\f$H\f$_{10}\f$ | 202 | 0.0250 | 
| Cyclo[cd]pyrene   | C\f$_{18}\f$H\f$_{10}\f$ | 226 | 0.0390 |
Rather than computing the properties of every possible dimer combination, the model evaluates only the total rate of dimer formation \f$\omega_{\text{dimer}}\f$ and the average carbon content of each dimer. Because PAH and dimer collision rates are high, we compute dimer concentration assuming a quasi-steady state. The PAH dimer concentration can be found by solving the quadratic equation given by
$$\omega_{\text{dimer}} = 2 \beta(m_D,m_D) [\text{DIMER}]^2 + [\text{DIMER}] \sum_i \beta(m_{\text{PAH}_i},m_{\text{PAH}_i}) N_i$$
for \f$[\text{DIMER}]\f$, where \f$\beta(m_{\text{PAH}_i},m_{\text{PAH}_i})\f$ is the self-collision rate of PAH species \f$i\f$, \f$N_i\f$ is the number density of PAH species \f$i\f$, and \f$\beta(m_D,m_D)\f$ is the self-collision rate of the PAH dimer, whose calculation depends on the chosen coagulation model. Once the steady state dimer concentration has been computed, the nucleation rate is given by
$$R_{nuc} = \frac{1}{2}\beta(m_D,m_D) [\text{DIMER}]^2.$$

This PAH nucleation model also accounts for condensation of PAH dimers onto existing soot particles, which contributes to chemical surface growth. The PAH condensation rate is computed similarly to the nucleation rate, but \f$\beta\f$ is computed as the collision rate between PAH dimers and soot particles rather than the self-collision rate of PAH dimers and the mass concentration of both the PAH dimers and soot particles is taken into account.

# Surface Growth

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

## Surface growth chemistry
Most soot surface growth models rely on acetylene (C\f$_2\f$H\f$_2\f$) as the primary source of gaseous carbon, though other species may also contribute. Additionally, surface growth models tend to include some dependence on the soot particle's surface area since the availability of sites for the addition of carbon atoms to existing particles tends to be a limiting factor in rate calculations \cite Wang_2011.

### Leung & Lindstedt (LL)
The Leung and Lindstedt mechanism for soot surface growth (LL) \cite Leung_1991 depends on both the gaseous concentration of acetylene and the particle surface area available for surface reactions. The overall rate of soot surface growth is computed as
$$R_{grw} = 0.6\times 10^4 e^{-21100/T} f(A_s) [\text{C}_2\text{H}_2].$$
\f$f(A_s)\f$ is a function of the available particle surface area given by
$$f(A_s) = \sqrt{\pi \left( \frac{6MW_C}{\pi \rho_{s}} \right) ^{2/3}} \left[ \frac{\rho Y_{s}}{MW_C} \right]^{1/3} [\rho N]^{1/6},$$
where \f$MW_C\f$ is the molar mass of carbon, \f$\rho\f$ is the gas density, \f$\rho_{s}\f$ is the solid density of soot, \f$Y_{s}\f$ is the mass fraction of soot, and \f$N\f$ is the soot particle number density. Results showed that the normal square dependence of the rate on available surface sites does not accurately predict the soot number density throughout the flame \cite Leung_1991, and later models explored alternative methods.

### Lindstedt (LIN)
Lindstedt proposed and tested several alternative models for the surface growth rate, concluding that the model in which the growth rate is dependent on soot number density but independent of soot surface area produced better results \cite Lindstedt_1994. This modified growth rate (LIN) is given by
$$R_{grw} = 750 e^{-12100/T} [\text{C}_2\text{H}_2] 2N_s MW_C,$$
where \f$N_s\f$ is the number density of soot particles and \f$MW_C\f$ is the molar mass of carbon.

### Hydrogen-abstraction acetylene-addition (HACA)

The HACA growth mechanism consists of a repeating sequence of elementary reaction steps with individual Arrhenius-style rate expressions, listed in the following table.

# Oxidation

Oxidation follows the same form as growth but the positive \f$k_s\f$ is replaced with the negatively signed \f$k_o\f$.

## Oxidation chemistry

### Leung & Lindstedt (LL)

### Nagle & Strickland-Constable (NSC)

### Lee et al. (LEE)

### Neoh et al. (NEOH)

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


