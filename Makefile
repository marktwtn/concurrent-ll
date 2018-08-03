.PHONY: all
all: main.c list.c list.h
	gcc main.c list.c

run: all
	./a.out
