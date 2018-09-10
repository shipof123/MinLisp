all: polish.c
	gcc mpc.c polish.c -o MinLisp -lm -ledit
