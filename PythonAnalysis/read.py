import h5py
import numpy as np
import matplotlib.pyplot as plt
from scipy import optimize

verbose = False

path = "/home/jongho/Physics/MTD/LGAD_ETROC0/ScopeReader/_inputHd5/"
filename = "laser.hd5"

f = h5py.File(path+filename,'r')
#print(list(f.keys()))

dataset = f['C0']
#print(dataset.shape[0])

rng = f.attrs['Waveform Attributes'].tolist()

if verbose :
    print("What's inside in the 'waveform attributes': ")
    print("channel mask"+",", "number of points"+",", "number of frames"+",", u"\N{GREEK CAPITAL LETTER DELTA}"+"t"+",", "t0"+",", "y multiply values"+",", "y offsets"+",", "y zero")
    print(rng)

npoints = rng[1]
dt = rng[3]
ymult = 0.004

xmin = (int)(npoints/2-10)
xmax = (int)(npoints/2+10)

#plt.figure(figsize=(12,8))
#plt.scatter(np.arange(xmin, xmax), dataset[0, xmin:xmax]*ymult)
#plt.scatter(np.arange(npoints), dataset[0, npoints:npoints*2]*ymult)
#plt.plot(np.arange(rng[1])*rng[3], dataset[0, rng[1]*1:rng[1]*2])
#plt.plot(np.arange(npoints)*dt, dataset[0, npoints:npoints*2]*ymult)

def test_func(x, a, b):
    return a * x + b

params, params_covariance = optimize.curve_fit(test_func, np.arange(xmin, xmax), dataset[0, xmin:xmax]*ymult, p0=[1,1])
print(params)

plt.figure(figsize=(12,8))
plt.scatter(np.arange(xmin, xmax), dataset[0, xmin:xmax]*ymult, label='Data')
plt.plot(np.arange(xmin, xmax), test_func(np.arange(xmin, xmax), params[0], params[1]),
        label='Fitted function')
plt.legend(loc='best')
plt.show()





