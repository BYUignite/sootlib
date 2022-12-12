\page momic Method of Moments with Interpolative Closure (MOMIC)

In the [chemistry](1_chemistry.md) section, rate expressions were written in terms of fractional moments. For coagulation, the rate expressions were written in terms of integral expressions, which were then specialized to specific models. For coagulation in the continuum regime, this resulted in fractional moments. The MOMIC model uses polynomial interpolation among logarithms of integer moments to evaluate fractional moments. In the free molecular regime, the term \f$(1/m+1/\mu)^{1/2}\f$ required special treatment for the lognormal model, and also here for the MOMIC model. In MOMIC, the coagulation rate with the power \f$1/2\f$ is interpolated from the coagulation rate assuming integer powers, which removes the difficulty in evaluation. 

# Interpolation

## Fractional moments

Interpolation among integer moments to find fractional moments \f$M_r\f$ is done using polynomial interpolation among logarithms of moments. In particular, Newton Foward Interpolation is used. (Frenklach uses Lagrange interpolation, but polynomials through given moments are unique, so the terminology used for the interpolation really just indicates the algorithm used for evaluation, and Newton Forward Interpolation is efficient for the repeated evaluations needed.)

Following Frenklach, positive fractional moments are interpolated using a polynomial including all available integer moments, while negative fractional moments, which require extrapolation, are evaluated using \f$M_0\f$, \f$M_1\f$, and \f$M_2\f$.

## Grid functions for FM coagulation

Inserting the expression for \f$\beta^{FM}\f$ into those for \f$R_{r,c}^{FM}\f$ gives
$$\begin{align}
&R_{0,c}^{FM} = -\frac{K_{FM}}{2}\iint n(m)n(\mu)(m+\mu)^{1/2}\left(m^{1/6}\mu^{-3/6}+2m^{-1/6}\mu^{-1/6} + m^{-3/6}\mu^{1/6}\right)m^0\mu^0dmd\mu, \nonumber \\\\
&R_{1,c}^{FM} = 0, \nonumber \\\\
&R_{r\ge 2,c}^{FM} = \frac{K_{FM}}{2}\sum_{k=1}^{r-1}\left(r\atop k\right)\underbrace{\iint n(m)n(\mu)(m+\mu)^\mathbf{1/2}\left(m^{1/6}\mu^{-3/6}+2m^{-1/6}\mu^{-1/6} + m^{-3/6}\mu^{1/6}\right)m^\mathbf{k}\mu^\mathbf{r-k}dmd\mu}_{f_{1/2}^{k,r-k}}. \nonumber
\end{align}$$

Here, \f$K_{FM}\f$is given by
$$K_{FM} = \epsilon_c\left(\frac{\pi k_BT}{2}\right)^{1/2}\left(\frac{6}{\pi\rho_s}\right)^{2/3}.$$

The term inside the integrals is called a *grid function* and is denoted \f$f_l^{x,y}\f$. For \f$R_{0,c}^{FM}\f$, the grid function is \f$f_{1/2}^{(0,0)}\f$. The subscript on the grid function denotes the power of the \f$(m+\mu)\f$ factor. The superscripts denote the respective powers of \f$m\f$ and \f$\mu\f$ at the far right (\f$k\f$ and \f$r-k\f$). \f$f_{1/2}\f$ is interpolated from \f$f_l\f$ with integer \f$l\f$, where, as for fractional moments, interpolation is among logarithms of \f$f\f$, that is, \f$\log{f_{1/2}}\f$ is interpolated from \f$\log{f_l}\f$, from which \f$f_{1/2}\f$ is computed.

Evaluation of these grid functions involves a number of fractional moments (which depends on the number of integer moments carried. These are computed and stored for a given soot state to avoid redundant calculations. Note that fractions have a six in the denominator and are not simplified. This results in convenient patterns, and consistency among terms that aids verification and implementation.
