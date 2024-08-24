#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
    Problem Statement: There is a gas station where fuel refill and car filling it's fuel tank is happening at the same time.
    Fuel refill will increase the full in gas station whereas car taking fuel will decrease it.
    This scenario is implemented using two threads.

    Update1: Last program we can see that the fuel value was negative, in reality we will keep it above a certain threshold, i.e. 0
    We can add an if condition to not allow fuel to be taken if sufficient quantity is not available

    Update2: We achieved the objective in Update1 but we notice eventually the fuel reaches the capacity for car to be filled, what if
    we wanted the car to wait until fuel is available and then take it

    Update3: We tried a while loop but that was an infinite loop since mutex lock is taken and never released. The other function will
    keep waiting forever and fuel value will never increase. Here is where conditional variables are effective. Let's create a conditional
    variable and use that now.
*/

int fuel = 0;
pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

void* fuel_filling(void* args) {
    for (int i=0; i<5; ++i) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Fuel filling...%d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel);
        sleep(1);
    }
}

void* car(void* args) {
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40) {
        printf("Not sufficient fuel, can't fill tank\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        /*
            pthread_cond_wait() is equivalent to:
            1. pthread_mutex_unlock(&mutexFuel);
            2. wait for signal on condFuel
            3. pthread_mutex_lock(&mutexFuel);
        */
    }
    fuel -= 40;
    printf("Car tank filled....left fuel = %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main() {
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
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
    pthread_cond_destroy(&condFuel);
    return 0;
}