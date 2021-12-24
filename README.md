# hpc_permutation_generator
Optimizing serial code of a permutation generator using openmp.

The serial program generates random string input from a to z and checks an internal dictionary to out put all possible words that can be created from the set of characters. The program is desinged to capture time stamps to determine the speed up and efficiency of using OpenMp with various amount of threads.


The program is modified to do mulitple bench mark testing through command line functions. -n [integer] determines the amount of characters to be tested and -s [integer] determines the quantity of tests
to run for benchmarking. At the end of the tests a summary of average times, results and total threads used are displayed to the user.

Instructions for use on Linux Terminal:

clone repository

go to the repository hpc_permutation_generator/permutation_generator/

use the linux command:
1. make clean
2. make
3. ./performance_gen3

This will run basic tests in serial

To change amount of threads being used use Linux Command:
export OMP_NUM_THREADS=2

For benchmark tests try with 2,4,8,16,32 and 64 threads.

Use command line arguments to change amount of characters being used and the quantity of tests being conducted.

./performance_gen3 -n 15 -s 50

These command arguments specify a random set of 15 characters while conducting 50 tests.

The benchmarking below was taken on Stampede2 using Knights Landing compute nodes.

Glossary
TWF = Total Words Found	 
FW = Found Words in (ms)	 
CW = Concatenate Words in (ms)

OpenMP Implementation
# of Threads	AVG. TWF	AVG. FW (ms)	SpeedUp	Eff	AVG. CW (ms)	SpeedUp	Eff
1	245	101.608871	1	100%	0.06063	1	100%
2	249	80.522662	1.2618668	63%	0.077974	0.777567	39%
4	208	52.225614	1.9455754	49%	0.06952	0.872123	22%
8	354	35.326596	2.8762712	36%	0.10367	0.584837	7%
16	224	21.728243	4.6763501	29%	0.0677	0.895569	6%
32	221	13.680162	7.4274611	23%	0.068427	0.886054	3%
64	301	8.495933	11.959707	19%	0.101613	0.596676	1%

OpenMP Implementation with schedule(dynamic) for load balancing
# of Threads	AVG. TR	AVG. FW (ms)	SpeedUp	Eff	AVG. CW (ms)	SpeedUp	Eff
1	265	109.777989	1	100%	0.074374	1	100%
2	219	88.63366	1.2385587	62%	0.07111	1.045901	52%
4	268	51.601954	2.1273998	53%	0.082141	0.905443	23%
8	336	29.983378	3.6612949	46%	0.114937	0.647085	8%
16	321	20.091481	5.4639073	34%	0.093387	0.796406	5%
32	274	16.175658	6.7866166	21%	0.096865	0.767811	2%
64	253	12.041209	9.1168577	14%	0.119098	0.624477	1%


