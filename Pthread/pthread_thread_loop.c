#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    pthread_mutex_lock(&mutex);
    for (int i=0; i<1000000; ++i) {
        ++mails;
    }
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_t th[8];
    for (int i=0; i<8; ++i) {
        if (pthread_create(&th[i], NULL, &routine, NULL)) {
            return 1;
        }
        printf("Thread %d created\n", i);
    }

    for (int i=0; i<8; ++i) {
        if (pthread_join(th[i], NULL)) {
            return 2;
        }
        printf("Thread %d finished\n", i);
    }

    printf("Number of mails = %d\n", mails);

    pthread_mutex_destroy(&mutex);
    return 0;
}