# import necessary files
import serial
import numpy as np 
from matplotlib import pyplot as plt
from scipy.signal import savgol_filter

def readArduinoData():
    """
    DOCSTRING: this is the function for reading data from the arduino
    return   : function will return a 3xn matrix containg RGB data and averaged 1D array
    """
    
    # here finds the port which arduino connected to
    data = []
    PORT = 0
    while True:
        try:
            RGBcircuit = serial.Serial("COM"+str(PORT), baudrate=9600, timeout=1)
            break
        except:
            PORT = PORT + 1

    print("PORT Connected to COM" + str(PORT))

    # now we get 1000 samples from the sensor circuit
    for index in range(1000):
        try:
            tempData = list(map(int, RGBcircuit.readline().decode('utf-8')[:-1].split(",")))
            data.append(tempData)
        
            if index % 100 == 0:
                print("Progress -> {} %".format(index / 10))

        except UnicodeDecodeError:
            pass

        except KeyboardInterrupt:
            exit()

        except ValueError:
            pass

    print("Progress -> 100%")
    
    RGBcircuit.close()
    data = np.array(data, dtype="int16")
    average = np.mean(data, axis=1)
   
    return data, average

def smooth(y, box_pts):
    """
    DOCSTRING: this function will average neareby samples and calculate the best fitting line
    return   : smoothed cureve of y
    """
    box = np.ones(box_pts)/box_pts
    y_smooth = np.convolve(y, box, mode='same')

    return y_smooth

def regressionProc(results, single = False):
    """
    DOCSTRING : This function will process given average and return R, G, B according to regression
    results   : This is the raw average. (Could be the matrix or single)
    single    : This is the switch between single and matrix mode
    """
    if not single:
        red   = 40.5785 * np.sqrt(results[:, 3] -42.1185) - RegressionConst[0]
        green = 0.01989 * np.power(results[:, 3] + 347.788, 1.5) - RegressionConst[1]
        blue  = 0.02475 * np.power(results[:, 3] + 460.702 , 1.5) - RegressionConst[2]
    
    else:
        red   = 40.5785 * np.sqrt(results -42.1185) + RegressionConst[0]
        green = 0.01989 * np.power(results + 347.788, 1.5) + RegressionConst[1]
        blue  = 0.02475 * np.power(results + 460.702 , 1.5) + RegressionConst[2]
    
    return red, green, blue

def findRegressionConsts(results):
    """
    DOCSTRING : this function will calculate the regression constant
    reuslts   : this is the matxis containing original RGB values and averages
    """
    
    # get random indexes to get samples from the samples
    randomIndexes = np.random.randint(low = 20, high = results.shape[0] - 20, size = 10)
    
    diffs = []
    
    # for every random index get the difference between calculation and sample
    for _, randIndex in enumerate(randomIndexes):
        tempRow = results[randIndex]
        tempAvg = tempRow[3] # average key in the selected row
        tR, tG, tB = regressionProc(tempAvg, single=True) # do regression for the selected row
        diffs.append([tR - tempRow[0], tG - tempRow[1], tB - tempRow[2]]) # get differences between reg and real
        
    diffs = np.array(diffs, dtype="float64")
    diffs = np.mean(diffs, axis = 0)
    
    return diffs

def processRatio(average, data):
    """
    DOCSTRING: this function will process regression compare and plot graphs for us
    average  : average array
    data     : 3xn RGB data array
    """
    
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

    _ , ax = plt.subplots(1, 1, sharex=True, figsize = (18, 14))

    ax.set_ylim(150, 800)
    
    xlimits = (np.min(results[:, 3]) + 21, np.max(results[:, 3]) - 21)
    ax.set_xlim(xlimits[0], xlimits[1])

    major_xticks = np.arange(xlimits[0], xlimits[1], 50)
    minor_xticks = np.arange(xlimits[0], xlimits[1], 10)

    major_yticks = np.arange(150, 850, 50)
    minor_yticks = np.arange(150, 850, 10)


    ax.set_xlabel("Average Between RGB readings")

    ax.set_title("Average vs RGB Raw readings and Regression")
    ax.set_ylabel("RGB Raw Readings")

    ax.plot(results[:, 3], smooth(results[:, 0], 20), 'r', label="Red")
    ax.plot(results[:, 3], smooth(results[:, 1], 20), 'g', label="Green")
    ax.plot(results[:, 3], smooth(results[:, 2], 20), 'b', label="Blue")

    # find the regressing constants and assign those
    global RegressionConst
    RegressionConst = np.array([0, 0, 0], dtype="float64") # first set to zero
    RegressionConst = findRegressionConsts(results)
    #red green blue equation
    red, green, blue = regressionProc(results)

    ax.plot(results[:, 3], red,   'r--', label="Red calculated")
    ax.plot(results[:, 3], green, 'g--', label="Green calculated")
    ax.plot(results[:, 3], blue , 'b--', label="Blue calculated")


    ax.set_xticks(major_xticks)
    ax.set_xticks(minor_xticks, minor=True)
    ax.set_yticks(major_yticks)
    ax.set_yticks(minor_yticks, minor=True)

    # And a corresponding grid
    ax.grid(which='both')
    ax.legend(loc = 'upper left')

def InverteReadings(data):
    """
    DOCSTRING: this is the function to inverte given data and find corresponding intensity
    data     : data to be inverted
    return   : will return 3 arrays
    """
    
    IR = np.power((data[:, 0] + RegressionConst[0]) / 40.5785, 2) + 42.1185
    IG = np.power((data[:, 1] + RegressionConst[1]) / 0.02052, 2/3) - 347.788
    IB = np.power((data[:, 2] + RegressionConst[2]) / 0.02475, 2/3) - 460.702

    return IR, IG, IB

def plotReadedData(data, average, title):
    _, ax = plt.subplots(2, 1, sharex=True, figsize = (18, 14))

    t = np.arange(0, data[:, 0].shape[0], 1)

    plt.suptitle(title)

    ax[0].set_title("Original Readings without Processing")
    ax[0].set_ylabel("Light Intensity")
    ax[0].plot(t, data[:, 0], 'r--', label="Red Reading")
    ax[0].plot(t, data[:, 1], 'g--', label="Green Reading")
    ax[0].plot(t, data[:, 2], 'b--', label="Blue Reading")
    ax[0].plot(t, average, 'k', label="Average")
    ax[0].grid()
    ax[0].legend(loc = 'upper left')

    R, G, B = InverteReadings(data)

    ax[1].set_title("Readings after process with regression")
    ax[1].set_xlabel("N Samples")
    ax[1].set_ylabel("Intensity")
    ax[1].plot(t, R, 'r')
    ax[1].plot(t, G, 'g')
    ax[1].plot(t, B, 'b')
    ax[1].grid()


# this is the global regression constant that we need to find using samples
RegressionConst = np.array([0, 0, 0], dtype="float64")

def main():
    _ = input("Do you want to calibrate the sensor? ").strip().upper()
    input("Press Enter when you are ready with a white paper")
    data, average = readArduinoData()
    processRatio(average, data)
    plotReadedData(data, average, "White Calibration Paper")

    if bool(int(input("Do you want to read calibration Information(1/0)? ").strip())):
        plt.show()

    print(RegressionConst, end = "\n\n")

    continue_ = True
    while continue_:
        continue_ = bool(int(input("Do you want to continue reading data(1/0)? ").strip()))
        if(continue_):
            title = input("Enter the title for the Reading -> ").strip()
            data, average = readArduinoData()
            plotReadedData(data, average, title)
            print("\n\n")

    plt.show()

if __name__ == "__main__":
    main()