\page qmom Quadrature Method of Moments (QMOM)

In the [chemistry](1_chemistry.md) section, the coagulation rates were written in terms of integral equations. These are then specialized to the several models for the particle size distributions (PSD). In QMOM, these integrals are computed by numerical quadrature. In general, we have
$$\int_a^bW(x)f(x)dx \approx\sum_{j_1}^Nw_jf(x_j),$$

where \f$f(x)\f$ is some generic function and \f$W(x)\f$ is a weighting function. On the right-hand-side (RHS), \f$w_j\f$ is a *weight* and \f$x_j\f$ is an *abscissa*. In specializing to soot formation, we take the weight function to be the (unknown) particle density function \f$n(m)\f$:
$$\int_0^\infty n(m)f(m)dm \approx\sum_{j_1}^Nw_jf(m_j).$$
Note that this is equivalent to assuming that the particle density function has the form
$$n(m) = \sum_{j=1}^N \delta(m-m_j).$$
That is, \f$n(m)\f$ is represented as a collection of a small number \f$N\f$ of single particle sizes with number density \f$w_j\f$ at each size, and mass \f$m_j\f$ of each size. This permits straightforward evaluation of integral functions involving \f$n(m)\f$. For example,
$$R_{0,c} = -\frac{1}{2}\iint\beta(m,\mu)n(m)n(\mu)dmd\mu = -\frac{1}{2}\sum_{j=1}^N\sum_{k=1}^N\beta(m_j,m_k)w_jw_k.$$

The \f$N\f$ \f$w_j\f$ and \f$m_j\f$ are evaulated using 2\f$N\f$ moments. So, for 4 moments we have
$$\begin{align}
M_0 &= \int m^0n(m)dm = \sum_{j=1}^2m_j^0w_j = w_1 + w_2 , \nonumber \\\\
M_1 &= \int m^1n(m)dm = \sum_{j=1}^2m_j^1w_j = m_1w_1 + m_2w_2, \nonumber \\\\
M_2 &= \int m^2n(m)dm = \sum_{j=1}^2m_j^2w_j = m_1^2w_1 + m_2^2w_2, \nonumber \\\\
M_3 &= \int m^3n(m)dm = \sum_{j=1}^2m_j^3w_j = m_1^3w_1 + m_2^3w_2 \nonumber .
\end{align}$$
These four equations can be solved for the two \f$w_j\f$ and \f$m_j\f$ values. These equations can be ill-conditioned; the Wheeler algorithm is commonly used for this solution.

