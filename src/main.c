/**************************************************************
 * FILE: main.c
 * DESC: solve N Queen Problem
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


//======= Proto Type =======

void init (int max);
void disp (void);
double urand(void);
int dU(int i, int j);


//======= Global Variables =======

int ng_pt;			// diagnosis points
int	max;			// max size for matrix
int	C;				// Coeff for Hill-Criming term
int sum_column;		// total num in one column
int sum_row;		// total num in one row
int sum_diag1;		// total num in diagonal
int sum_diag2;		// total num in diagonal

int V[100][100];	// voltage vector
int U[100][100];	// input vector


/**************************************************************
 * FUNC: main
 * DESC: main function
 *
 * ***********************************************************/

int main(int argc, char *argv[]){

    //======= Variables =======
    
	int t, i, j;
	int seed;


	//======= Check the arguments =======
	
	if ( argc != 2 && argc != 3){

		fprintf(
			stderr,
			"\n%s <Matrix Size> [Seed Num for rand]\n"
			"\n"
			"\tMatrix Size: 4-100\n"
			"\tSeed Num for rand: 10 by default"
			"\n\n",
			argv[0]
		);

		exit (1);
	}



	//======= Get Parameters =======
	
	max = atoi(argv[1]);

	if ( argc == 2 )
		seed = 10;
	else
		seed = atoi(argv[2]);


	printf("PARAM: max	= %d\n", max);
	printf("PARAM: seed = %d\n", seed);
	printf("\n");


	//======= Initialization =======

	srand(seed);
	init(max);

	t = 0;
	ng_pt = 1;
	C = 1;


	//======= Start =======

	while ( ng_pt > 0 && t < 1000){

		ng_pt = 0;
		
		for ( i = 0; i < max; i++ ){
			for ( j = 0; j < max; j++){


				//======= Update Input Vector =======

				U[i][j] = U[i][j] + dU(i, j);
				
				if ( U[i][j] > 15) U[i][j] = 15;
				if ( U[i][j] < -15) U[i][j] = -15;


				//======= Calculate Voltage Vector =======
				
				if ( U[i][j] > 0) V[i][j] = 1;
				else V[i][j] = 0;

	
				if (sum_column != 1
					|| sum_row != 1
					|| sum_diag1 >= 2
					|| sum_diag2 >= 2)
					ng_pt++;
			}
		}

		printf (
			"\n\n(t	= %4d, ng_pt = %2d)\n\n", 
			t, 
			ng_pt
		);
		
		disp();

		t++;

		//======= Update Coeff for Hill-crimbing =======
		
		if ( t % 20 < 5) C = 4;
		else C = 1;
	}


	/*======= End Message =======*/

	if ( ng_pt == 0 )

		printf(
			"Solved! (t=%d)\n", 
			t-1
		);
	else
		printf("Unsolved (ng_pt=%d)\n",
			ng_pt
		);
}


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

