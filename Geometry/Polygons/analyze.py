import numpy as np
import matplotlib.pyplot as plt
def read(path):
    vals = np.loadtxt(path)
    xs = vals[:,0]
    ys = vals[:,1]
    return xs,ys
plt.plot(*read("chocolate.out"))
plt.plot(*read("optimal.out"),'.')
plt.show()