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

