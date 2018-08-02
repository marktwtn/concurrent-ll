#ifndef LIST_H
#define LIST_H

#include <pthread.h>

typedef struct node {
    int val;
    struct node *link;
    pthread_mutex_t lock;
} node_t;

node_t *node_delete(int val);
int node_insert(int val, int target);

#endif
