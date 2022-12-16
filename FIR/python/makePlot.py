import matplotlib.pyplot as plt
import numpy as np
import math
import cbadc
from parsInput import parsFunc
from saveEstimator import *


N, beta, rho, kappa, amplitude, OSR, offset, size, eta2, K1, K2, DSR, bits_used, fraction_bits, outputFormat = parsFunc()
N = int(N)
M = N
# OSR = 512


CT = np.eye(N) # Set the amplification factor.

Gamma = []
for x in range(N):
    innerlist = []
    for y in range(N):
        if x == y:
            innerlist.append(kappa * beta)
        else:
            innerlist.append(0)
        
    Gamma.append(innerlist)

A = []
for x in range(N):
    innerlist = []
    for y in range(N):
        if x == y:
            innerlist.append(beta * rho)
        elif x == y+1:
            innerlist.append(beta)
        else:
            innerlist.append(0)
        
    A.append(innerlist)
    
B = []
for x in range(N):
    innerlist = []
    if x == 0:
        innerlist.append(beta)
    else:
        innerlist.append(0)
    B.append(innerlist)

Gamma_tildeT = CT
T = 1.0 / (2 * beta)
frequency = 1.0 / (T * OSR) # Choose the sinusoidal frequency via an oversampling ratio (OSR).
phase = np.pi / 3 # We also specify a phase an offset these are hovewer optional.
max_floating_point_value = 1 << (bits_used-fraction_bits)


analog_signal = cbadc.analog_signal.Sinusoidal(amplitude, frequency, phase, offset)
analog_system = cbadc.analog_system.AnalogSystem(A, B, CT, Gamma, Gamma_tildeT)
digital_control = cbadc.digital_control.DigitalControl(cbadc.analog_signal.Clock(T), M)
byte_stream = cbadc.utilities.read_byte_stream_from_file("sinusoidal_simulation.dat", M)
control_signal_sequences = cbadc.utilities.byte_stream_2_control_signal(byte_stream, M)
fixed_point = cbadc.utilities.FixedPoint(bits_used, max_floating_point_value)


digital_estimator = cbadc.digital_estimator.FIRFilter(
    analog_system, digital_control, eta2, K1, K2, fixed_point=fixed_point
)


digital_estimator(control_signal_sequences)
# print(digital_estimator)
# print(size)
u_hat = np.zeros(size)
# u_hat = [0 for x in range(size)]
# u_hat = [0]*size
for index in range(size-1):
    u_hat[index] = next(digital_estimator)


u_hat_fixed = np.zeros(size)

# u_hat = float_to_fixed(u_hat, FixedPointBits)
for i in range(len(u_hat)):
    u_hat_fixed[i] = fixed_point.float_to_fixed(u_hat[i])

# print(u_hat)

t = np.arange(-K1 + 1, size - K1 + 1)
t_down = np.arange(-(K1) // DSR, (size - K1) // DSR) * DSR + 1

with open('../result.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
A = [int(x) for x in result]

with open('resultDecimal.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
B = [int(x) for x in result]
B = B[:size-1]
# B.insert(0, 0)
# print(B)

# for i in range(len(A)):
#         A[i] = to_float(A[i], FixedPointBits)

file = open("u_hat.txt", "w+")
np.savetxt(file, u_hat_fixed, fmt="%d")
file.close()



# print(A)
for i in range(len(A)):
    A[i] = fixed_point.fixed_to_float(A[i])

# for i in range(len(B)):
#     B[i] = fixed_point.fixed_to_float(B[i])

t_ref = np.arange(0, size +  K1)

stf_at_omega = digital_estimator.signal_transfer_function(
    np.array([2 * np.pi * frequency])
)[0]
u = np.zeros_like(u_hat)
for index, tt in enumerate(t_ref[0:len(u)]):
    u[index] = analog_signal.evaluate(tt * T)


#### SNR ####
offset = size-K1-K1-1
noise = np.zeros(offset)
for i in range(offset):
    # print("A: ", A[i])
    # print("u: ", u[i+K1])
    noise[i] = u[i+K1+1] - A[i]
    # print("A: ", A[i], "u: ", u[i], "noise: ", noise[i])

# get avarage of noise
noiseAvarage = 0
for i in range(offset):
    noiseAvarage += noise[i]
noiseAvarage = noiseAvarage / offset
print("noiseAvarage: ", noiseAvarage)

#get RMS of noise
noiseRMS = 0
for i in range(offset):
    noiseRMS += noise[i]**2
noiseRMS = noiseRMS / offset
noiseRMS = math.sqrt(noiseRMS)
print("noiseRMS: ", noiseRMS)


# get RMS of signal
signalRMS = 0
for i in range(offset):
    signalRMS += A[i]**2
signalRMS = signalRMS / offset
signalRMS = math.sqrt(signalRMS)
print("signalRMS: ", signalRMS)

# get SNR
SNR = 0
# for i in range(80):
#     SNR += (noise[i] - noiseAvarage)**2
# SNR = SNR / 80
# SNR = math.sqrt(SNR)
SNR = 20 * math.log10(signalRMS / noiseRMS)
print("SNR: ", SNR)


test = list(range(len(A)))

# print(A)
t2 = list(range(len(A)))
t2 = [i + K2/DSR for i in t2]
t2 = [x * DSR+1 for x in t2]
t3 = list(range(len(B)))
t3 = [i + K2/DSR for i in t3]
t3 = [x * DSR for x in t3]
# plt.plot(t_down, u_hat[0:len(t_down)], label="$\hat{u}(t)$ Reference")
# plt.plot(t, u_hat, label="$\hat{u}(t)$ Reference")
plt.plot(t2, A, label="Calculated ")
# plt.plot(t3, B, label="Simulated")
# plt.plot(test, A)


plt.plot(t_ref[0:(len(u))], stf_at_omega * u, label="$\mathrm{STF}(2 \pi f_u) * u(t)$")




plt.xlabel("$t / T$")
plt.legend()
plt.title("Estimated input signal")
plt.grid(which="both")
plt.xlim((K1, size - K1-1))
plt.tight_layout()
plt.savefig("plot.png")
plt.savefig("plot.svg")
plt.show()

t = np.arange(len(noise))

plt.figure()
plt.plot(t, noise, label="$\hat{u}(t)$ Reference")
plt.savefig("noise.png")




