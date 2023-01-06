\page computational_cost Computational Cost

<!-- #################################################################### -->

The computational cost of the implemented soot models is compared, represented by the time required for one thousand evaluations of the ```calcSourceTerms``` function averaged over one hundred trials.           Comparisons were performed using a 3.5 GHz Intel i5-7400 CPU with 8 GB of available RAM via Windows Subsystem for Linux (WSL). The base ```sootModel``` object used for comparisons was initialized with ```LL``` chemistry and a 4-moment ```QMOM``` PSD treatment, and the ```state``` object represents a stoichiometric ethylene-air mixture, initially at 1 atm and 298 K, equilibrated by Cantera at constant pressure and enthalpy.

The following figure summarizes the relative cost of soot chemistry models, where only the model in      question differs from the base ```sootModel``` object. Results are normalized by the runtime of the base   ```sootModel``` configuration, which required an average of 0.3156 s.
Even though there are differences in the mean computational time for soot chemistry models, they may or may  not represent a significant addition to the computational cost of a combustion simulation as a whole.

<img src="comp_cost_chem.png" width=500>

The next figures compare  the relative computational cost of SootLib's implemented PSD models using the same criteria as the chemistry comparison, where only the PSD model or the number of moments used differs from the base ```sootModel``` configuration. Results are normalized by the runtime of the 2-moment ```MONO``` configuration, which required an average of 0.2961 s.
The ```MOMIC``` configurations are presented on a separate plot to highlight the difference in scale      compared to the ```MONO```, ```LOGN```, and ```QMOM``` models.
The numbers above the bars indicate the number of moments used.

<img src="comp_cost_PSDa.png" width=500>

<img src="comp_cost_PSDb.png" width=500>

It is well known that the computational cost of a sectional model depends on the number of sections---and   therefore the number of transport equations---defined for the system, so a comparison to that effect is not   included here. Additionally, sections interact with one another differently than moments do, so a direct      comparison between the sectional model and any of the moment methods would not necessarily be meaningful.

Comparison of these figures reveals two important points to consider when choosing soot model parameters for combustion simulations. First, the choice of soot chemistry presents much  less variation in computational time than the choice of PSD model. That is, choosing a more complex combination of soot chemistry models is unlikely to affect the overall computational cost of a simulation as much as choosing a more complex PSD model would. Second, the choice of PSD treatment and the number of moments to use is non-trivial. Assuming a shape for the soot PSD requires significantly less computational time than more complex methods, but comes at the expense of accuracy and flexibility. Thus, choosing an appropriate soot PSD model often becomes a question of balance between accuracy and computational cost.
