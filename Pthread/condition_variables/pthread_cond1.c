#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
    Problem Statement: There is a gas station where fuel refill and car filling it's fuel tank is happening at the same time.
    Fuel refill will increase the full in gas station whereas car taking fuel will decrease it.
    This scenario is implemented using two threads.
*/

int fuel = 0;
pthread_mutex_t mutexFuel;

void* fuel_filling(void* args) {
    for (int i=0; i<5; ++i) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Fuel filling...%d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        sleep(1);
    }
}

void* car(void* args) {
    pthread_mutex_lock(&mutexFuel);
    fuel -= 40;
    printf("Car tank filled....left fuel = %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main() {
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    for (int i=0; i<2; ++i) {
        if (i==1) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL)) {
                perror("Thread creation failed\n");
                return 1;
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL)) {
                perror("Thread creation failed\n");
                return 1;
            }
        }
    }
    for (int i=0; i<2; ++i) {
        if (pthread_join(th[i], NULL)) {
            perror("Thread join failed\n");
            return 2;
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    return 0;
}