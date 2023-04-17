import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as sciwav

filename = "do1.wav"
Fs, signal = sciwav.read(filename)
N = len(signal)

#normlise
signal_normlised = signal / pow(2, 15)
audio_lenth = N / Fs

#Get array of time axis.
time = np.linspace(0, audio_lenth, N)

# Plot Original Time Domain
plt.figure()
plt.plot(time, signal_normlised)
plt.xlabel("Time(s)")
plt.ylabel("Amplitude")
plt.title("Original signal(Time Domain)")

# FT and Original Freq Domain
fft = np.fft.fft(signal_normlised)
freq = np.linspace(0, Fs, N)
delta_f = Fs / N
f, ax = plt.subplots(1, 1)
plt.plot(freq, 20 * np.log10(abs(fft) / N))
plt.title("Original signal(Freq Domain)")
plt.xlabel("Frequency(Hz)")
plt.ylabel("Amplitude(dB)")
plt.xscale("log")
plt.show()
