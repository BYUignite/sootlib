\page test Lognormal distribution


The lognormal model assumes that the soot particle size distribution (PSD) is lognormal. This can be represented by the first three moments of the size distribution \f$M_0\f$, \f$M_1\f$, and \f$M_2\f$. 

# Particle size distribution

The lognormal distribution in terms of mass is given by
$$n(\log m) =\frac{dN(\log m)}{d\log m} = \frac{M_0}{\sigma\sqrt{2\pi}}\exp\left(-\frac{(\log m-\log\bar{m})^2}{2\sigma^2}\right).$$

Here, \f$N\f$ is used to denote the cumulative distribution and \f$\sigma\f$ is the standard deviation of \f$n\f$ with \f$\log m\f$ as the variable. We can write \f$n(m)\f$ instead of \f$n(\log m)\f$ using \f$d\log m = (1/m)dm\f$:

$$n(m) =\frac{dN(m)}{dm} = \frac{M_0}{\sigma\sqrt{2\pi}}\frac{1}{m}\exp\left(-\frac{\log^2(m/\bar{m})}{2\sigma^2}\right).$$

# Moments

The \f$k^\text{th}\f$ moment (integer or fraction) is given by
$$M_k = \int_0^\infty m^kn(m)dm.$$
Subsituting the expression for n(m) and performing the integration gives
$$M_k = M_0\bar{m}^ke^{k^2\sigma^2/2}.$$
This gives any moment \f$M_k\f$ in terms of \f$M_0\f$, \f$\bar{m}\f$ and \f$\sigma^2\f$. Now write \f$\sigma\f$ and \f$\bar{m}\f$ in terms of \f$M_0\f$, \f$M_1\f$, and \f$M_2\f$ by writing the above equation for \f$k=1\f$ and \f$k=2\f$, and solve for \f$\bar{m}\f$ and \f$\sigma^2\f$:
$$\bar{m} = \frac{M_1^2}{M_0^{3/2}M_2^{1/2}},$$
$$\sigma^2 = \log\left(\frac{M_0M_2}{M_1^2}\right).$$
Now, combine these with the expression for \f$M_k\f$ to get
$$M_k = M_0^{1-3k/2 + k^2/2}M_1^{2k-k^2}M_2^{k^2/2 - k/2}.$$

# Model evaluation

