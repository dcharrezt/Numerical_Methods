import numpy as np
import matplotlib.pyplot as plt
import math

X = []
Y = []
C = []

with open("dots2.txt", 'r') as file:
	for line in file:
		asd= file.readline().rstrip('\n').split()
		if( len(asd) == 3 ):
			X.append( float(asd[0]) )
			Y.append( float(asd[1]) )
			C.append( str(asd[2]) )

plt.axes([0., 0., 1, 1])

plt.scatter(X, Y, s=1, c=C, alpha=.5)

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