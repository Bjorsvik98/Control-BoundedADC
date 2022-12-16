from re import I
import matplotlib.pyplot as plt
import numpy as np
from parsInput import parsFunc
import collections
import cbadc
from saveEstimator import *



N, beta, rho, kappa, amplitude, OSR, offset, size, eta2, K1, K2, DSR, FixedPointBits, bits_used, fraction_bits, parallel, numCores = parsFunc()
N = int(N)
DSR = int(DSR)
precision = 0.00001
# bits_used = FixedPointBits
max_floating_point_value = 1 << (bits_used-fraction_bits)
fixed_point = cbadc.utilities.FixedPoint(bits_used, max_floating_point_value)


with open('../result.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
A = [int(x) for x in result]

with open('resultDecimal.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
B = [int(x) for x in result]
B = B[:K1-1]
B.insert(0, 0)


with open('u_hat.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
u_hat = [int(x) for x in result]

# print("u_hat = ", u_hat, "\n")
# for i in range(len(u_hat)):
#         u_hat[i] = to_fixed(u_hat[i], FixedPointBits)
# print("u_hat = ", u_hat, "\n")


correct = 0
fails = 0
for i in range(len(A)):
    if (i > K1+K2): # Removes the K1+K2 first values to get correct result. The first K samples correct
        if(A[i] == u_hat[((i)*DSR)+(K1+K2-1)]): # u_hat is float with another precision
            correct += 1
        else:
            fails += 1
        
# print("Number of identical values =", correct, "\nNumber of different values =",fails, "\nTotal samples =", size)

errorSlack = 10000
correct = 0
fails = 0
simCorrect = 0
simFails = 0
# print(A)
# print(B)
# print(len(A))
# print(len(u_hat))
for i in range((len(A))//DSR):
    # if (i > K1+K2) and (i < (size - (K1 + K2))): # Removes the K1+K2 first values to get correct result. The first K samples correct
        # print("A = ", A[i], "u_hat = ", u_hat[i])
    # print("A[",i,"] = ", A[i], "u_hat[",i,"] = ", u_hat[i])
    if(A[i] > (u_hat[i*DSR]-errorSlack) and  A[i] < (u_hat[i*DSR]+errorSlack)): # u_hat is float with another precision
        correct += 1
    else:
        fails += 1

for i in range(len(B)):
    # print("A[{}] = {} B[{}] = {}".format(i, A[i], i, B[i]))
    if(A[i] == (B[i])): 
        simCorrect += 1
    else:
        simFails += 1

print("\nResult from simulation")
print("Number of identical values = {}, and wrong values = {}\n\n".format(simCorrect, simFails))





# 
for i in range(len(u_hat)):
        u_hat[i] = fixed_point.fixed_to_float(u_hat[i])
for i in range(len(A)):
    A[i] = fixed_point.fixed_to_float(A[i])

sum = 0
# print("u_hat = ", u_hat, "\n")
# print(len(A))
for i in range(int(K1/2)):
    # print("A = ", A[i], "u_hat = ", u_hat[i], "diff = ", A[i]-u_hat[i])
    sum += abs(A[i] - u_hat[i])
    # print("Difference = ", A[i]-u_hat[i])

avg = sum / (len(u_hat))
print("Average difference = ", avg)

print("Result of local run:")
print("Number of close values =", correct, "\nNumber of totaly different values =",fails, "\nTotal samples =", size)


