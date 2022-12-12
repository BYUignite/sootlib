\page sect Sectional

The sectional soot model treats the particle size distribution (PSD) as residing in a number of discrete sections. These sections are treated as individual soot sizes, and interact as such, though the real PSD includes many more sizes. The soot resides in a number of *bins* of different masses. Each bin contains the number of particles per volume at the corresponding size. The bins are spaced geometrically using a constant bin growth factor that defaults to 2. The smallest bin is the mass of the smallest soot nucleate. Hence, the bins are given by
$$m_{min}\left(F^0,\,F^1,\,F^2,\ldots,\, F^{N-1}\right),$$
where \f$N\f$ is the number of sections, and \f$F\f$ is the bin growth factor.

# Nucleation

Nucleation is assumed to occur in the smallest bin. If the nucleate species has a different soot mass than \f$m_{min}\f$ corresponding to the specified bins (e.g., for variable sizes as occur during PAH nuclation), then the number going into the bin due to nucleation is adjusted to conserve mass.

# Growth and oxidation

## Growth

Growth results in a positive motion (velocity in the particle mass space) of particles from a given bin to the next larger bin. Oxidation results in a negative motion of particles from a given bin to the next smaller bin. The rate of change of particle number density in a bin due to growth is given by

$$\begin{align}
&\frac{dn_{1,g}}{dt} = -\frac{k_gA_1n_1}{m_2-m_1}, \nonumber \\\\
&\frac{dn_{i,g}}{dt} = \frac{k_gA_{i-1}n_{i-1}}{m_{i}-m_{i-1}} - \frac{k_gA_in_i}{m_{i+1}-m_i},\;\;\;\;2\le i\le N-1 \nonumber \\\\
&\frac{dn_{N,g}}{dt} = \frac{k_gA_{N-1}n_{N-1}}{m_{N}-m_{N-1}}  + \frac{k_gA_Nn_N}{m_N}. \nonumber
\end{align}$$

Here, \f$k_g\f$ has units of kg/m\f$^2\f$s, \f$A\f$ is area per particle, \f$m\f$ is mass perparticle, and \f$n\f$ is number per volume. The first bin includes only a sink as growth removes particles from the first bin, which then appear in the second bin. Interior bins include a source term from growth out of their smaller neighbor, and a sink term for growth into their larger neighbor. The last bin includes growth into the bin from the smaller neighbor, but also growth into the bin itself. Since there is no larger bin, this growth is accounted for as a change in the number of particles of size \f$m_N\f$ in bin \f$N\f$. Note that growth out of one bin is growth into the next. This is accounted for in the implementation to minimize computation costs. Evaluation is from the first bin to the last.

## Oxidation

Oxidation is similar to growth but flows from larger bins to smaller bins, and the evaluation is from the last bin to the first.

$$\begin{align}
&\frac{dn_{N,o}}{dt} =                                          -\frac{k_oA_Nn_N}{m_{N}-m_{N-1}}, \nonumber \\\\
&\frac{dn_{i,o}}{dt} = \frac{k_oA_{i+1}n_{i+1}}{m_{i+1}-m_{i}} - \frac{k_oA_in_i}{m_{i}-m_{i-1}},\;\;\;\;N-1\ge i\ge 2 \nonumber \\\\
&\frac{dn_{1,o}}{dt} = \frac{k_oA_{2}n_{2}}{m_{2}-m_{1}}  - \frac{k_gA_1n_1}{m_1}. \nonumber
\end{align}$$

Note the signs on the last term representing in a source in bin 1 from oxidation of bin 2, and a sink due to oxidation of bin 2, manifested as a reduction of particles (which stay in bin 1) due to oxidation of particles in bin 1 in such a way that mass is conserved.

# Coagulation

Coagulation is implemented using the descrete version of the coagulation rate presented on the [chemistry and physical models](1_chemistry.md) page, that is,
$$R_{c,i} = \frac{1}{2}\sum_{j=1}^{i-1}\beta(m_j,m_{i-j})n_jn_{i-j} - n_i\sum_{j=1}^N\beta(m_i,m_j)n_j.$$
This is implemented to maximize computational efficiency. 

Because the sectional model does not include all particle sizes, coagulation results in particle sizes that are between sections. Particles between sections are divided between the two neighboring sections so that mass and number are conserved \cite Lehtinen_2001. The location of the coagulate is found analytically in terms of the geometrically spaced sections.

