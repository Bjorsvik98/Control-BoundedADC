"""
Simulating a Control-Bounded ADC
================================

This example shows how to simulate the interactions between an analog system
and a digital control while the former is excited by an analog signal.
"""


import matplotlib.pyplot as plt
import cbadc
import numpy as np
from saveEstimator import *
from parsInput import parsFunc

N, beta, rho, kappa, amplitude, OSR, offset, size, eta2, K1, K2, DSR, FixedPointBits, bits_used, fraction_bits, parallel = parsFunc()
N = int(N)
OSR = int(OSR)

# OSR = 512

###############################################################################
# The Analog System

M = N # We fix the number of analog states.
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
# end_time = T * size
# bits_used = bits_used
# print("bits_used: ", bits_used)
max_floating_point_value = 1 << (bits_used-fraction_bits)

analog_signal = cbadc.analog_signal.Sinusoidal(amplitude, frequency, phase, offset)
analog_system = cbadc.analog_system.AnalogSystem(A, B, CT, Gamma, Gamma_tildeT)
digital_control = cbadc.digital_control.DigitalControl(cbadc.analog_signal.Clock(T), M)
fixed_point = cbadc.utilities.FixedPoint(bits_used, max_floating_point_value)

# print(analog_signal)


###############################################################################
# read and write controll signal
byte_stream = cbadc.utilities.read_byte_stream_from_file("sinusoidal_simulation.dat", M)
control_signal_sequences = cbadc.utilities.byte_stream_2_control_signal(byte_stream, M)

S = [[0]*N]*size
file = open("../BatchFiles/control_signal_sequences.txt", "w")
line = "{} {}\n".format(size, M)
file.write(line)
for x in range(size-1):
    line = list(next(control_signal_sequences))
    S[x] = line
    outLine = ', '.join(map(str, line)) + '\n'
    file.write(outLine)

file.close()
#################

###############################################################################


# digital_estimator = cbadc.digital_estimator.BatchEstimator(
#     analog_system, digital_control, eta2, K1, K2, fixed_point=fixed_point
# )
# digital_estimator(control_signal_sequences)

digital_estimator = cbadc.digital_estimator.ParallelEstimator(
    analog_system, digital_control, eta2, K1, K2
)
digital_estimator(control_signal_sequences)

# fM = [[0]*N]*(size+1)
# fm = np.zeros((size+1), N)
fM = np.empty(shape=(size+1,N),dtype=complex)
fM.fill(0)
# bM = [[0]*N]*(size+1)
# bM = np.zeros((size+1), N)
bM = np.empty(shape=(size+1,N),dtype=complex)
bM.fill(0)
output = np.zeros(size)

for n in range(N):
    for k2 in range(size):
        tempFBS = 0
        for m in range(N):
            if S[k2-1][m] == 1:
                tempFBS += digital_estimator.forward_b[n][m]
            else:
                tempFBS -= digital_estimator.forward_b[n][m]

            # print("tempFBS",k2,m,"=",tempFBS)
        fM[k2][n] = (digital_estimator.forward_a[n] * fM[k2-1][n]) + tempFBS
        print("fM[{0}][{1}] = {2}".format(k2, n, fM[k2][n]))

        k3 = size - k2
        tempBBS = 0
        for m in range(N):
            if S[k3-1][m] == 1:
                tempBBS += digital_estimator.backward_b[n][m]
            else:
                tempBBS -= digital_estimator.backward_b[n][m]


        bM[k3-1][n] = (digital_estimator.backward_a[n] * bM[k3][n]) + tempBBS
        # print("bM[{}][{}] = {}".format(k3-1, n, bM[k3-1][n]), "backward_a[{}] = {}".format(n, digital_estimator.backward_a[n].real), "bM[{}][{}] = {}".format(k3, n, bM[k3][n]), "tempBBS = {}".format(tempBBS))
        # print("bM[1][0] = ", bM[1][0], "bM[2][0] = ", bM[2][0])
        
        # print("bM[",k3-1,"][",n,"]:", bM[k3-1][n])
        # print("bm[{0}][{1}] = {2}".format(k3-1, n, bM[k3-1][n]))




for k4 in range(size):
    temp = 0
    for n in range(N):
        tempFWFM = 0
        tempBWFM = 0
        tempFWFM = digital_estimator.forward_w[0][n] * fM[k4][n]
        # print("tempFWFM", tempFWFM,"forward_w[0][",n,"]" , digital_estimator.forward_w[0][n].real, "fM[",k4,"][",n,"]", fM[k4][n])
        tempBWFM = digital_estimator.backward_w[0][n] * bM[k4][n]
        
        # print("tempBWFM", tempBWFM,"backward_w[0][",n,"]" , digital_estimator.backward_w[0][n].real, "bM[",k4,"][",n,"]", bM[k4][n])
        temp += tempFWFM 
        temp += tempBWFM
        
    output[k4] = temp
    # print("output: ", output[k4])


"""


byte_stream = cbadc.utilities.read_byte_stream_from_file("sinusoidal_simulation.dat", M)
control_signal_sequences = cbadc.utilities.byte_stream_2_control_signal(byte_stream, M)
fixed_point = cbadc.utilities.FixedPoint(bits_used, max_floating_point_value)


digital_estimator = cbadc.digital_estimator.ParallelEstimator(
    analog_system, digital_control, eta2, K1, K2
)


digital_estimator(control_signal_sequences)



u_hat = np.zeros(size)
for index in range(size-K1):
    u_hat[index] = next(digital_estimator)

for i in range(len(u_hat)):
    if u_hat[i] >= 32767:
        u_hat[i] = 32766

t = np.arange(-K1 + 1, size - K1 + 1)
t = np.arange(size)

t2 = list(range(len(output)))
# t2 = list(range(1700))
t2 = [i + 0/DSR for i in t2]
t2 = [x * DSR for x in t2]
# plt.plot(t_down, u_hat[0:len(t_down)], label="$\hat{u}(t)$ Reference")
plt.plot(t, u_hat, label="$\hat{u}(t)$ Reference")
plt.plot(t2, output, label="Calculated")
# plt.plot(t2, B, label="Calculated2")

plt.xlabel("$t / T$")
plt.legend()
plt.title("Estimated input signal")
plt.grid(which="both")
# plt.xlim(500,600)
plt.xlim((0, size/2))
plt.tight_layout()
plt.savefig("plot2.png")
plt.show()

"""