#==============================================================
# FILE: Makefile
# DESC: Makefile to compile cui_main
#
# AUTHOR: S.Yatsuzuka
#
#==============================================================

CC=gcc
CFLAGS=-I.

all: cui_main gui_main

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

cui_main: common.o cui_main.o
	$(CC) -o cui_main common.o cui_main.o

gui_main: gui_main.o
	$(CC) -o gui_main gui_main.o -lX11

clean:
	rm -f cui_main gui_main *.o
