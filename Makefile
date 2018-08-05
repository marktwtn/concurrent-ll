thread?=2

.PHONY: all
all: main.c list.c list.h
	gcc -DTHREAD_NUM=$(thread) main.c list.c -lpthread

run: all
	./a.out
