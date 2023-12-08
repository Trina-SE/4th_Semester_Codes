#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

pthread_mutex_t mutex;
pthread_mutex_t write_mutex;
int readers_count = 0;

void *reader(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        readers_count++;
        if (readers_count == 1) {
            pthread_mutex_lock(&write_mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Read the shared resource (simulate reading)
        printf("Reader is reading...\n");
        usleep(rand() % 1000000);

        pthread_mutex_lock(&mutex);
        readers_count--;
        if (readers_count == 0) {
            pthread_mutex_unlock(&write_mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Simulate more reading
        usleep(rand() % 1000000);
    }
}

void *writer(void *arg) {
    while (1) {
        pthread_mutex_lock(&write_mutex);

        // Write to the shared resource (simulate writing)
        printf("Writer is writing...\n");
        usleep(rand() % 1000000);

        pthread_mutex_unlock(&write_mutex);

        // Simulate more writing
        usleep(rand() % 1000000);
    }
}
int main() {
    
    srand(time(NULL));

    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&write_mutex, NULL);

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writer_threads[i], NULL, writer, NULL);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    return 0;
}

