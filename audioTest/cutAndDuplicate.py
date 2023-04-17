import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as sciwav

notes = ["do1", "re1", "mi1", "fa1", "so1", "la1", "xi1", "do2", "re2", "mi2", "fa2", "so2", "la2", "xi2"]
for i in range(1):
    Fs, signal = sciwav.read(notes[i] + ".wav")
    N = len(signal)
    newSignal = signal[4000:6000]
    newSignal = np.vstack((newSignal, newSignal))
    newSignal = np.vstack((newSignal, newSignal))
    newSignal = np.vstack((newSignal, newSignal))
    newSignal = np.vstack((newSignal, newSignal))
    newSignal = np.vstack((newSignal, newSignal))
    plt.figure()
    plt.plot(signal)
    plt.xlabel("Time(s)")
    plt.ylabel("Amplitude")
    plt.title("Original signal(Time Domain)")
    plt.show()
    sciwav.write(notes[i] + ".mp3", Fs, newSignal)