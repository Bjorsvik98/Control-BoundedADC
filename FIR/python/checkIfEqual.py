import matplotlib.pyplot as plt
import numpy as np
from parsInput import parsFunc
import collections
import cbadc
from saveEstimator import *



N, beta, rho, kappa, amplitude, OSR, offset, size, eta2, K1, K2, DSR, bits_used, fraction_bits, outputFormat = parsFunc()
N = int(N)
DSR = int(DSR)
precision = 0.00001

with open('../result.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
A = [int(x) for x in result]

# print(A)
# for i in range(len(A)):
#         A[i] = to_float(A[i], FixedPointBits)


with open('u_hat.txt') as file:
    result = file.readlines()
    result = [line.rstrip() for line in result]
u_hat = [int(x) for x in result]

# print(u_hat)
# for i in range(len(u_hat)):
#         u_hat[i] = to_fixed(u_hat[i], FixedPointBits)

correct = 0
fails = 0
# print(A)
# print((len(A))//DSR-K1)
# print(len(u_hat))
# print(type(A[0]))
# print(type(u_hat[0]))

for i in range(len(A)//DSR-K1-K2):
    # if (i > (K1+K2)//DSR): # Removes the K1+K2 first values to get correct result. The first K samples correct
        # print("i-((K1+K2)//DSR)", i-((K1+K2)//DSR), "(i-1)*DSR", (i)-((K1+K2)//DSR))
        # print("A[",i-((K1+K2)//DSR),"]", A[i-((K1+K2)//DSR)], "u_hat[",(i-1)*DSR,"]", u_hat[(i)-((K1+K2)//DSR)])
    # print("A[",i,"] = ", A[i], "u_hat[",((i)*DSR)+(K1+K2-1),"] = ", u_hat[((i)*DSR)+(K1+K2-1)])
    if(A[i] == u_hat[((i)*DSR)+(K1+K2-1)]): # u_hat is float with another precision
        correct += 1
    else:
        fails += 1
    
        # if (i > K1+K2+100 & i <K1+K2+200):
            # print("A = ", A[i-((K1+K2)//DSR)], "u = ", u_hat[(i-1)*DSR])


# for i in range(len(A)//DSR):
#     if (i > K1+K2): # Removes the K1+K2 first values to get correct result. The first K samples correct
        
#         if(abs(A[i-((K1+K2)//DSR)]-u_hat[(i-1)*DSR]) < precision): # u_hat is float with another precision
#             correct += 1
#         else:
#             fails += 1
#     if (i > K1+K2+100 & i <K1+K2+200):
#         print("A = ", A[i-((K1+K2)//DSR)], "u = ", u_hat[(i-1)*DSR])
    
print("Number of identical values =", correct, "\nNumber of different values =",fails, "\nTotal samples =", size)

