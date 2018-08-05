#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

#ifndef THREAD_NUM
#define THREAD_NUM 2
#endif
#ifndef RANDOM_RANGE
#define RANDOM_RANGE 10
#endif

extern node_t ListHead;

void *child(void *arg) {
    srand(time(NULL));
    for(int i=0; i<10; i++) {
        node_insert(rand()%RANDOM_RANGE + 1 ,0);
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t thr[THREAD_NUM];

    for(int i=0; i<THREAD_NUM; i++) {
        pthread_create(&thr[i], NULL, child, NULL);
    }

    for(int i=0; i<THREAD_NUM; i++) {
        pthread_join(thr[i], NULL);
    }

    // print the singly-linked list
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

    return 0;
}
