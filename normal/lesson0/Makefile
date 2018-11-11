main : add.o sub.o main.o
	gcc add.o sub.o main.o -o main

add.o : add.c
	gcc -c add.c -o add.o

sub.o : sub.c
	gcc -c sub.c -o sub.o
main.o : main.c
	gcc -c main.c -o main.o

clean :
	rm -rf *.o main
