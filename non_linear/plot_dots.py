import numpy as np
import matplotlib.pyplot as plt
import math






n = 1024
X = np.random.normal(0, 1, n)
Y = np.random.normal(0, 1, n)
T = np.arctan2(Y, X)

plt.axes([0., 0., 1, 1])
plt.scatter(X, Y, s=10, c=T, alpha=.5)

plt.xlim(-1.5, 1.5)
plt.xticks(())
plt.ylim(-1.5, 1.5)
plt.yticks(())

rr = np.arange(-1.5, 1.5, 0.0001)

def f_1(x): 
    return np.sqrt( -1*(x*x) + 1 )

def f_2(x): 
    return -1*np.sqrt( -1*(x*x) + 1 )

def f_3(x): 
    return (x*x)

plt.plot(rr, f_1(rr))
plt.plot(rr, f_2(rr))
plt.plot(rr, f_3(rr))

plt.show()