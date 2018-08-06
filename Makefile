thread?=2
range?=10
times?=10

.PHONY: all
all: main.c list.c list.h
	gcc -DEXE_TIMES=$(times) -DTHREAD_NUM=$(thread) -DRANDOM_RANGE=$(range) main.c list.c -lpthread

run: all
	./a.out

debug:
	gcc -DDEBUG -DEXE_TIMES=$(times) -DTHREAD_NUM=$(thread) -DRANDOM_RANGE=$(range) main.c list.c -lpthread
	./a.out
