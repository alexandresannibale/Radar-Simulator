"""
Created on Wed Jun 21 22:51:11 2023

@author: alexandre
"""

import numpy  as np
import matplotlib.pyplot as plt
import seaborn
seaborn.set(style="darkgrid")

Tx = np.loadtxt("VRxChirp.txt")
Rx = np.loadtxt("VRx.txt")
RxClean = np.loadtxt("RxKaleen.txt")
conv = np.loadtxt("convolutionSignal.txt")

us = 1e-6

plt.close("all")
fig = plt.figure(figsize=(12,7))
ax = fig.subplots(2,2)

ax[0,0].plot(Rx[:,0]/us, Rx[:,1])
ax[0,0].plot(RxClean[:,0]/us, RxClean[:,1])
ax[0,0].set_ylabel("Return Signal, Rx [$AU$]")
ax[0,0].grid(True)

ax[0,1].plot(Rx[:,0]/us, Rx[:,1])
ax[0,1].plot(RxClean[:,0]/us, RxClean[:,1])
ax[0,0].set_ylabel("Return Signal, Rx [$AU$]")
ax[0,1].grid(True)
ax[0,1].set_xlim(20.0, 20.5)

ax[1,0].plot(conv[:,0]/us, conv[:,1])
ax[1,0].grid(True)
ax[1,0].set_ylabel("Matched Filter, [$AU$]")
ax[1,0].set_xlabel("elapsed time, [$\mu s$]")

ax[1,1].plot(conv[:,0]/us, conv[:,1])
ax[1,1].grid(True)
ax[1,1].set_ylabel("Matched Filter, [$AU$]")
ax[1,1].set_xlim(6.55, 6.80)
ax[1,1].set_xlabel("elapsed time, [$\mu s$]")

fig.tight_layout()


fig.savefig("plot_signals_chirp_pulse_no_noise.png")
