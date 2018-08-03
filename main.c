#include "list.h"

#define THREAD_NUM 2

void *child(void *arg) {
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

    return 0;
}
