\page mono Monodispersed


The monodispersed model assumes that the soot particle size distribution (PSD) is represented with a single particle size. This size is represented by the first two moments of the size distribution \f$M_0\f$ and \f$M_1\f$ with units of \f$\#\f$/m\f$^3\f$ and kg/m\f$^3\f$, respectively. The mass is given by
$$\bar{m} = \frac{M_1}{M_0} = \frac{\pi}{6}d^3\rho_s,$$
assuming spherical particles.
The diameter is then
$$d = \left(\frac{6\bar{m}}{\pi\rho_s}\right)^{1/3} = \left(\frac{6M_1}{\pi\rho_sM_0}\right)^{1/3}.$$
While there is only one assumed size (at a given location and time), that size varies as \f$M_0\f$ and \f$M_1\f$ vary.

# Particle size distribution

The PDS written in terms of a particle density function (PDF) may be written as 
$$n(m) = M_0\delta(m-\bar{m}),$$
So that
$$M_0 = \int m^0n(m)dm = \int M_0\delta(m-\bar{m})dm,$$
$$M_1 = \int m^1n(m)dm = \int mM_0\delta(m-\bar{m})dm = \bar{m}M_0.$$

# Fractional moments

Note that fractional moments \f$M_r\f$ for some fraction \f$r\f$ are given by
$$M_r = \int m^rn(m)dm = \int m^rM_0\delta(m-\bar{m})dm = \bar{m}^rM_0 = \left(\frac{M_1}{M_0}\right)^rM_0,$$
$$M_r = M_0^{1-r}M_1^r.$$
This is a logarithmic interpolation equivalent to 
$$\log{M_r} = (1-r)\log M_0 + (r)\log M_1.$$

# Model evaluation

Given an assumed single particle size, all models for nucleation, growth, coagulation, etc. are written directly in terms of that size.
