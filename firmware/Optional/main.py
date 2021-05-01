# !usr/bin/python


# import necessary files
import serial
import numpy as np 
from matplotlib import pyplot as plt

t = np.arange(0, 999, 1)

def readArduinoData():
    data = []
    RGBcircuit = serial.Serial("COM7", baudrate=9600, timeout=1)
    for index in range(1000):
        try:
            tempData = list(map(int ,RGBcircuit.readline().decode()[:-1].split(", ")))
            data.append(tempData)
        
            if index % 100 == 0:
                print("Progress -> {} %".format(index / 10))

        except UnicodeDecodeError:
            pass

        except KeyboardInterrupt:
            exit()

    RGBcircuit.close()
    data = np.array(data, dtype="int16")
    average = np.mean(data, axis=1)
   
    return data, average

def plotData(t, data, average):
    _ , ax = plt.subplots(2, 1, sharex=True, figsize = (18, 14))

    ax[1].set_xlabel("N Samples")

    ax[0].set_title("Original Readings without Processing")
    ax[0].set_ylabel("Light Intensity")
    ax[0].plot(t, data[:, 0], 'r--', label="Red Reading")
    ax[0].plot(t, data[:, 1], 'g--', label="Green Reading")
    ax[0].plot(t, data[:, 2], 'b--', label="Blue Reading")
    ax[0].plot(t, average, 'k', label="Average")
    ax[0].grid()
    ax[0].legend(loc = 'upper left')


    ax[1].set_title("Ratio Between average and reading")
    ax[1].set_ylabel("Original Ratio")
    ax[1].plot(t, average / data[:, 0], 'r')
    ax[1].plot(t, average / data[:, 1], 'g')
    ax[1].plot(t, average / data[:, 2], 'b')
    ax[1].grid()

    plt.show()

def main():
    data, average = readArduinoData()
    plotData(t, data, average)

if __name__ == "__main__":
    main()