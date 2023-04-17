import numpy as np
import scipy.io.wavfile as sciwav

freqs = [349, 392, 440, 497, 523, 587, 659, 698, 784, 880, 988, 1046, 1175, 1318]
for i in range(len(freqs)):
    freqs[i] = freqs[i] - 100

notes = ["do1", "re1", "mi1", "fa1", "so1", "la1", "xi1", "do2", "re2", "mi2", "fa2", "so2", "la2", "xi2"]
Fs = 44100
time = np.linspace(0, 2, 2 * Fs)
maxAmplitude = 12000
for i in range(len(freqs)):
    sinWave = maxAmplitude * np.sin(2 * np.pi * freqs[i] * time)
    sinWave.astype("int16")
    sciwav.write(notes[i] + ".mp3", Fs, sinWave)
