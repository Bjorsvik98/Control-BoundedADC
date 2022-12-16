from multiprocessing.dummy import Array
# import matplotlib.pyplot as plt
# import cbadc
import numpy as np

def saveEstimatorMatrices(Array, path, outputFormat):
    # Array = digital_estimator.WT
    row, col = Array.shape
    file = open(path, "w+")
    line = "{} {}\n".format(row, col)
    file.write(line)
    if outputFormat == 1:
        np.savetxt(file, Array, delimiter=' ', fmt='%d')
    if outputFormat == 2:
        np.savetxt(file, Array, delimiter=', ',fmt="%d")
    file.close()

def saveEstimatorConstants(Value, path):
    file = open(path, "w+")
    line = "{}\n".format(Value)
    file.write(line)
    file.close()

def saveEstimatorMatricesInt(Array, path):
    # Array = digital_estimator.WT
    row, col = Array.shape
    file = open(path, "w+")
    line = "{} {}\n".format(row, col)
    file.write(line)
    np.savetxt(file, Array, delimiter=' ', fmt='%u')
    file.close()


"""
f is the input floating point number 
e is the number of fractional bits in the Q format. 
    Example in Q1.15 format e = 15
"""
def to_fixed(f,e):
    # print("input = ",f)
    a = f* (2**e)
    b = int(round(a))
    if a < 0:
        # next three lines turns b into it's 2's complement.
        b = abs(b)
        b = ~b
        b = b + 1
    return b

"""
x is the input fixed number which is of integer datatype
e is the number of fractional bits for example in Q1.15 e = 15
"""
def to_float(x,e):
    c = abs(x)
    sign = 1 
    if x < 0:
        # convert back from two's complement
        c = x - 1 
        c = ~c
        sign = -1
    f = (1.0 * c) / (2 ** e)
    f = f * sign
    return f

def formatEstimatorMatrix(path):
    file = open(path, "r")
    lines = file.readlines()
    file.close()
    file = open(path, "w+")
    for index, line in enumerate(lines):
        if index == 0:
            file.write(line)
        if index == 1:
            line = line.replace("\n", "}")
            line = "{{"+line+",\n"
            file.write(line)
        if index > 1 and index < len(lines)-1:
            line = line.replace("\n", "},\n")
            line = "{"+line
            file.write(line)
        if index == len(lines)-1:
            line = line.replace("\n", "}};")
            line = "{"+line
            file.write(line)
        
    file.close()

def initCoefficients(path):
    file = open(path, "w")
    file.write("#ifndef COEFFICIENTS_H\n")
    file.write("#define COEFFICIENTS_H\n")
    file.write("#ifdef USE_MYSTDLIB\n  #include \"stdlib.h\"\n #else\n  #include <stdlib.h>\n #endif\n\n")
    # file.write("// #include \"stdlib.h\"\n#include <stdint.h>\n#include <stdlib.h>\n\n")
    file.close()

def saveConstCoefficients(path, value, name):
    file = open(path, "a")
    line = "#define {} {}\n".format(name, value)
    file.write(line)
    file.close()

def saveMatrixCoefficients(path, matrix, name, fixed_point):
    # print(type(matrix[0][0]))
    # if type(matrix[0][0]) == np.float64:
        # print("Ipnut matrix is float")
    # floatToFixed(matrix, fixed_point)
    file = open(path, "a")
    hRow, hCol = matrix.shape
    line = "\n"
    file.write(line)
    saveConstCoefficients(path , hRow, "{}_Height".format(name))
    saveConstCoefficients(path , hCol, "{}_Width".format(name))


    line = "const int32_t {}[{}_Height][{}_Width] = {{\n{{".format(name, name, name)
    file.write(line)
    np.savetxt(file, matrix, delimiter=', ',fmt="%d", newline="},\n{")

    #Remove last line of file
    file.seek(0, 2)
    size = file.tell()
    file.truncate(size-2)

    line = "};\n\n"
    file.write(line)


    file.close()

