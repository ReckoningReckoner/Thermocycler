import numpy as np
import scipy.stats as stats

data = np.genfromtxt('./output.csv', delimiter=',')

j = 0
for i in range(9, len(data)):
    if j < 20:
        res = stats.linregress(data[i-9:i+1, 0], data[i-9:i+1, 1])
        theo = res[0]*1000

        real = data[i, 2]
        time = data[i, 0]
        print(time, real, theo, real-theo, (data[i-9:i+1, 0]**2).sum())

    else:
        break
