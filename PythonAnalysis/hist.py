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

for i in range(1,21):
    xmin = (int)(825+1024*i)
    xmax = (int)(850+1024*(i+1))

    params, params_covariance = optimize.curve_fit(poly3d, np.arange(xmin, xmax), dataset[1, xmin:xmax]*ymult, p0=[1,1,1,1])

    def f(x):
        return -(params[0]*pow(x,3)+params[1]*pow(x,2)+params[2]*pow(x,1)+params[3])

    maximumX = optimize.fminbound(f, xmin, xmax)
    maximumY = -f(maximumX)

    def f2(x):
        return params[0]*pow(x,3)+params[1]*pow(x,2)+params[2]*pow(x,1)+params[3]-(maximumY*0.8)

    root = optimize.root(f2, x0=(830+1024*i))
    t1 = root.x*dt

    plt.hist(t1-t0, 20)

plt.show()

#plt.figure(figsize=(12,8))
#plt.scatter(np.arange(xmin, xmax), dataset[1, xmin:xmax]*ymult, label='Data')
#plt.scatter(np.arange(npoints), dataset[1, npoints*0:npoints*1]*ymult, label='Data')
#plt.plot(np.arange(xmin, xmax), poly1d(np.arange(xmin, xmax), params[0], params[1]), label='Fitted function')
#plt.plot(np.arange(xmin, xmax), poly3d(np.arange(xmin, xmax), params[0], params[1], params[2], params[3]), label='Fitted function', c='r')
#plt.legend(loc='best')
#plt.grid(True)
#plt.title("Scope")
#plt.xlabel("time(s)")
#plt.ylabel("amplitude(mV)")
#plt.show()
