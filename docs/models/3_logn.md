\page test Lognormal distribution


The lognormal model assumes that the soot particle size distribution (PSD) is lognormal. This can be represented by the first three moments of the size distribution \f$M_0\f$, \f$M_1\f$, and \f$M_2\f$. 

# Particle size distribution

The lognormal distribution in terms of mass is given by
$$n(\log m) =\frac{dN(\log m)}{d\log m} = \frac{M_0}{\sigma\sqrt{2\pi}}\exp\left(-\frac{(\log m-\log\bar{m})^2}{2\sigma^2}\right).$$

Here, \f$N\f$ is used to denote the cumulative distribution and \f$\sigma\f$ is the standard deviation of \f$n\f$ with \f$\log m\f$ as the variable. We can write \f$n(m)\f$ instead of \f$n(\log m)\f$ using \f$d\log m = (1/m)dm\f$:

$$n(m) =\frac{dN(m)}{dm} = \frac{M_0}{\sigma\sqrt{2\pi}}\frac{1}{m}\exp\left(-\frac{\log^2(m/\bar{m})}{2\sigma^2}\right).$$

# Moments

The \f$r^\text{th}\f$ moment (integer or fraction) is given by
$$M_r = \int_0^\infty m^rn(m)dm.$$
Subsituting the expression for n(m) and performing the integration gives
$$M_r = M_0\bar{m}^re^{r^2\sigma^2/2}.$$
This gives any moment \f$M_r\f$ in terms of \f$M_0\f$, \f$\bar{m}\f$ and \f$\sigma^2\f$. Now write \f$\sigma\f$ and \f$\bar{m}\f$ in terms of \f$M_0\f$, \f$M_1\f$, and \f$M_2\f$ by writing the above equation for \f$r=1\f$ and \f$r=2\f$, and solve for \f$\bar{m}\f$ and \f$\sigma^2\f$:
$$\bar{m} = \frac{M_1^2}{M_0^{3/2}M_2^{1/2}},$$
$$\sigma^2 = \log\left(\frac{M_0M_2}{M_1^2}\right).$$
Now, combine these with the expression for \f$M_r\f$ to get
$$M_r = M_0^{1-3r/2 + r^2/2}M_1^{2r-r^2}M_2^{r^2/2 - r/2}.$$

# Model evaluation

The nucleation, growth, and oxidation models can be evaluated as presented on the [chemistry](1_chemistry.md) page. Those relations are written in terms of fractional moments, which are available using the equation above. The expression for coagulation in the **continuum regime \(C\)** can be integrated to give
$$\begin{align}
R^C_{0,c} &= -K_C\left[M_0^2 + M_{2/6}M_{-2/6} + K_C^\prime\left(M_0M_{-2/6} + M_{2/6}M_{-4/6}\right)\right], \\\\
R^C_{1,c} &=0, \\\\
R^C_{2,c} &= 2K_C\left[M_1^2 + M_{4/6}M_{8/6} + K_C^\prime\left(M_1M_{4/6} + M_{2/6}M_{8/6}\right)\right], \\\\
&K_C = \frac{2k_BT}{3\mu_v}, \\\\
&K_C^\prime = (2)(1.675)\lambda_g\left(\frac{\pi\rho_s}{6}\right)^{1/3}.
\end{align}$$

In the **free molecular (FM)** the coagulation coefficient has a factor \f$(1/m+1/\mu)^{1/2}\f$. This factor precludes direct integration of the coagulation rate. As a result, this factor is approximated \cite Pratsinis_1988 as
$$\left(\frac{1}{m} + \frac{1}{\mu}\right)^{1/2} \approx b\left(\frac{1}{m^{1/2}} + \frac{1}{\mu^{1/2}}\right),$$
where \f$b\f$ is a correction constant that is bounded between \f$1/\sqrt{2}\approx 0.707\f$ and 1 when \f$m\f$ and \f$\mu\f$ approach the same size and when they are widely separated, respectively. Taking the average gives at worst a 15\% error, which is done here. The rate expression is then integrated to give
$$\begin{align}
R^{FM}_{0,c} &=-K_{FM}b\left(M_0M_{1/6} + 2M_{2/6}M_{-1/6} + M_{4/6}M_{-3/6}\right), \\\\
R^{FM}_{1,c} &=0, \\\\
R^{FM}_{2,c} &=2K_{FM}b\left(M_1M_{7/6} + 2M_{8/6}M_{5/6} + M_{10/6}M_{3/6}\right), \\\\
&K_{FM} = \epsilon_c\left(\frac{\pi k_BT}{2}\right)^{1/2}\left(\frac{6}{\pi\rho_s}\right)^{2/3}.
\end{align}$$

Detailed derivations are given in \cite Lignell_2008b.
