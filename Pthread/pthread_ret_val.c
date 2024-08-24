#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void* roll_dice() {
    int *val = malloc(sizeof(int));
    *val = (rand()  % 6) + 1;
    return (void *)val;
}

int main() {
    srand(time(NULL));
    int* res[8];
    pthread_t th[8];
    for (int i=0; i<8; ++i) {
        if (pthread_create(&th[i], NULL, &roll_dice, NULL)) {
            return 1;
        }
    }
   
    for (int i=0; i<8; ++i) {
        if (pthread_join(th[i], (void **)(&res[i]))) {
            return 2;
        }
    }
    
    for (int i=0; i<8; ++i) {
        printf("Dice Roll Thread %d = %d\n", i, *res[i]);
         free(res[i]);
    }
    return 0;
}