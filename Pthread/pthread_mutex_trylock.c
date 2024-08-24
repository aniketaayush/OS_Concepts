#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h> // For error codes like EBUSY

pthread_mutex_t mutex;

void* routine () {
    int lock_val;
    if((lock_val = pthread_mutex_trylock(&mutex)) == 0) { // We got the lock
        printf("Lock Taken\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    } else {
        if (lock_val == EBUSY) {
            printf("Lock already acquired by another thread\n");
        } else {
            printf("Didn't got the lock\n");
        }
    }
}

int main() {
    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);
    for (int i=0; i<4; ++i) {
        if (pthread_create(&th[i], NULL, &routine, NULL)) {
            perror("Thread creation failed\n");
            return 1;
        }
    }
    for (int i=0; i<4; ++i) {
        if (pthread_join(th[i], NULL)) {
            perror("Thread join failed\n");
            return 2;
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}