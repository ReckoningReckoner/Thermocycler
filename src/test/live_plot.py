import matplotlib.pyplot as plt
import subprocess

PORT = '/dev/tty.lpss-serial2'
COMMAND = 'picocom ' + PORT
p = subprocess.Popen(COMMAND, shell=True,
                     stdout=subprocess.PIPE)

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
            plt.pause(1)
        except ValueError as e:
            continue
    print(line)

plt.plot(times, temperatures)
plt.show()
