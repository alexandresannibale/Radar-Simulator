"""
Created on Wed Jun 21 22:51:11 2023

@author: alexandre
"""

import numpy  as np
import matplotlib.pyplot as plt
import seaborn
seaborn.set(style="darkgrid")

x = np.loadtxt("convolutionSignal.txt")
Rx = np.loadtxt("Rx.txt")
reverse = np.loadtxt("reverse.txt")
plt.close("all")
plt.plot(x[:,0], x[:,1],"-o")
