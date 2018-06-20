import numpy as np
import matplotlib.pyplot as plt
import math

X = []
Y = []


with open("output_lagrange.txt", 'r') as file:
	for line in file:
		asd= line.rstrip('\n').split()
		print(asd)
		X.append( float(asd[0]) )
		Y.append( float(asd[1]) )

plt.axes([0., 0., 1, 1])

print(X)
print(Y)

plt.scatter(X, Y, s=10, c='black', alpha=.5)
# plt.xlim(0, 5)
# plt.xticks(())
# plt.ylim(0, 1)
# plt.yticks(())

plt.rc('grid', linestyle="-", color='black')
plt.grid(True)

plt.show()
