import numpy as np
from matplotlib import pyplot as plt
import soundfile as sf
from scipy.io import wavfile as read
from scipy.signal import spectrogram, lfilter, freqz, tf2zpk
from scipy import signal

# nacitanie nahravok, dlzka vo vzorkoch a v sekundach, min a max hodnota
fs, s = read.read('../audio/xmatus35.wav')
# t = np.arange(s.size) / fs
minimalna_hodnota = min(s)
maximalna_hodnota = max(s)
pocet_vzorkov = s.size
pocet_sekund = s.size / fs
# print("minimalna hodnota: ", minimalna_hodnota)
# print("maximalna hodnota: ", maximalna_hodnota)
# print("pocet vzorkov: ", pocet_vzorkov)
# print("pocet sekund: ", pocet_sekund)

# ustrednenie a normalizacia
s1 = s - np.mean(s)
s1 = s1 / np.abs(s1).max()
# print("ustrednuta a normalizovana hodnota: ", s1)
# t = np.arange(s1.size) / fs

# rozdelenie na ramce o dlzke 1024 vzorkov s prekrytim 512 vzorkov + vyber ramca 25
frameCount = int(pocet_vzorkov / 768)
frameArray = np.ndarray((frameCount, 1024))
overlap = 256
positionStart = 0
positionEnd = 1024
for i in range(frameCount):
    if positionEnd <= len(s1):
        frameI = np.array(s1[positionStart: positionEnd])
        frameArray[i] = np.array(frameI)
    positionStart = int((1024 - overlap) * i)
    positionEnd = int(positionStart + 1024)
t = np.arange(frameArray[25].size) / fs + 1024 / fs * 768 * 25 / 1000

# pocitanie DFT
def dft(x):
    dft = np.ndarray((1024))
    for j in range(0, 1024):
        temp = 0
        for k in range(0, 1024):
            temp += x[k] * np.exp(-1j * ((2 * np.pi) / 1024) * j * k)
        dft[j] = temp
    return dft


dft = np.fft.fft(frameArray[:frameCount])
new_dft = 10 * np.log10(np.abs(dft)**2)

# urcenie rusivych frekvencii a generovanie kosinusoviek
f1 = 840
f2 = f1*2
f3 = f1*3
f4 = f1*4
y1 = np.cos(np.arange(pocet_vzorkov) * f1 * np.pi * 2 / fs)
y2 = np.cos(np.arange(pocet_vzorkov) * f2 * np.pi * 2 / fs)
y3 = np.cos(np.arange(pocet_vzorkov) * f3 * np.pi * 2 / fs)
y4 = np.cos(np.arange(pocet_vzorkov) * f4 * np.pi * 2 / fs)
y = (y1 + y2 + y3 + y4) / 192
f, t, sgr = spectrogram(y, fs)
# prevod na PSD
# (ve spektrogramu se obcas objevuji nuly, ktere se nelibi logaritmu, proto +1e-20)
sgr_log = 10 * np.log10(sgr+1e-20)
# sf.write('../audio/4cos.wav', y, fs)

# cistiaci filter
quality_factor = 30.0
b1_notch, a1_notch = signal.iirnotch(f1, quality_factor, fs)
freq, h = signal.freqz(b1_notch, a1_notch, fs = fs)
y1_notched = signal.filtfilt(b1_notch, a1_notch, s1)

b2_notch, a2_notch = signal.iirnotch(f2, quality_factor, fs)
freq, h = signal.freqz(b2_notch, a2_notch, fs = fs)
y2_notched = signal.filtfilt(b2_notch, a2_notch, y1_notched)

b3_notch, a3_notch = signal.iirnotch(f3, quality_factor, fs)
freq, h = signal.freqz(b3_notch, a3_notch, fs = fs)
y3_notched = signal.filtfilt(b3_notch, a3_notch, y2_notched)

b4_notch, a4_notch = signal.iirnotch(f4, quality_factor, fs)
freq, h = signal.freqz(b4_notch, a4_notch, fs = fs)
y4_notched = signal.filtfilt(b4_notch, a4_notch, y3_notched)

f, t, sgr = spectrogram(y4_notched, fs)
sgr_log = 10 * np.log10(sgr+1e-20)

# impulsni odezva
N_imp = 32
imp = [1, *np.zeros(N_imp-1)] # jednotkovy impuls
h1 = lfilter(b1_notch, a1_notch, imp)
h2 = lfilter(b2_notch, a2_notch, imp)
h3 = lfilter(b3_notch, a3_notch, imp)
h4 = lfilter(b4_notch, a4_notch, imp)

