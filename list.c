#include "list.h"

node_t *node_delete(int val) {
    node_t *prev, *current;
    prev = &ListHead;

    pthread_mutex_lock(&prev->lock);
    while ((current = prev->link)) {
        pthread_mutex_lock(&current->lock);
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
    node_t *prev, *current;
    prev = &ListHead;

    pthread_mutex_lock(&prev->lock);
    while ((current = prev->link)) {
        pthread_mutex_lock(&current->lock);
        if (current->val == target) {
            node_t *newNode = malloc(sizeof(node_t));
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
    pthread_mutex_unlock(&prev->lock);
    return (-1);
}
