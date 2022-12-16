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


N, beta, rho, kappa, amplitude, OSR, offset, size, eta2, K1, K2, DSR, bits_used, fraction_bits, outputFormat = parsFunc()
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
max_floating_point_value = 1 << (bits_used-fraction_bits)


analog_signal = cbadc.analog_signal.Sinusoidal(amplitude, frequency, phase, offset)
analog_system = cbadc.analog_system.AnalogSystem(A, B, CT, Gamma, Gamma_tildeT)
digital_control = cbadc.digital_control.DigitalControl(cbadc.analog_signal.Clock(T), M)
fixed_point = cbadc.utilities.FixedPoint(bits_used, max_floating_point_value)
###############################################################################
# read and write controll signal
byte_stream = cbadc.utilities.read_byte_stream_from_file("sinusoidal_simulation.dat", M)
control_signal_sequences = cbadc.utilities.byte_stream_2_control_signal(byte_stream, M)

file = open("/home/sp22/CBADC_RISC-V/FIR/FIRFiles/control_signal_sequences.txt", "w+")
line = "{} {}\n".format(size, M)
file.write(line)
for x in range(size-1):
    line = list(next(control_signal_sequences))
    if outputFormat == 1:
        outLine = ' '.join(map(str, line)) + '\n'
    if outputFormat == 2:
        outLine = ', '.join(map(str, line)) + '\n'
    file.write(outLine)

file.close()
#################

###############################################################################



digital_estimator = cbadc.digital_estimator.FIRFilter(
    analog_system, digital_control, eta2, K1, K2, fixed_point=fixed_point
)
digital_estimator(control_signal_sequences)


# print(digital_estimator.h[0][0][0])


# saveEstimatorMatrices(digital_estimator.h[0], "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/h.txt", outputFormat)



# saveEstimatorConstants(size, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/number_of_cyckles.txt")
# saveEstimatorConstants(digital_estimator.eta2, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/eta2.txt")
# saveEstimatorConstants(digital_estimator.K1, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/K1.txt")
# saveEstimatorConstants(digital_estimator.K2, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/K2.txt")
# saveEstimatorConstants(digital_estimator.Ts, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/Ts.txt")
# saveEstimatorConstants(digital_estimator.number_of_iterations, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/number_of_iterations.txt")
# saveEstimatorConstants(DSR, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/DSR.txt")



# saveEstimatorMatricesInt(h, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/h2.txt")
# if outputFormat == 2:
#     formatEstimatorMatrix("/home/sp22/CBADC_RISC-V/FIR/FIRFiles/h.txt")
#     formatEstimatorMatrix("/home/sp22/CBADC_RISC-V/FIR/FIRFiles/control_signal_sequences.txt")

coefficientPath = "../include/coefficients.h"
initCoefficients(coefficientPath)
saveConstCoefficients(coefficientPath, DSR, "DSR")
saveConstCoefficients(coefficientPath, digital_estimator.K1, "K1")
saveConstCoefficients(coefficientPath, digital_estimator.K2, "K2")
saveConstCoefficients(coefficientPath, digital_estimator.K1 + digital_estimator.K2, "K")
saveConstCoefficients(coefficientPath, size, "samples")


saveMatrixCoefficients(coefficientPath, digital_estimator.h[0], "H", fixed_point)

saveControllSequence(coefficientPath, "/home/sp22/CBADC_RISC-V/FIR/FIRFiles/control_signal_sequences.txt", "S") #must be last



# print("max =", fixed_point.max, "min =",fixed_point.max_int, "max_int =", fixed_point.max_int)
print(fixed_point)