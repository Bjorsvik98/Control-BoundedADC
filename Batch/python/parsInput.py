from argparse import ArgumentParser, ArgumentDefaultsHelpFormatter

def parsFunc():
    parser = ArgumentParser(formatter_class=ArgumentDefaultsHelpFormatter)
    parser.add_argument("-N", "--Nvec", default=6, help="the size of N")
    parser.add_argument("-b", "--beta", default=6250.0, help="the size of beta")
    parser.add_argument("-r", "--rho", default=-1e-2, help="the size of rho")
    parser.add_argument("-k", "--kappa", default=-1.0, help="the size of kappa")
    parser.add_argument("-a", "--amplitude", default=1, help="the amplitude of the input signal") ## anaog signal
    parser.add_argument("--OSR", default=1<<9, help="Choose the oversampling ratio (OSR)") ## anaog signal
    parser.add_argument("--offset", default=0, help="Choose the offset of the input sinusodial signal") ## anaog signal
    parser.add_argument("-s", "--sizeBits", default=16, help="Choose number of bits in the size of the signal")
    parser.add_argument("--eta2", default=1e6)
    parser.add_argument("-K1", "--K1", default=20)
    parser.add_argument("-K2", "--K2", default=20)
    parser.add_argument("--DSR", default=1)
    parser.add_argument("--FPB", "--FixedPointBits", default=30, help="Number og fixed point bits to use")
    parser.add_argument("--bits", "--bitsUsed", default=32, help="Number of float bits to use")
    parser.add_argument("--fraction", "--fractionBits", default=16, help="Number of fraction bits to use")
    parser.add_argument("-p", "--parallel", default=0, help="use parallel or not 0 = normal batch and 1 = parallel")
    parser.add_argument("-c", "--numCores", default=1, help="Number of cores to use")
    

    args = vars(parser.parse_args())
    # Set up parameters
    N = args["Nvec"]
    beta = args["beta"]
    rho = args["rho"]
    kappa = args["kappa"]
    amplitude = args["amplitude"]
    OSR = args["OSR"]
    offset = args["offset"]
    sizeBits = args["sizeBits"]
    # size = 1 << int(sizeBits)
    size = int(sizeBits)
    eta2 = args["eta2"]
    K1 = int(args["K1"])
    K2 = int(args["K2"])
    DSR = int(args["DSR"])
    FixedPointBits = int(args["FPB"])
    bits_used = int(args["bits"])
    fraction_bits = int(args["fraction"])
    parallel = int(args["parallel"])
    numCores = int(args["numCores"])

    return N, beta, rho, kappa, amplitude, OSR, offset, size, eta2, K1, K2, DSR, FixedPointBits, bits_used, fraction_bits, parallel, numCores


 


