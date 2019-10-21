import h5py
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

verbose = False

path = "/home/jongho/Physics/MTD/LGAD_ETROC0/ScopeReader/_inputHd5/"
filename = "laser.hd5"

f = h5py.File(path+filename,'r')
#print(list(f.keys()))

dataset = f['C0']
#print(dataset.shape[0])

rng = f.attrs['Waveform Attributes'].tolist()

if verbose :
    print "What's inside in the 'waveform attributes': "
    print "channel mask"+",", "number of points"+",", "number of frames"+",", u"\N{GREEK CAPITAL LETTER DELTA}"+"t"+",", "t0"+",", "y multiply values"+",", "y offsets"+",", "y zero"
    print rng

npoints = rng[1]
dt = rng[3]
ymult = 0.004

xarray = np.arange(rng[1])*rng[3]

if verbose :
    print xarray

ch1 = np.arange(dataset[0, rng[1]:rng[1]*2])*ymult
#ch2 = np.arange(dataset[1, rng[1]:rng[1]*2])*ymult


#print(np.arange(rng[1]*2-rng[1])*rng[3])

#plt.plot(np.arange(rng[1]*2)*rng[3], dataset[0, rng[1]*1:rng[1]*3]*0.004)
#plt.plot(np.arange(rng[1])*rng[3], dataset[0, rng[1]*1:rng[1]*2])
#plt.show()





