import matplotlib.pyplot as plt
import subprocess
from datetime import datetime

PORT = '/dev/cu.usbmodem14131'
COMMAND = 'picocom ' + PORT
p = subprocess.Popen(COMMAND, shell=True,
                     stdout=subprocess.PIPE)
f = open('output' + datetime.now().strftime('%Y-%m-%d %H:%M:%S') + '.txt', 'w')

times = []
temperatures = []
plt.ion()
plt.figure()
plt.xlabel("Time [ms]")
plt.ylabel("Temperature [C]")

c = 0
while p.poll() is None:
    line = str(p.stdout.readline(), 'utf-8').replace('\n', '')

    data = line.split(",")
    if len(data) >= 2:
        try:
            times.append(float(data[0]))
            temperatures.append(float(data[1]))
            plt.plot(times, temperatures, '.', color='b')
            plt.draw()
            plt.pause(0.01)
        except ValueError as e:
            continue
    print(line)
    f.write(line)

plt.plot(times, temperatures)
plt.show()
