import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
bb= 0.2497
bd =5.16
ad =0.3105
ah =64.3
a = np.genfromtxt("datos.dat")
r,v =np.genfromtxt("RadialVelocities.dat",unpack=True)

figu= plt.figure()
modelo= np.zeros(len(r))
for i in range(len(r)):
	modelo[i]=np.sqrt(a[0]) *r[i]/(r[i]**2 + bb**2)**(3/2) + np.sqrt(a[1])*r[i]/ (r[i]**2 + (bd+ad)**2)**(3/2) + np.sqrt(a[2])/(r[i]**2 + ah**2)**(1/4)
scatterr= plt.scatter(r,v,s=100,color="green")
aprox= plt.plot(r,modelo)
figu.savefig("Plots.jpg")

