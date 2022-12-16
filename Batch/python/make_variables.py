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

N, beta, rho, kappa, amplitude, OSR, offset, size, eta2, K1, K2, DSR, FixedPointBits, bits_used, fraction_bits, parallel, numCores = parsFunc()
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


###############################################################################
# read and write controll signal
byte_stream = cbadc.utilities.read_byte_stream_from_file("sinusoidal_simulation.dat", M)
control_signal_sequences = cbadc.utilities.byte_stream_2_control_signal(byte_stream, M)

file = open("control_signal_sequences.txt", "w")
line = "{} {}\n".format(size, M)
file.write(line)
# print("size: ", size)
for x in range(size-1):
    line = list(next(control_signal_sequences))
    # if size > 1000:
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
    analog_system, digital_control, eta2, K1, downsample=DSR
)
digital_estimator(control_signal_sequences)
# print("Bb =",digital_estimator.Bb)

# saveEstimatorMatricesFloat(digital_estimator.Af, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/Af.txt", fixed_point)
# saveEstimatorMatricesFloat(digital_estimator.Ab, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/Ab.txt", fixed_point)
# saveEstimatorMatricesFloat(digital_estimator.Bf, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/Bf.txt", fixed_point)
# saveEstimatorMatricesFloat(digital_estimator.Bb, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/Bb.txt", fixed_point)
# saveEstimatorMatricesFloat(digital_estimator.WT, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/WT.txt", fixed_point)



# saveEstimatorConstants(size, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/size.txt")
# saveEstimatorConstants(digital_estimator.eta2, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/eta2.txt")
# saveEstimatorConstants(digital_estimator.K1, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/K1.txt")
# saveEstimatorConstants(digital_estimator.K2, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/K2.txt")
# saveEstimatorConstants(digital_estimator.Ts, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/Ts.txt")
# saveEstimatorConstants(digital_estimator.number_of_iterations, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/number_of_iterations.txt")
# saveEstimatorConstants(DSR, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/DSR.txt")
# saveEstimatorConstants(N, "/home/sp22/CBADC_RISC-V/Batch/BatchFiles/N.txt")




# formatEstimatorMatrix("/home/sp22/CBADC_RISC-V/Batch/BatchFiles/control_signal_sequences.txt")
# print("saving coefficients")
# samples = size - digital_estimator.K1 - digital_estimator.K2
coefficientPath = "/home/sp22/CBADC_RISC-V/Batch/include/coefficients.h"
initCoefficients(coefficientPath)
saveConstCoefficients(coefficientPath, DSR, "DSR")
# saveConstCoefficients(coefficientPath, N, "N")
saveConstCoefficients(coefficientPath, size, "size")
saveConstCoefficients(coefficientPath, digital_estimator.K1, "K1")
saveConstCoefficients(coefficientPath, digital_estimator.K2, "K2")
saveConstCoefficients(coefficientPath, digital_estimator.K1 + digital_estimator.K2, "K")
# saveConstCoefficients(coefficientPath, size - digital_estimator.K1 - digital_estimator.K2, "samples")
# print("forward_b =",digital_estimator.forward_b)
# print("forward_a_down: ",digital_estimator.forward_a_down)
# print("forward_a:      ",digital_estimator.forward_a)
# print("forward_w_down: ",digital_estimator.forward_w_down)
# print("forward_w:      ",digital_estimator.forward_w)


if parallel == 0:
    saveMatrixCoefficients(coefficientPath, digital_estimator.Af, "Af", fixed_point)
    saveMatrixCoefficients(coefficientPath, digital_estimator.Ab, "Ab", fixed_point)
    saveMatrixCoefficients(coefficientPath, digital_estimator.Bf, "Bf", fixed_point)
    saveMatrixCoefficients(coefficientPath, digital_estimator.Bb, "Bb", fixed_point)
    saveMatrixCoefficients(coefficientPath, digital_estimator.WT, "WT", fixed_point)


else:
    # print("backward_b_list", digital_estimator.backward_b_list)
    # print("backward_b", digital_estimator.backward_b)
    if DSR == 1:
        print("DSR = 1")
        saveComplexMatrixCoefficients(coefficientPath, digital_estimator.forward_b, "forward_b", fixed_point)
        saveComplexMatrixCoefficients(coefficientPath, digital_estimator.backward_b, "backward_b", fixed_point)
        # saveComplexMatrixCoefficientsDownsampled(coefficientPath, digital_estimator.backward_b_list, "backward_b_list", fixed_point, DSR)
        # saveComplexMatrixCoefficientsDownsampled(coefficientPath, digital_estimator.forward_b_list, "forward_b_list", fixed_point, DSR)

    elif DSR > 1:
        print("Downsampling > 1 not supported for parallel estimator yet")
        # print("DSR > 1 and ",digital_estimator.Bf_list)
        saveComplexMatrixCoefficientsDownsampled(coefficientPath, digital_estimator.backward_b_list, "backward_b_list", fixed_point, DSR)
        saveComplexMatrixCoefficientsDownsampled(coefficientPath, digital_estimator.forward_b_list, "forward_b_list", fixed_point, DSR)
        # saveComplexMatrixCoefficientsDownsampled(coefficientPath, digital_estimator.forward_b, "forward_b", fixed_point, DSR)
        # saveComplexMatrixCoefficientsDownsampled(coefficientPath, digital_estimator.backward_b, "backward_b", fixed_point, DSR)
    else:
        print("DSR must be greater than 0")

    saveComplexMatrixCoefficients(coefficientPath, digital_estimator.forward_a_down, "forward_a", fixed_point)
    saveComplexMatrixCoefficients(coefficientPath, digital_estimator.backward_a_down, "backward_a", fixed_point)
    saveComplexMatrixCoefficients(coefficientPath, digital_estimator.forward_w_down, "forward_w", fixed_point)
    saveComplexMatrixCoefficients(coefficientPath, digital_estimator.backward_w_down, "backward_w", fixed_point)

# print(digital_estimator.forward_a)

saveControllSequence(coefficientPath, "control_signal_sequences.txt", "S") #must be last
    
appendDefine("../include/filter.h", "N", N)
appendDefine("../include/filter.h", "FRACTION_BITS", fraction_bits)

# print(fixed_point)

# print(digital_estimator.Bb)
