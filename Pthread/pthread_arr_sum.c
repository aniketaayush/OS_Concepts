#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* add_elements(void* args) {
    // args contains the starting index 
    // Calculate the sum and populate back to args
    int index = *(int *)args;
    int sum = 0;
    for (int i=0; i<5; ++i) {
        sum += primes[index+i];
    }    
    *(int *)args = sum;
    printf("Thread local sum, idx=%d = %d\n", index, sum);
    return args;
}

int main() {
    pthread_t th[2];
    for (int i=0; i<2; ++i) {
        int *idx = malloc(sizeof(int));
        *idx = i*5;
        if (pthread_create(&th[i], NULL, &add_elements, (void *)idx)) {
            perror("Thread creation failed\n");
        }
    }

    int gsum = 0;
    for (int i=0; i<2; ++i) {
        int *res;
        if (pthread_join(th[i], (void **)&res)) {
            perror("Failed to join thread\n");
        }
        gsum += *res;
        free(res);
    }

    printf("Global Sum of Array = %d\n", gsum);

    return 0;
}