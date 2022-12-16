# convert from signed 2's complement hex to decimal 


def twos_complement(hex_string, bits):
    value = int(hex_string, 16)
    if value & (1 << (bits - 1)):
        value -= 1 << bits
    return value

# print(twos_complement('fff9c43c', 32))


# convert resultHex.txt to decimal

def convert_to_decimal(filename, writeFilename):
    f = open(filename, "r+")
    writeFile = open(writeFilename, "w+")

    lines = f.readlines()
    for line in lines:
        # print(twos_complement(line, 32))
        line = "{}\n".format(twos_complement(line, 32))
        writeFile.write(line)

def convert_to_decimal_some_lines(filename, writeFilename, startLine, endLine):
    f = open(filename, "r+")
    writeFile = open(writeFilename, "w+")

    lines = f.readlines()
    
    for line in lines[0:30000]:
        # print(line, lines.index(line))
        if startLine <= lines.index(line) <= endLine:
            # if line == "00000000":
            #     writeFile.write(line)
            # else:
            line = "{}\n".format(twos_complement(line, 32))
            writeFile.write(line)
            # print(twos_complement(line, 32), lines.index(line))
            
        # print(twos_complement(line, 32))
        # line = "{}\n".format(twos_complement(line, 32))
        # writeFile.write(line)

# convert_to_decimal('resultHex.txt', 'resultDecimal.txt')
convert_to_decimal_some_lines('resultHex.txt', 'resultDecimal.txt', 100, 5000)