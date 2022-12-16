Code for batch filter with a normal implementation and one for parallelization

<br />

# Get hex file

## Batch
To generate new hex-file for batch write:
```bash
make batch.hex
```
And batch32.hex will contain the newly compiled hex file in a 32 bit format. 

## Parallel
To generate new hex-file for the parallel batch write:
```bash
make parallel.hex
```
And parallel32.hex will contain the newly compiled hex file in a 32 bit format. 

<br />
<br />

# Run code local 

To run code local and get plot of the code compared to the correct result write:

```bash
cd python
make all parallel=0
```

parallel=0 for batch filter 
parallel=1 for the parallel implementation
 
# Change variables 

To change variables like N, Size of batch and fractionBits do:

```bash
cd python
make variables parallel=x N=x sizeBits=x
```

To find all posibilities open makefile in the python folder and check the first lines

# Simulate on leda
go to python folder, type make all. 
Copy parallel32.hex to memimage.hex on leda. 
Run Simulation
Copy out.hex to resultHex.txt
type make verify