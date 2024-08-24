#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* thread_func() {
    printf("Hello from thread\n");
    sleep(3);
    printf("End of thread function\n");
}

int main() {
    pthread_t t1, t2;
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
    return 0;
}