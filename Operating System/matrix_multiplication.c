#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <time.h>

#define MAX_SIZE 100

int matrixA[MAX_SIZE][MAX_SIZE];
int matrixB[MAX_SIZE][MAX_SIZE];
int resultMatrix[MAX_SIZE][MAX_SIZE];

int rowsA, colsA, rowsB, colsB;

void initialize_matrices()
{
    freopen("input.txt", "r", stdin);
    printf("Enter the number of rows in the first matrix (A): ");
    scanf("%d", &rowsA);

    printf("Enter the number of columns in the first matrix (A): ");
    scanf("%d", &colsA);

    printf("Enter the number of rows in the second matrix (B): ");
    scanf("%d", &rowsB);

    printf("Enter the number of columns in the second matrix (B): ");
    scanf("%d", &colsB);

    if (colsA != rowsB)
    {
        printf("\n\nMatrix dimensions are not compatible for multiplication.\nThe number of columns in A must equal the number of rows in B.\n\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter elements for the first matrix (A):\n");
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            printf("Matrix A[%d][%d]: ", i, j);
            scanf("%d", &matrixA[i][j]);
        }
    }

    printf("Enter elements for the second matrix (B):\n");
    for (int i = 0; i < rowsB; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            printf("Matrix B[%d][%d]: ", i, j);
            scanf("%d", &matrixB[i][j]);
        }
    }
}

void multiply_matrices()
{
    // int shmget(key_t key, size_t size, int shmflg)
    int shm_id = shmget(IPC_PRIVATE, rowsA * colsB * sizeof(int), 0666);

    if (shm_id == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // void *shmat(int shmid, const void *shmaddr, int shmflg)
    int *resultMatrix = (int *)shmat(shm_id, NULL, 0);

    if (resultMatrix == (int *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rowsA; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            for (int j = 0; j < colsB; j++)
            {
                resultMatrix[i * colsB + j] = 0;
                for (int k = 0; k < colsA; k++)
                {
                    resultMatrix[i * colsB + j] += matrixA[i][k] * matrixB[k][j];
                }
            }
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < rowsA; i++)
    {
        int status;
        wait(NULL);
    }

    printf("\nResulting matrix C:\n");
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            printf("%5d ", resultMatrix[i * colsB + j]);
        }
        printf("\n");
    }

    // int shmdt(const void *shmaddr)
    shmdt(resultMatrix);
    // int shmctl(int shmid, int cmd, struct shmid_ds *buf)
    shmctl(shm_id, IPC_RMID, NULL);
}

void print_matrices()
{
    printf("\n\nMatrix A:\n");
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            printf("%5d ", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\nMatrix B:\n");
    for (int i = 0; i < rowsB; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            printf("%5d ", matrixB[i][j]);
        }
        printf("\n");
    }
}

void multiply_matrices_c()
{
    int result[MAX_SIZE][MAX_SIZE] = {0};

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            for (int k = 0; k < colsA; k++)
            {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    printf("\nResulting matrix C (C multiplication):\n");
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            printf("%5d ", result[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    initialize_matrices();
    print_matrices();

    // clock_t start_time1 = clock();
    // multiply_matrices_c();
    // clock_t end_time1 = clock();

    // double execution_time_c = ((double)(end_time1 - start_time1)) / CLOCKS_PER_SEC;
    // printf("\nExecution time (C multiplication): %f seconds\n\n", execution_time_c);

    clock_t start_time = clock();
    multiply_matrices();
    clock_t end_time = clock();

    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f seconds\n\n", execution_time);

    return 0;
}
