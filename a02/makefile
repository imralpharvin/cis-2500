bag: main.o bow.o bow.h
	gcc -Wall -ansi -pedantic main.o bow.o -o bag

main.o: main.c bow.c bow.h
	gcc -Wall -ansi -pedantic -c main.c -o main.o

bow.o: bow.c bow.h
	gcc -Wall -ansi -pedantic -c bow.c -o bow.o

clean: rm-i bag bow.o main.o
