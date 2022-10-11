
automaton : stack.o matrix.o actions.o main.o
	gcc -Wall stack.o matrix.o actions.o main.o -o automaton 

stack.o : stack.c stack.h
	gcc -Wall -c stack.c

matrix.o : matrix.c matrix.h
	gcc -Wall -c matrix.c

actions.o : actions.c actions.h matrix.h
	gcc -Wall -c actions.c

main.o : main.c actions.h stack.h matrix.h
	gcc -Wall -c main.c
