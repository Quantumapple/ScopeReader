import h5py
import numpy as np
import matplotlib.pyplot as plt
from scipy import optimize

def poly1d(x, a, b):
    return a * x + b

def poly3d(x, a, b, c, d):
    return a*pow(x,3)+b*pow(x,2)+c*pow(x,1)+d

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

t0 = rng[4]
npoints = rng[1]
dt = rng[3]
ymult = 0.004

xmin = (int)(825)
xmax = (int)(850)

#params, params_covariance = optimize.curve_fit(poly1d, np.arange(xmin, xmax), dataset[1, xmin:xmax]*ymult, p0=[-10,1])
params, params_covariance = optimize.curve_fit(poly3d, np.arange(xmin, xmax), dataset[1, xmin:xmax]*ymult, p0=[1,1,1,1])
print(params)

#ymax = optimize.fmin(lambda x: -poly3d(np.arange(xmin, xmax), params[0], params[1], params[2], params[3]), 0)
#print(ymax)

plt.figure(figsize=(12,8))
#plt.scatter(np.arange(xmin, xmax), dataset[1, xmin:xmax]*ymult, label='Data')
plt.scatter(np.arange(npoints), dataset[1, npoints*0:npoints*1]*ymult, label='Data')
#plt.plot(np.arange(xmin, xmax), poly1d(np.arange(xmin, xmax), params[0], params[1]), label='Fitted function')
plt.plot(np.arange(xmin, xmax), poly3d(np.arange(xmin, xmax), params[0], params[1], params[2], params[3]), label='Fitted function', c='r')
plt.legend(loc='best')
plt.grid(True)
plt.title("Scope")
plt.xlabel("time(s)")
plt.ylabel("amplitude(mV)")
plt.show()
#plt.savefig('fig_scope_ch2_2nd.pdf')
#print("t0: ", t0)
#ymax = test_func(xmax, params[0], params[1])
#yt1= ymax*0.8
#t1 = (yt1 - params[1])/params[0]
#print(t1*dt)
#print(t1*dt-t0)
