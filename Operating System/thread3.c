#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *work_thread(void *arg);

int main() {
    pthread_t thread;
    int *ar = malloc(2 * sizeof(int)); // Allocate memory for the array

    if (ar == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    void *msg;

    printf("Enter two numbers:");
    for (int i = 0; i < 2; i++) {
        scanf("%d", &ar[i]);
    }

    pthread_create(&thread, NULL, work_thread, ar);
    pthread_join(thread, &msg);

    int sum = *((int*)msg);
    printf("Sum is: %d\n", sum);

    free(ar); // Free the allocated memory

    return 0;
}

void *work_thread(void *arg) {
    int *x = (int*)arg;

    int *sum = malloc(sizeof(int)); // Allocate memory for the sum

    if (sum == NULL) {
        fprintf(stderr, "Memory allocation failed in the thread\n");
        pthread_exit(NULL);
    }

    *sum = x[0] + x[1];

    pthread_exit(sum);
}

