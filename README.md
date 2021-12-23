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

