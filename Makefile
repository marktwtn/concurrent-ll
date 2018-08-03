.PHONY: all
all: main.c list.c list.h
	gcc main.c list.c -lpthread

run: all
	./a.out
