.PHONY: clean

main : test.o
	gcc $^ -o $@

%.o : %.c
	gcc -c $^ -o $@

clean :
	rm -rf *o main
