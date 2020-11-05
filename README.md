# Assignment 4 - Jack Vento
## The Program
Sequence is a program meant to highlight Bit Vectors and efficiency of sieves in calculating primes. It then takes those primes and either prints out statistics about them (whether they are Mersenne, Fibonacci, and/or Lucas primes) or prints all palindromic primes in a variety of bases (bases 2, 9, 10, and 32 are on display presently but any base is possible).

These are three possible arguments:
* -n x: Sets the range to [2, x] in the sieve's search for primes (default: x = 1000 if not specified).
* -s: Checks if each prime in the range [2, x] is Mersenne, Fibonacci, or Lucas.
* -p: Prints all palindromic primes in the range [2, x]<sub>10</sub> for bases 2, 9, 10, and 32.

Run the program using `./sequence <arguments>` after compiling. No arguments are mutually exclusive.

## Makefile
* `make` and `make all` will compile the program to an executable named "*sequence*".
* `make clean` removes all compiler-generated files.
* `infer` is also an optional featured command, which the program passes.