# plt.figure(figsize=(9,5))
# plt.stem(np.arange(N_imp), h1, basefmt=' ')
# plt.gca().set_xlabel('$n$')
# plt.gca().set_title('Impulsní odezva prvého filtru(840Hz) $h[n]$')
# plt.grid(alpha=0.5, linestyle='--')
# plt.tight_layout()
# plt.show()

# plt.figure(figsize=(9,5))
# plt.stem(np.arange(N_imp), h2, basefmt=' ')
# plt.gca().set_xlabel('$n$')
# plt.gca().set_title('Impulsní odezva druhého filtru(1680Hz) $h[n]$')
# plt.grid(alpha=0.5, linestyle='--')
# plt.tight_layout()
# plt.show()

# plt.figure(figsize=(9,5))
# plt.stem(np.arange(N_imp), h3, basefmt=' ')
# plt.gca().set_xlabel('$n$')
# plt.gca().set_title('Impulsní odezva tretieho filtru(2520Hz) $h[n]$')
# plt.grid(alpha=0.5, linestyle='--')
# plt.tight_layout()
# plt.show()

# plt.figure(figsize=(9,5))
# plt.stem(np.arange(N_imp), h4, basefmt=' ')
# plt.gca().set_xlabel('$n$')
# plt.gca().set_title('Impulsní odezva štvrtého filtru(3360Hz) $h[n]$')
# plt.grid(alpha=0.5, linestyle='--')
# plt.tight_layout()
# plt.show()

t = np.arange(s1.size) / fs
# sf.write('../audio/clean_bandstop.wav', y4_notched, fs)

#frekvencna charakteristika
_, ax = plt.subplots(1, 2, figsize=(8,3))
w, H = freqz(b1_notch, a1_notch)
ax[0].plot(w / 2 / np.pi * fs, np.abs(H))
ax[0].set_xlabel('Frekvence [Hz]')
ax[0].set_title('Modul frekvenční charakteristiky 1. filtru $|H(e^{j\omega})|$')

ax[1].plot(w / 2 / np.pi * fs, np.angle(H))
ax[1].set_xlabel('Frekvence [Hz]')
ax[1].set_title('Argument frekvenční charakteristiky 1. filtru $\mathrm{arg}\ H(e^{j\omega})$')

for ax1 in ax:
    ax1.grid(alpha=0.5, linestyle='--')
plt.tight_layout()
plt.show()

_, ax = plt.subplots(1, 2, figsize=(8,3))
w, H = freqz(b2_notch, a2_notch)
ax[0].plot(w / 2 / np.pi * fs, np.abs(H))
ax[0].set_xlabel('Frekvence [Hz]')
ax[0].set_title('Modul frekvenční charakteristiky 2. filtru $|H(e^{j\omega})|$')

ax[1].plot(w / 2 / np.pi * fs, np.angle(H))
ax[1].set_xlabel('Frekvence [Hz]')
ax[1].set_title('Argument frekvenční charakteristiky 2. filtru $\mathrm{arg}\ H(e^{j\omega})$')

for ax1 in ax:
    ax1.grid(alpha=0.5, linestyle='--')
plt.tight_layout()
plt.show()

_, ax = plt.subplots(1, 2, figsize=(8,3))
w, H = freqz(b3_notch, a3_notch)
ax[0].plot(w / 2 / np.pi * fs, np.abs(H))
ax[0].set_xlabel('Frekvence [Hz]')
ax[0].set_title('Modul frekvenční charakteristiky 3. filtru $|H(e^{j\omega})|$')

ax[1].plot(w / 2 / np.pi * fs, np.angle(H))
ax[1].set_xlabel('Frekvence [Hz]')
ax[1].set_title('Argument frekvenční charakteristiky 3. filtru $\mathrm{arg}\ H(e^{j\omega})$')

for ax1 in ax:
    ax1.grid(alpha=0.5, linestyle='--')
plt.tight_layout()
plt.show()

_, ax = plt.subplots(1, 2, figsize=(8,3))
w, H = freqz(b4_notch, a4_notch)
ax[0].plot(w / 2 / np.pi * fs, np.abs(H))
ax[0].set_xlabel('Frekvence [Hz]')
ax[0].set_title('Modul frekvenční charakteristiky 4. filtru $|H(e^{j\omega})|$')

