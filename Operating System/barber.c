#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>
#include<stdlib.h>


#define NUM_CHAIRS 5

sem_t customers;
sem_t barbers;
sem_t accessSeats;
int numFreeSeats = NUM_CHAIRS;

void *barber_thread(void *arg) {
   while(1) {
        sem_wait(&customers); 
        sem_wait(&accessSeats);

        numFreeSeats++;
        printf("Barber: Cutting hair\n");

        sem_post(&barbers);
        sem_post(&accessSeats);
    }
}

void *customer_thread(void *arg) {
    sem_wait(&accessSeats); 

    if (numFreeSeats > 0) {
        numFreeSeats--;
        printf("Customer: Arrived, waiting for haircut\n");

        sem_post(&customers); 
        sem_post(&accessSeats); // Release seats
        sem_wait(&barbers); // Wait for the barber 
    } else {
        printf("Customer: Barber shop full, leaving\n");
        sem_post(&accessSeats); 
    }
}

int main() {
    pthread_t barber, customer;
    sem_init(&customers, 0, 0);
    sem_init(&barbers, 0, 0);
    sem_init(&accessSeats, 0, 1);

    pthread_create(&barber, NULL, barber_thread, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_create(&customer, NULL, customer_thread, NULL);
        sleep(1);
    }

    pthread_join(barber, NULL);

    return 0;
}

