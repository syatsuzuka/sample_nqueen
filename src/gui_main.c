/**************************************************************
 * FILE: gui_main.c
 * DESC: solve N Queen Problem
 *
 * AUTHOR: S.Yatsuzuka
 *
 * ***********************************************************/

//======= Preprocessor =======

#include "common.h"
#include "gui_main.h"
#define VERSION "ver 0.1"


/**************************************************************
 * FUNC: main
 * DESC: main function
 *
 * ***********************************************************/

int main(int argc, char *argv[]){

    //======= Variables =======
    
	int t, i, j;
	int seed;
	int prev;


	//======= Check the arguments =======
	
	if ( argc != 2 && argc != 3){

		fprintf(
			stderr,
			"\nThis is a sample program to solve N Queen Puzzle using RNN (Recurrent Neural Network)\n\n"
			"\n[VERSION]\n"
			"\t"
			VERSION
			"\n\n[USAGE]\n"
			"\t%s <Matrix Size> [Seed Num for rand]\n"
			"\n[INPUT PARAMETERS]\n"
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


	//======= Display window =======
	

	window();
	gc = XCreateGC (d, w0, 0, 0);
	UNIT = ( GRID_SIZE ) / max;
	put_frame(max, UNIT);


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

				prev = V[i][j];


				//======= Calculate Voltage Vector =======
				
				if ( U[i][j] > 0) V[i][j] = 1;
				else V[i][j] = 0;

				if (prev != V[i][j]) 
					put_queen(i, j, UNIT);

	
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

	getchar();
	getchar();
}


/**************************************************************
 * FUNC: window
 * DESC: 
 * 
 * ***********************************************************/

void window(void){
	

	//======= Create Window object =======

	d = XOpenDisplay(NULL);
	black = BlackPixel(d, 0);
	white = WhitePixel(d, 0);

	w0 = XCreateSimpleWindow (
		d,
		RootWindow (d, 0),
		WIN_OFFSET,
		WIN_OFFSET,
		WIN_SIZE,
		WIN_SIZE,
		2,
		black,
		white
	);

	XMapWindow (d, w0);
	XFlush(d);
	sleep(3);
	gc = XCreateGC (d, w0, 0, 0);
}

/**************************************************************
 * FUNC: put_frame
 * DESC:
 *
 * ***********************************************************/

void put_frame(int max, int UNIT){

	//======= Variables =======

	int x, y;


	//======= Set up color =======

	XSetForeground (d, gc, black);


	//======= Draw vertical line =======

	for(x = 0; x <= max; x++){

		XDrawLine(
			d, 
			w0, 
			gc, 
			x * UNIT + MARGIN, 
			0 + MARGIN, 
			x * UNIT + MARGIN,
			UNIT * max + MARGIN 
		);
	}


	//======= Draw horizontal line =======

	for (y = 0; y <= max; y++){

		XDrawLine (
			d,
			w0,
			gc,
			0 + MARGIN,
			y * UNIT + MARGIN,
			UNIT * max + MARGIN,
			y * UNIT + MARGIN
		);
	}

	XFlush (d);
			
}

/**************************************************************
 * FUNC: put_queen
 * DESC:
 *
 * ***********************************************************/

void put_queen(int i, int j, int UNIT){


	//======= Fill a cell with black ( Put a Queen ) =======

	if ( V[i][j] == 1 ){

		XSetForeground (
			d,
			gc,
			black
		);

		XFillRectangle(
			d,
			w0,
			gc,
			(j) * UNIT + MARGIN,
			(i) * UNIT + MARGIN,
			UNIT,
			UNIT
		);
	}

	//======= Fill a cell with white =======

	else {
	
		XSetForeground (
			d,
			gc,
			white
		);

		XFillRectangle(
			d,
			w0,
			gc,
			(j) * UNIT + 1 + MARGIN,
			(i) * UNIT + 1 + MARGIN,
			UNIT - 1,
			UNIT - 1
		);
	}

	XFlush (d);
	XSync (d, 0);
}
