thread?=2
range?=10

.PHONY: all
all: main.c list.c list.h
	gcc -DTHREAD_NUM=$(thread) -DRANDOM_RANGE=$(range) main.c list.c -lpthread

run: all
	./a.out

debug:
	gcc -DDEBUG -DTHREAD_NUM=$(thread) -DRANDOM_RANGE=$(range) main.c list.c -lpthread
	./a.out
