/**************************************************************
 *
 *
 * ***********************************************************/

/*======= Preprocessor =======*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define A 1
#define B 1


/*======= Proto Type =======*/

void init (int max, int seed);
double urand(int seed);
int dU(int i, int j);


/*======= Global Variables =======*/

int conf, diag, row, length, UNIT, max, sum_column, sum_row, diagonal1, diagonal2, C;

int V[101][101];
int U[101][101];

/**************************************************************
 *
 *
 * ***********************************************************/

int main(){

	/*======= Variables =======*/

	int t, i, j;
	int seed;

	/*======= Get Parameters =======*/

	printf("Please input problem size. (4_100)");
	scanf("%d", &max);
	printf("Please input seed.");
	scanf("%d", &seed);


	/*======= Initialization =======*/

	init(max, seed);

	t = 0;
	diag = 1;
	C = 1;


	/*======= Start =======*/

	while ( diag > 0 && t < 1000){

		diag = 0;
		
		for ( i = 1; i <= max; i++ ){

			for ( j = 1; j <= max; j++){

				U[i][j] = U[i][j] + dU(i, j);
				
				if ( U[i][j] > 15) U[i][j] = 15;
				if ( U[i][j] < -15) U[i][j] = -15;

				if ( U[i][j] > 0) V[i][j] = 1;
				else V[i][j] = 0;

	
				conf = 1;
				if (sum_column + sum_row == 2
					&& diagonal1 < 2
					&& diagonal2 < 2)
					conf = 0;

				diag += conf;
			}
		}

		t++;
		if ( t % 20 < 5) C = 4;
		else C = 1;
	}


	/*======= Display output =======*/

	printf ("\n");
	
	for ( i = 1; i <= max; i++){
		for ( j = 1; j <= max; j++){
			printf("%d ", V[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");
	printf("Solved\a diag=%d t=%d\n", diag, t);
}


/**************************************************************
 *  
 *   
 * ***********************************************************/

void init(int max, int seed){
	
	/*======= Variables =======*/

	int i, j, x;

	/*======= Initialization =======*/

	for ( i = 1; i <= max; i++){
		for ( j = 1; j <= max; j++){
			x = (int)((double)20 * urand(seed));
			U[i][j] = x - 10;

			if ( U[i][j] < 0 ) V[i][j] = 1;
			else V[i][j] = 0;
		}
	}
}

/**************************************************************
 *  
 *   
 * ***********************************************************/

double urand(int seed){
	
	/*======= Variables =======*/

	int i;

	/*======= Initialization =======*/
	srand(seed);
	
	return ((double)rand()+1.0)/((double)RAND_MAX+2.0);
}


/**************************************************************
 *  
 *   
 * ***********************************************************/

int dU(int i, int j){

	/*======= Variables =======*/

	int k, du, h, C;


	C = 1;

	sum_column = 0;
	sum_row = 0;


	/*======= Check.1 =======*/

	for ( k = 1; k <= max; k++){
		sum_row = sum_row + V[i][k];
		sum_column = sum_column + V[k][j];
	}


	/*======= Check.2 =======*/

	diagonal1 = 0;
	k = 1;

	while((j+k) <= max && (i-k) >= 1){

		diagonal1 = diagonal1 + V[i-k][j+k];
		k++;
	}

	k = 1;

	while((j-k) >= 1 && (i+k) <= max){
		diagonal1 = diagonal1 + V[i+k][j-k];
		k++;
	}

	diagonal2 = 0;
	k = 1;

	while((j+k) <= max && (i+k) <= max){
		diagonal2 = diagonal2 + V[i+k][j+k];
		k++;
	}

	k = 1;

	while((j-k) >= 1 && (i-k) >= 1){
		diagonal2 = diagonal2 + V[i-k][j-k];
		k++;
	}


	/*======= Define h func =======*/

	h = 0;
	if (sum_column == 0) h = 1;
	if (sum_row == 0) h++;


	/*======= Define dUij =======*/

	du = -A * (sum_row + sum_column - 2) 
		-B * (diagonal1 + diagonal2) + C * h;

	return (du);

}

