# Sample code for RNN (Recurrent Neural Network)
This is a sample code to solve N Queen Puzzle using RNN. You can read [Wikipedia - Eight Queens Puzzle](https://en.wikipedia.org/wiki/Eight_queens_puzzle) to know what N Queen Puzzle is. Here, I also included the calculation result not for 8 queens puzzle, but 100 queens puzzle.
In order to compile GUI edition, you need to install

## Prerequisite

* Install gcc
* Install X11

## How To Use

Step.1) Get source code.

 $ git clone https://github.com/syatsuzuka/sample_nqueen.git

Step.2) Compile source code to create executable.

 $ cd sample_nqueen/src

 $ gcc cui_main.c -o cui_main

 $ gcc gui_main.c -lX11 -o gui_main

Step.3) Run the executable file.

 $ cd src

 $ ./cui_main <Matrix Size> [Seed Number for rand] > <output file>

 $ ./gui_main

