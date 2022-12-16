from parsInput import parsFunc

N, beta, rho, kappa, amplitude, OSR, offset, size, eta2, K1, K2, DSR, FixedPointBits, bits_used, fraction_bits, parallel, numCores = parsFunc()


def make_assembly(coreNr, inputFile, outputFile):
    f = open(inputFile, "r+")
    writeFile = open(outputFile, "w+")
    lines = f.readlines()
    
    stackAdr = ['a', 'f', 'e', 'd', 'c', 'b', 'a', '9', '8', '7', 'c', 'a', '8', '6', '4', '2'] 

    newFunctionInput = "00{}00513\n".format(coreNr)
    
    newStackPointer = "0000{}137\n".format(stackAdr[coreNr])
    endLine = 20
    for x in range(len(lines)):
        if x < endLine:
            # print(type("00100513"))
            if lines[x] == "00100513\n":
                writeFile.write(newFunctionInput)
                # print("found {} and changed it to {}".format(lines[x].replace("\n", ""),  newFunctionInput.replace("\n", "")))
            elif lines[x] == "0000f137\n":
                writeFile.write(newStackPointer)
                # print("found {} and changed it to {}".format(lines[x].replace("\n", ""),  newStackPointer.replace("\n", "")))
            else:
                writeFile.write(lines[x])


# numCores = 3
for x in range(numCores):
    make_assembly(x+1, '../parallel32.hex', '../assemblyInit{}.hex'.format(x+1))
        