#include <stdlib.h>

#include "list.h"

node_t ListHead = { .val = 0 };

node_t *node_delete(int val) {
    node_t *prev, *current;
    int getlock; // 0 : acquire lock successfully
    prev = &ListHead;

    pthread_mutex_lock(&prev->lock);
    while ((current = prev->link)) {
        pthread_mutex_trylock(&current->lock);
        // unable to get the lock
        if (getlock != 0) {
            pthread_mutex_unlock(&prev->lock);
            return NULL;
        }
        if (current->val == val) {
            prev->link = current->link;
            current->link = NULL;
            pthread_mutex_unlock(&prev->lock);
            pthread_mutex_unlock(&current->lock);
            return current;
        }
        pthread_mutex_unlock(&prev->lock);
        prev = current;
    }
    pthread_mutex_unlock(&prev->lock);
    return NULL;
}

int node_insert(int val, int target) {
    node_t *prev, *current, *newNode;
    int getlock; // 0 : acquire lock successfully
    prev = &ListHead;

    pthread_mutex_lock(&prev->lock);
    while ((current = prev->link)) {
        getlock = pthread_mutex_trylock(&current->lock);
        // unable to get the lock
        if (getlock != 0) {
            pthread_mutex_unlock(&prev->lock);
            return -1;
        }
        // find the target value and insert the node after it
	if (current->val == target) {
            newNode = malloc(sizeof(node_t));
            newNode->val = val;
            newNode->link = current->link;
            current->link = newNode;
            pthread_mutex_unlock(&current->lock);
            pthread_mutex_unlock(&prev->lock);
            return 0;
        }
        pthread_mutex_unlock(&prev->lock);
        prev = current;
    }
    // does not find the target value and insert the node at the end of the list
    newNode->link = NULL;
    prev->link    = newNode;
    pthread_mutex_unlock(&prev->lock);
    return 0;
}
