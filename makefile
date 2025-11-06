programme: event.o main_event.o
	gcc event.o main_event.o -o programme -g

main_event.o: main_event.c event.h
	gcc -c main_event.c -g

event.o: event.c event.h
	gcc -c event.c -g

