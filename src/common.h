/**************************************************************
 * FILE: common.h
 * DESC: common object to solve N Queen Problem
 *
 * AUTHOR: S.Yatsuzuka
 *
 * ***********************************************************/


//======= Preprocessor =======

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A 1
#define B 1

//======= Global Variables =======

int ng_pt;          // diagnosis points
int max;            // max size for matrix
int C;              // Coeff for Hill-Criming term
int sum_column;     // total num in one column
int sum_row;        // total num in one row
int sum_diag1;      // total num in diagonal
int sum_diag2;      // total num in diagonal

int V[100][100];    // voltage vector
int U[100][100];    // input vector


//======= Proto Type =======

void init (int max);
void disp (void);
double urand(void);
int dU(int i, int j);
