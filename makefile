all: CC/prog1

CC/prog1: prog1.c
	gcc -std=c89 prog1.c -lm -o prog1 