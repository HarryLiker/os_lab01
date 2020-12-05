FLAGS = -std=c11 -pedantic -Wall -Werror

all: lab.out child.out

lab.out: lab.c
	gcc $(FLAGS) lab.c -o lab.out

child.out: child.c
	gcc $(FLAGS) child.c -o child.out

clean:
	rm *.out