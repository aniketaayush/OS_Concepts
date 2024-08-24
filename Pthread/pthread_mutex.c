#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* thread_func() {
    pthread_mutex_lock(&mutex);
    for (int i=0; i<10000; ++i) {
        ++mails;
    }
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    if(pthread_create(&t1, NULL, &thread_func, NULL) != 0) {
        printf("Failed to create thread t1\n");
        return 1;
    }
    if(pthread_create(&t2, NULL, &thread_func, NULL) != 0) {
        printf("Failed to create thread t2\n");
        return 1;
    }
    if(pthread_join(t1, NULL) !=0) {
        printf("Failed to join thread t1\n");
    }
    if(pthread_join(t2, NULL) !=0) {
        printf("Failed to join thread t2\n");
    }
    pthread_mutex_destroy(&mutex);
    printf("Total mail = %d\n", mails);
    return 0;
}