def saveComplexMatrixCoefficients(path, matrix, name, fixed_point):

    if matrix.ndim == 1:
        floatToFixed2(matrix.real, fixed_point)
        floatToFixed2(matrix.imag, fixed_point)
    elif matrix.ndim == 2:
        floatToFixed(matrix.real, fixed_point)
        floatToFixed(matrix.imag, fixed_point)
    file = open(path, "a")

    size = matrix.shape[0]
    line = "\n"
    file.write(line)
    saveConstCoefficients(path, size, "{}_Height".format(name))
    if matrix.ndim == 2:
        saveConstCoefficients(path , matrix.shape[1], "{}_Width".format(name))
        # Real part
        line = "const int32_t real_{}[{}_Height][{}_Width] = {{\n{{".format(name, name, name)
        file.write(line)
        np.savetxt(file, matrix.real, delimiter=', ',fmt="%d", newline="},\n{")

        #Remove last line of file
        file.seek(0, 2)
        size = file.tell()
        file.truncate(size-2)
        line = "};\n\n"
        file.write(line)

        # Imaginary part
        line = "const int32_t imag_{}[{}_Height][{}_Width] = {{\n{{".format(name, name, name)
        file.write(line)
        np.savetxt(file, matrix.imag, delimiter=', ',fmt="%d", newline="},\n{")

    elif matrix.ndim == 1:
        saveConstCoefficients(path , 1, "{}_Width".format(name))
        # Real part
        line = "const int32_t real_{}[{}_Height] = {{\n".format(name, name, name)
        file.write(line)
        np.savetxt(file, matrix.real, delimiter=', ',fmt="%d", newline=", " )

        #Remove last line of file
        file.seek(0, 2)
        size = file.tell()
        file.truncate(size-2)
        line = "};\n\n"
        file.write(line)

        # Imaginary part
        line = "const int32_t imag_{}[{}_Height] = {{\n".format(name, name, name)
        file.write(line)
        np.savetxt(file, matrix.imag, delimiter=', ',fmt="%d", newline=", ")

    #Remove last line of file
    file.seek(0, 2)
    size = file.tell()
    file.truncate(size-2)

    line = "};\n\n"
    file.write(line)



    file.close()

def saveControllSequence(path, controlSequencePath, name):
    sequenceFile = open(controlSequencePath, "r")
    sequence = sequenceFile.readlines()
    sequenceFile.close()
    heighth = sequence[0].split(" ")[0]
    width = sequence[0].split(" ")[1]

    file = open(path, "a")
    
    saveConstCoefficients(path, heighth, "{}_Height".format(name))
    saveConstCoefficients(path, width, "{}_Width".format(name))
    line = "const int32_t {}[{}_Height][{}_Width] = {{\n".format(name, name, name)
    file.write(line)
    for index, line in enumerate(sequence):
        # line = line.replace("0", "-1")
        if index > 0 and index < len(sequence)-1:
            line = line.replace("\n", "},\n")
            line = "{"+line
            file.write(line)  
        if index == len(sequence)-1:
            line = line.replace("\n", "}};")
            line = "{"+line
            file.write(line)
    file.write("\n\n#endif")
    file.close()    

def floatToFixed(Array, fixed_point):
    for i in range(len(Array)):
        for j in range(len(Array[i])):
            # if Array[i][j] > 1:
            #     Array[i][j] = 1
            #     print("An element in the matrix is larger than 1")
            Array[i][j] = fixed_point.float_to_fixed(Array[i][j])
    return Array

def floatToFixed2(Array, fixed_point):
    for i in range(len(Array)):
        Array[i] = fixed_point.float_to_fixed(Array[i])
    return Array

def appendDefine(path, name, value):
    f = open(path,'r')
    temp = f.read()
    f.close()

    f = open(path, 'w')
    line = "#ifndef {} \n#define {} {}\n#endif\n".format(name, name, value)
    # testLine = "#define {} {}\n".format(name, value)
    # print(temp.find(testLine))
    # if temp.find(line) == -1:
    #     f.write(line)
    # else:
    #     print("line found")
    f.write(line)

    f.write(temp)
    f.close()