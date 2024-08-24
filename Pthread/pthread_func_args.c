#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* print_primes(void *arg) {
    printf("%d ",*(int *)arg);
}

int main() {
    // Make each thread print a unique prime
    pthread_t th[10];
    for (int i=0; i<10; ++i) {
        if (pthread_create(&th[i], NULL, &print_primes, (void*)(&primes[i]))) {
            perror("Thread creation failed\n");
        }
    }
    for (int i=0; i<10; ++i) {
        if (pthread_join(th[i], NULL)) {
            perror("Thread join failed\n");
        }
    }
    printf("\n");
}