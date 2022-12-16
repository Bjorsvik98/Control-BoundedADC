from multiprocessing.dummy import Array
# import matplotlib.pyplot as plt
# import cbadc
import numpy as np

def saveEstimatorMatrices(Array, path):
    # Array = digital_estimator.WT
    row, col = Array.shape
    file = open(path, "w+")
    line = "{} {}\n".format(row, col)
    file.write(line)
    np.savetxt(file, Array, delimiter=' ')
    file.close()

def saveEstimatorMatricesFloat(Array, path, fixed_point):
    for i in range(len(Array)):
        for j in range(len(Array[i])):
            # if Array[i][j] > 1:
            #     Array[i][j] = 1
            #     print("An element in the matrix is larger than 1")
            Array[i][j] = fixed_point.float_to_fixed(Array[i][j])
    # digital_estimator.Af[i] = fixed_point.float_to_fixed(digital_estimator.Af[i])
    # print(Array)
    # Array = digital_estimator.WT
    row, col = Array.shape
    file = open(path, "w+")
    line = "{} {}\n".format(row, col)
    file.write(line)
    np.savetxt(file, Array, delimiter=' ', fmt='%u')
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
            line = "{"+line+",\n"
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
    floatToFixed(matrix, fixed_point)
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
    line = "int32_t {}[{}_Height][{}_Width] = {{\n".format(name, name, name)
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
    # OutArray = np.zeros_like(Array)
    for i in range(len(Array)):
        for j in range(len(Array[i])):
            # if Array[i][j] > 1:
            #     Array[i][j] = 1
            # print("An element in the matrix is larger than 1")
            Array[i][j] = fixed_point.float_to_fixed(Array[i][j])
            # print("Element converted from {} to {}".format(Array[i][j], OutArray[i][j]))
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
    
def saveComplexMatrixCoefficientsDownsampled(path, matrix, name, fixed_point, DSR):

    # print(matrix)

    for l in range(len(matrix)):
        temp = matrix[l]
        # print(temp)
        for i in range(temp.shape[0]):
            for j in range(temp.shape[1]):
                # print(temp[i][j])
                temp.real[i][j] = fixed_point.float_to_fixed(temp.real[i][j])
                temp.imag[i][j] = fixed_point.float_to_fixed(temp.imag[i][j])
        matrix[l] = temp


    file = open(path, "a")
    size = matrix[0].shape[0]
    line = "\n"
    file.write(line)
    saveConstCoefficients(path, size, "{}_Height".format(name))
    saveConstCoefficients(path , matrix[0].shape[1], "{}_Width".format(name))

    # Real part
    line = "const int32_t real_{}[DSR][{}_Height][{}_Width] = {{\n{{ {{".format(name, name, name)
    file.write(line)
    for i in range(DSR):
        np.savetxt(file, matrix[i].real, delimiter=', ',fmt="%d", newline="},\n{")
        file.seek(0, 2)
        size = file.tell()
        file.truncate(size-2)
        line = "},\n{ {"
        file.write(line)
        # np.savetxt(file, matrix.real, delimiter=', ',fmt="%d", newline="},\n{")

    #Remove last line of file
    file.seek(0, 2)
    size = file.tell()
    file.truncate(size-3)
    line = "};\n\n"
    file.write(line)


     # imaginary part
    line = "const int32_t imag_{}[DSR][{}_Height][{}_Width] = {{\n{{ {{".format(name, name, name)
    file.write(line)
    for i in range(DSR):
        np.savetxt(file, matrix[i].imag, delimiter=', ',fmt="%d", newline="},\n{")
        file.seek(0, 2)
        size = file.tell()
        file.truncate(size-2)
        line = "},\n{ {"
        file.write(line)

    #Remove last line of file
    file.seek(0, 2)
    size = file.tell()
    file.truncate(size-3)
    line = "};\n\n"
    file.write(line)


    file.close()