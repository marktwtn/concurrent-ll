#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "list.h"

#ifndef THREAD_NUM
#define THREAD_NUM 2
#endif
#ifndef RANDOM_RANGE
#define RANDOM_RANGE 10
#endif
#ifndef EXE_TIMES
#define EXE_TIMES 10
#endif

extern node_t ListHead;

void *child(void *arg) {
    srand(time(NULL));
    int randV, randT;
    node_t *ret;
    for(int i=0; i<EXE_TIMES; i++) {
        if(rand()%2) {
            randV = rand()%RANDOM_RANGE + 1;
            ret = node_delete(randV);
            if (ret) {
                free(ret);
                #ifdef DEBUG
                printf("Delete node with %d val.\n", randV);
                #endif
            } else {
                #ifdef DEBUG
                printf("Delete node with %d val. (FAILED)\n", randV);
                #endif
	    }
	} else {
            randV = rand()%RANDOM_RANGE + 1;
            randT = rand()%(RANDOM_RANGE+1);
            if (!node_insert(randV, randT)) {
                #ifdef DEBUG
                printf("Insert node with %d val after node %d.\n", randV, randT);
                #endif
            } else {
                #ifdef DEBUG
                printf("Insert node with %d val after node %d. (FAILED)\n", randV, randT);
                #endif
	    }
	}
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t thr[THREAD_NUM];
    struct timeval start, end;
    int duration;

    gettimeofday(&start, NULL);
    for(int i=0; i<THREAD_NUM; i++) {
        pthread_create(&thr[i], NULL, child, NULL);
    }

    for(int i=0; i<THREAD_NUM; i++) {
        pthread_join(thr[i], NULL);
    }
    gettimeofday(&end, NULL);

    duration = (end.tv_sec * 1000000 + end.tv_usec) -
               (start.tv_sec * 1000000 + start.tv_usec);

    // print the result
    node_t *current;
    current = &ListHead;
    int index=0;
    printf("-----\n");
    printf("The singly-linked list:\n");
    printf("-----\n");
    printf("Node %d: val=%d\n", index++, current->val);
    while(current = current->link) {
        printf("Node %d: val=%d\n", index++, current->val);
    }
    printf("Thread total number: %d\n", THREAD_NUM);
    printf("Duration: %d (us)\n", duration);
    printf("Value range: 1 ~ %d\n", RANDOM_RANGE);
    printf("Operation execution per thread: %d \n", EXE_TIMES);

    return 0;
}
