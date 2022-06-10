all: sort
sort: main.o algorytmy.o
	gcc -o sort main.o algorytmy.o
main.o: main.c algorytmy.h
	gcc -c main.c
algorytmy.o: algorytmy.c algorytmy.h
	gcc -c algorytmy.c
clean:
	rm *.o