ax[1].plot(w / 2 / np.pi * fs, np.angle(H))
ax[1].set_xlabel('Frekvence [Hz]')
ax[1].set_title('Argument frekvenční charakteristiky 4. filtru $\mathrm{arg}\ H(e^{j\omega})$')

for ax1 in ax:
    ax1.grid(alpha=0.5, linestyle='--')
plt.tight_layout()
plt.show()

# Nulove body a poly
z1, p1, k1 = tf2zpk(b1_notch, a1_notch)
z2, p2, k2 = tf2zpk(b2_notch, a2_notch)
z3, p3, k3 = tf2zpk(b3_notch, a3_notch)
z4, p4, k4 = tf2zpk(b4_notch, a4_notch)

plt.figure(figsize=(4, 3.5))
# jednotkova kruznice
ang = np.linspace(0, 2*np.pi, 100)
plt.plot(np.cos(ang), np.sin(ang))
# nuly, poly
plt.scatter(np.real(z1), np.imag(z1), marker='o', facecolors='none', edgecolors='r', label='nuly')
plt.scatter(np.real(p1), np.imag(p1), marker='x', color='g', label='póly')
plt.gca().set_xlabel('Realná složka 1.filtru $\mathbb{R}\{$z$\}$')
plt.gca().set_ylabel('Imaginární složka 1.filtru $\mathbb{I}\{$z$\}$')
plt.grid(alpha=0.5, linestyle='--')
plt.legend(loc='upper left')
plt.tight_layout()
plt.show()

plt.figure(figsize=(4, 3.5))
# jednotkova kruznice
ang = np.linspace(0, 2*np.pi, 100)
plt.plot(np.cos(ang), np.sin(ang))
# nuly, poly
plt.scatter(np.real(z2), np.imag(z2), marker='o', facecolors='none', edgecolors='r', label='nuly')
plt.scatter(np.real(p2), np.imag(p2), marker='x', color='g', label='póly')
plt.gca().set_xlabel('Realná složka 2.filtru $\mathbb{R}\{$z$\}$')
plt.gca().set_ylabel('Imaginární složka 2.filtru $\mathbb{I}\{$z$\}$')
plt.grid(alpha=0.5, linestyle='--')
plt.legend(loc='upper left')
plt.tight_layout()
plt.show()

plt.figure(figsize=(4, 3.5))
# jednotkova kruznice
ang = np.linspace(0, 2*np.pi, 100)
plt.plot(np.cos(ang), np.sin(ang))
# nuly, poly
plt.scatter(np.real(z3), np.imag(z3), marker='o', facecolors='none', edgecolors='r', label='nuly')
plt.scatter(np.real(p3), np.imag(p3), marker='x', color='g', label='póly')
plt.gca().set_xlabel('Realná složka 3.filtru $\mathbb{R}\{$z$\}$')
plt.gca().set_ylabel('Imaginární složka 3.filtru $\mathbb{I}\{$z$\}$')
plt.grid(alpha=0.5, linestyle='--')
plt.legend(loc='upper left')
plt.tight_layout()
plt.show()

plt.figure(figsize=(4, 3.5))
# jednotkova kruznice
ang = np.linspace(0, 2*np.pi, 100)
plt.plot(np.cos(ang), np.sin(ang))
# nuly, poly
plt.scatter(np.real(z4), np.imag(z4), marker='o', facecolors='none', edgecolors='r', label='nuly')
plt.scatter(np.real(p4), np.imag(p4), marker='x', color='g', label='póly')
plt.gca().set_xlabel('Realná složka 4.filtru $\mathbb{R}\{$z$\}$')
plt.gca().set_ylabel('Imaginární složka 4.filtru $\mathbb{I}\{$z$\}$')
plt.grid(alpha=0.5, linestyle='--')
plt.legend(loc='upper left')
plt.tight_layout()
plt.show()

# vypisovanie (prisposobovane aktualnemu vypisu)
# plt.figure(figsize=(9, 5))
# plt.pcolormesh(t, f, sgr_log)
# plt.plot(t, y4_notched)
# plt.gca().set_xlabel('$t[s]$')
# plt.gca().set_xlabel('$f[Hz]$')
# plt.gca().set_title('Frekvenčná charakteristika filtrov')
# cbar = plt.colorbar()
# cbar.set_label('Spektralní hustota výkonu [dB]', rotation=270, labelpad=15)
# plt.grid(alpha=0.5, linestyle='--')
# plt.tight_layout()
# plt.show()
