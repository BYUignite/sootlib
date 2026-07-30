
import numpy as np
import matplotlib
matplotlib.use('PDF')       
import matplotlib.pyplot as plt

########################################################################

rhosoot = 1850

e    = np.loadtxt('experiments.dat')
s1   = np.loadtxt('burner.out')
s2   = np.loadtxt('burner_MOMIC.out')
s3   = np.loadtxt('burner_HMOM.out')

xe  = e[:, 0] * 100
xs1  = s1[ :,0] * 100
xs2  = s2[ :,0] * 100
xs3  = s3[ :,0] * 100
ye  = e[:,1] * 1E6
ys1  = s1[ :,2] * 1E6 / rhosoot
ys2  = s2[ :,2] * 1E6 / rhosoot
ys3  = s3[ :,2] * 1E6 / rhosoot

ie1 = range(0,10)               # Xu and Faeth Laser indices
ie2 = range(10,19)              # Xu and Faeth Sampling indices
ie3 = range(19,50)              # Menon Laser indices

#-------------- SET UP SOME PLOT BOILERPLATE

matplotlib.rcParams.update({'font.size':20, 'figure.autolayout': True}) 
fig, ax = plt.subplots()
ax.tick_params(which='both', direction='in', top=True, right=True)
plt.cla()

#-------------- MAKE THE PLOT

ax.plot(xs1, ys1,   '-',  color='black',  linewidth=2) 
ax.plot(xs2, ys2,   '-',  color='blue',  linewidth=2) 
ax.plot(xs3, ys3,   '-',  color='gray',  linewidth=2) 
ax.plot(xe[ie1], ye[ie1],   'o',  color='black',  markersize=4) 
ax.plot(xe[ie2], ye[ie2],   's',  color='black',  markersize=4) 
ax.plot(xe[ie3], ye[ie3],   '^',  color='black',  markersize=4) 

ax.set_xlabel("z (cm)", fontsize=22)
ax.set_ylabel(r"$f_v$ (ppmv)",fontsize=22)
ax.set_yscale('log')
ax.set_xlim([0,3])
ax.set_ylim([1E-4,10])

ax.xaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())

ax.legend(['SootLib1','MOMIC','HMOM', 'Xu & Faeth Laser', 'Xu & Faeth Sampling', 'Menon Laser'], loc='lower right', frameon=False, fontsize=16)

#-------------- SAVE PLOT TO FILE

plt.savefig("burner.pdf")

