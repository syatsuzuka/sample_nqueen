/**************************************************************
 * FILE: common.c
 * DESC: common object to solve N Queen Problem
 *
 * AUTHOR: S.Yatsuzuka
 *
 * ***********************************************************/

//======= Preprocessor =======

#include "common.h"


/**************************************************************
 * FUNC: init
 * DESC: initialize the matrix using rand func
 *   
 * ***********************************************************/

void init(int max){

	
	/*======= Variables =======*/

	int i, j, x;


	/*======= Initialization =======*/

	for ( i = 0; i < max; i++){
		for ( j = 0; j < max; j++){
			x = (int)((double)20 * urand());
			U[i][j] = x - 10;

			if ( U[i][j] < 0 ) V[i][j] = 1;
			else V[i][j] = 0;
		}
	}
}


/**************************************************************
 * FUNC: disp
 * DESC: display the value in matrix data
 *   
 * ***********************************************************/

void disp(void){


	//======= Variables =======

	int i, j;


	//======= Display Input Vector =======
	
	printf("<Input Vector>\n");
	
    for ( i = 0; i < max; i++){
        for ( j = 0; j < max; j++){
            printf("%2d\t", U[i][j]);
        }
        printf("\n");
    }

	printf("\n\n");


	//======= Display Volage Vector =======
	
	printf("<Voltage Vector>\n");

    for ( i = 0; i < max; i++){
        for ( j = 0; j < max; j++){
            printf("%d ", V[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}


/**************************************************************
 * FUNC: urand
 * DESC: return the uniformed random values
 *   
 * ***********************************************************/

double urand(void){
	
	//======= Variables =======

	int i;


	//======= Return uniformed random value =======
	
	return ((double)rand()+1.0)/((double)RAND_MAX+2.0);
}


/**************************************************************
 * FUNC: dU
 * DESC: adjust input vector
 *   
 * ***********************************************************/

int dU(int i, int j){


	//======= Variables =======

	int k, du, h, C;


	//======= Reset values =======
	
	C = 1;
	sum_column = 0;
	sum_row = 0;


	//======= Check the total num in column and row =======

	for ( k = 0; k < max; k++){
		sum_row = sum_row + V[i][k];
		sum_column = sum_column + V[k][j];
	}


	//======= Check the total num in diagonal.1 =======

	sum_diag1 = 0;
	k = 1;

	while((j+k) < max && (i-k) >= 0){

		sum_diag1 = sum_diag1 + V[i-k][j+k];
		k++;
	}

	k = 1;

	while((j-k) >= 0 && (i+k) < max){
		sum_diag1 = sum_diag1 + V[i+k][j-k];
		k++;
	}


	//======= Check the total num in diagonal.2 =======

	sum_diag2 = 0;
	k = 1;

	while((j+k) < max && (i+k) < max){
		sum_diag2 = sum_diag2 + V[i+k][j+k];
		k++;
	}

	k = 1;

	while((j-k) >= 0 && (i-k) >= 0){
		sum_diag2 = sum_diag2 + V[i-k][j-k];
		k++;
	}


	//======= Calc the weight for Hill-Crimbing =======

	h = 0;
	if (sum_column == 0) h = 1;
	if (sum_row == 0) h++;


	//======= Define dUij =======

	du = -A * (sum_row + sum_column - 2) 
		-B * (sum_diag1 + sum_diag2) + C * h;


	//======= Logging =======

	printf ("dU[%d][%d]	= %d, ", i, j, du);


	return (du);

}

