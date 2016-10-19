/**************************************************************
 * FILE: cui_main.c
 * DESC: solve N Queen Problem
 *
 * AUTHOR: S.Yatsuzuka
 *
 * ***********************************************************/

//======= Preprocessor =======

#include "common.h"


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

