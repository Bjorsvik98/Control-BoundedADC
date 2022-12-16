# N, beta, rho, kappa, amplitude, OSR, offset,  eta2, K1, K2
N = 5
sizeBits = 10 # was 7
K1 = 120 # was 20
K2 = $(K1)
DSR = 1
FPB = 32 # 16 #FixedPointBits
fractionBits = 31 # 15 #FractionalBits
o = 2

FLAGS = -s $(sizeBits) -K1 $(K1) -K2 $(K2) -N $(N) --DSR $(DSR) --bits $(FPB) --fraction $(fractionBits) -o $(o)

dat:
	python3 makeDat.py $(FLAGS)

variable:
	python3 make_variables.py $(FLAGS)

c:
	make -C ../ clean
	make -C ../ run USE_MYSTDLIB=0

c_hex:
	make -C ../ clean
	make -C ../ fir.hex

plot:
	python3 makePlot.py $(FLAGS)

check:
	python3 checkIfEqual.py $(FLAGS)

all: dat variable c plot #check c_hex

FIR:
	python3 FIRFiltering.py $(FLAGS)

convertHex: 
	python3 convertHex.py

verify: convertHex plot check
