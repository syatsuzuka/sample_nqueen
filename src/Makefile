#==============================================================
# FILE: Makefile
# DESC: Makefile to compile cui_main
#
# AUTHOR: S.Yatsuzuka
#
#==============================================================

cui_main: common.o cui_main.o
	gcc -o cui_main common.o cui_main.o

common.o: common.c
	gcc -c common.c

cui_main.o: cui_main.c
	gcc -c cui_main.c

clean:
	rm -f cui_main common.o cui_main.o
