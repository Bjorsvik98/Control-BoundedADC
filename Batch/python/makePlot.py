import matplotlib.pyplot as plt
import numpy as np
import cbadc
import math
from parsInput import parsFunc
from saveEstimator import *


N, beta, rho, kappa, amplitude, OSR, NumbersChecked, size, eta2, K1, K2, DSR, FixedPointBits, bits_used, fraction_bits, parallel, numCores = parsFunc()
N = int(N)
M = N
size = int(size)
amplitude = int(amplitude)
OSR = int(OSR)
K1 = int(K1)
# OSR = 512
# print("N = ", N, "M = ", M, "size = ", size, "amplitude = ", amplitude, "OSR = ", OSR)



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
# bits_used = FixedPointBits
max_floating_point_value = 1 << (bits_used-fraction_bits)

analog_signal = cbadc.analog_signal.Sinusoidal(amplitude, frequency, phase, NumbersChecked)
analog_system = cbadc.analog_system.AnalogSystem(A, B, CT, Gamma, Gamma_tildeT)
digital_control = cbadc.digital_control.DigitalControl(cbadc.analog_signal.Clock(T), M)
byte_stream = cbadc.utilities.read_byte_stream_from_file("sinusoidal_simulation.dat", M)
control_signal_sequences = cbadc.utilities.byte_stream_2_control_signal(byte_stream, M)
fixed_point = cbadc.utilities.FixedPoint(bits_used, max_floating_point_value)


digital_estimator = cbadc.digital_estimator.ParallelEstimator(
    analog_system, digital_control, eta2, K1
)
digital_estimator.warm_up()

digital_estimator(control_signal_sequences)
# print(digital_estimator)
# size = K2 << 4
u_hat = np.zeros(K1)
# u_hat = [0 for x in range(size)]
# u_hat = [0]*size
# print("size: ", size)
for index in range(int(K1)):
    u_hat[index] = next(digital_estimator)


# print("u_hat: ", u_hat)
# print("u_hat length: ", len(u_hat))
# print("size: ", size)

# u_hat = float_to_fixed(u_hat, FixedPointBits)
# for i in range(len(u_hat)):
#     # if u_hat[i] >= 32767:
#     #     u_hat[i] = 32766
#     u_hat[i] = fixed_point.float_to_fixed(u_hat[i])

# print(fixed_point)


# print(u_hat)

# t = np.arange(-K1 + 1, size - K1 + 1)
t = np.arange(K1)

with open('../result.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
A = [int(x) for x in result]


for i in range(len(A)):
    A[i] = fixed_point.fixed_to_float(A[i])


with open('resultDecimal.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
B = [int(x) for x in result]
B = B[:K1-1]
B.insert(0, 0)

for i in range(len(B)):
    B[i] = fixed_point.fixed_to_float(B[i])

# print("A: ", A)
# print("u_hat: ", u_hat.size)


t_ref = np.arange(0, size)

stf_at_omega = digital_estimator.signal_transfer_function(
    np.array([2 * np.pi * frequency])
)[0]
u = np.zeros_like(u_hat)
for index, tt in enumerate(t_ref[0:len(u)]):
    u[index] = analog_signal.evaluate(tt * T)

# convert to fixed point
# for i in range(len(u)):
#     u[i] = fixed_point.float_to_fixed(u[i])


########## SNR ##########
offset = 199
NumbersChecked = K1 - (offset * 2)
print("NumbersChecked: ", NumbersChecked)

noise = np.zeros(NumbersChecked)
for i in range(NumbersChecked):
    print("u_hat: ", u_hat[i+offset])
    print("u: ", u[i+offset+1])
    noise[i] = u[i+offset+1] - u_hat[i+offset]

# for i in range(len(noise)):
#     noise[i] = fixed_point.fixed_to_float(noise[i])
# print("noise: ", noise)


# get avarage of noise
noiseAvarage = 0
for i in range(NumbersChecked):
    noiseAvarage += noise[i]
noiseAvarage = noiseAvarage / NumbersChecked
# print("noiseAvarage: ", noiseAvarage)

#get RMS of noise
noiseRMS = 0
for i in range(NumbersChecked):
    noiseRMS += noise[i]**2
noiseRMS = noiseRMS / NumbersChecked
noiseRMS = math.sqrt(noiseRMS)
# print("noiseRMS: ", noiseRMS)



# get RMS of signal
signalRMS = 0
for i in range(NumbersChecked):
    signalRMS += u_hat[i]**2
signalRMS = signalRMS / NumbersChecked
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



file = open("u_hat.txt", "w+")
np.savetxt(file, u_hat, fmt="%d")
file.close()


# for i in range(len(A)-500):
#     print("A: ", A[i])
#     print("u_hat: ", u_hat[i])

# for i in range(len(u_hat)):
#     u_hat[i] = fixed_point.fixed_to_float(u_hat[i])

# for i in range(len(u)):
#     u[i] = fixed_point.fixed_to_float(u[i])

# for i in range(len(A)):
#     A[i] = fixed_point.fixed_to_float(A[i])




    

# print(B)
t = [x + 1 for x in t]


t2 = list(range(len(A)))
t2 = [i + 0/DSR for i in t2]
# t2 = [x * DSR for x in t2]
t2 = [x + 1 for x in t2]
t3 = list(range(len(B)))
t3 = [i + 0/DSR for i in t3]
t3 = [x * DSR for x in t3]
# plt.plot(t_down, u_hat[0:len(t_down)], label="$\hat{u}(t)$ Reference")
# for i in range(len(t)):
    # print("A: ", A[i], "u_hat: ", u_hat[i])

plt.plot(t_ref[0:(len(u))], stf_at_omega * u, label="$\mathrm{STF}(2 \pi f_u) * u(t)$")


plt.plot(t, u_hat, label="Reference signal")
# plt.plot(t2, A, label="Estimated signal")
# plt.plot(t3, B, label="Simulated")

# plt.xlabel("$t / T$")
plt.xlabel("Sample nr.")
# plt.ylabel("Amplitude")
plt.legend()
# plt.title("Estimated input signal")
plt.grid(which="both")
plt.xlim((offset, K1-offset))
# plt.xlim((0, K1))
plt.tight_layout()
plt.savefig("plot.svg")
plt.savefig("plot.png")
plt.show()



plt.figure()
plt.grid(which="both")
plt.plot(t[offset:(K1-offset)], noise, label="$\hat{u}(t)$ Reference")
plt.savefig("noise.png")


