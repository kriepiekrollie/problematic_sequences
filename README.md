# problematic_sequences
some code regarding a math problem

## Compilation

Compile the code by running `make` in the root directory.

## Running

`./bin/main -f 5 -l 22 -s -1 -p`

Will find search for a problematic sequence of length 22 (`-l 22`)
in the finite field with 5 elements (`-f 5`),
and stop after finding the first one (`-s`).
It will also only search through sequences that start at 1 (`-1`).

Then when it finds one it will print (`-p`).

Some other options include:

- `-c`, which will output the number of nodes searched at each length.

- `-m`, which will print values of m as discussed in class.

- `-b`, which will print a table related to m lol.

- `-t`, which will print running time.
