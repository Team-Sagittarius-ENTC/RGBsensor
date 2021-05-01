# !usr/bin/python


# import necessary files
import serial
import numpy as np 
from matplotlib import pyplot as plt

t = np.arange(0, 999, 1)

def readArduinoData():
    data = []
    PORT = 0
    while True:
        try:
            RGBcircuit = serial.Serial("COM"+str(PORT), baudrate=9600, timeout=1)
            break
        except:
            PORT = PORT + 1

    print("PORT Connected to COM" + str(PORT))

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

        except ValueError:
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

def processRatio(average, data):
    average = average.reshape(-1, 1).astype("int16") # reshape the average
    result = np.hstack((data, average)) # connect average with the data

    # Now it is time to group the data
    results=[]
    for x in sorted(np.unique(result[...,3])):
        results.append([    np.average(result[np.where(result[...,3]==x)][...,0]),
                            np.average(result[np.where(result[...,3]==x)][...,1]), 
                            np.average(result[np.where(result[...,3]==x)][...,2]), 
                            x])

    results = np.array(results, dtype="float64")
    for i in range(3):
        results[:,i] = results[:,i] / results[:,3]

    _ , ax = plt.subplots(1, 1, sharex=True, figsize = (18, 14))


    major_xticks = np.arange(np.min(results[:, 3]), np.max(results[:, 3]), 50)
    minor_xticks = np.arange(np.min(results[:, 3]), np.max(results[:, 3]), 10)

    major_yticks = np.arange(0.5, 1.5, 0.1)
    minor_yticks = np.arange(0.5, 1.5, 0.02)


    ax.set_xlabel("Average Between RGB readings")

    ax.set_title("Average vs Ratio Graph")
    ax.set_ylabel("Ratio")

    ax.plot(results[:, 3], results[:, 0], 'r', label="Red Ratio")
    ax.plot(results[:, 3], results[:, 1], 'g', label="Green Ratio")
    ax.plot(results[:, 3], results[:, 2], 'b', label="Blue Ratio")

    ax.set_xticks(major_xticks)
    ax.set_xticks(minor_xticks, minor=True)
    ax.set_yticks(major_yticks)
    ax.set_yticks(minor_yticks, minor=True)

    # And a corresponding grid
    ax.grid(which='both')


    ax.legend(loc = 'upper left')

def sayColor(t, average, data):
    #mean = np.mean(average)
    ratios = [1.1985, 0.94, 0.8849]

    data[:,0] = data[:, 0] / ratios[0]
    data[:,1] = data[:, 1] / ratios[1]
    data[:,2] = data[:, 2] / ratios[2]

    _ , ax = plt.subplots(1, 1, sharex=True, figsize = (18, 7))

    ax.set_xlabel("N Samples")

    ax.set_ylim((200, 700))
    major_yticks = np.arange(200, 700, 100)
    minor_yticks = np.arange(200, 700, 10)
    ax.set_yticks(major_yticks)
    ax.set_yticks(minor_yticks, minor=True)

    ax.set_title("Proccessed Data")
    ax.set_ylabel("Light Intensity")
    ax.plot(t, data[:, 0], 'r--', label="Red Reading")
    ax.plot(t, data[:, 1], 'g--', label="Green Reading")
    ax.plot(t, data[:, 2], 'b--', label="Blue Reading")
    
    
    ax.grid(which='both')
    ax.legend(loc = 'upper left')


def main():
    data, average = readArduinoData()
    plotData(t[:], data[:], average[:])
    processRatio(average[:], data[:])
    sayColor(t[:], average[:], data[:])

    plt.show()

if __name__ == "__main__":
    main()