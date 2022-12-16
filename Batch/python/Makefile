# N, beta, rho, kappa, amplitude, OSR, offset,  eta2, K1, K2
N = 3
sizeBits = 2048 # 512 is default
K1 =  2000 # 160 is default

K2 = $(K1)
DSR = 1
FPB = 32	# 32 FixedPointBits
fractionBits = 21 # 21 is the default for the 32-bit fixed point
parallel = 1
numCores = $(N)

amplitude = 1


FLAGS = -s $(sizeBits) -K1 $(K1) -K2 $(K2) -N $(N) --DSR $(DSR) --bits $(FPB) --fraction $(fractionBits) --parallel $(parallel) --numCores $(numCores) 

dat:
	python3 makeDat.py $(FLAGS)

variable:
	python3 make_variables.py $(FLAGS)

ifeq ($(parallel), 1)
c:
	make -C ../ clean
	make -C ../ parallel USE_MYSTDLIB=0
else
c:
	make -C ../ clean
	make -C ../ batch USE_MYSTDLIB=0

endif

c_hex:
	make -C ../ clean
	make -C ../ parallel.hex


plot: 
	python3 makePlot.py $(FLAGS)

check: 
	python3 checkIfEqual.py $(FLAGS)

all: dat variable c plot #check c_hex

FIR:
	python3 FIRFiltering.py $(FLAGS)

getFunction:
	cp ../../python-program/parsInput.py ../../python-program/saveEstimator.py .

clean:
	rm -f *.png *.svg script.txt

assemblyCore:
	python3 assemblyCore.py $(FLAGS)

convertHex: 
	python3 convertHex.py

verify: convertHex plot check

