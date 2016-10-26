/**************************************************************
 * FILE: gui_main.h
 * DESC: header file for gui_main.c
 *
 * AUTHOR: S.Yatsuzuka
 *
 * ***********************************************************/


//======= Preprocessor =======

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define WIN_SIZE 600
#define WIN_OFFSET 100
#define GRID_SIZE 500
#define MARGIN 50


//======= Proto Type =======

void window(void);
void put_frame(int max, int UNIT);
void put_queen(int i, int j, int UNIT);


//======= Global Variables =======

Display *d;
Window w0;
unsigned long black, white;
XEvent e;
GC gc;
int UNIT;
