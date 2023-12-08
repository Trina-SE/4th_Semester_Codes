#include <stdio.h>

int main() {
    FILE *file;
    char data[100];

    // Writing to a file
    file = fopen("example.txt", "w"); // "w" stands for write mode

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter some text to write to the file: ");
    fgets(data, sizeof(data), stdin);

    // Write data to the file
    fprintf(file, "%s", data);

    // Close the file
    fclose(file);

    // Reading from a file
    file = fopen("example.txt", "r"); // "r" stands for read mode

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read data from the file
    printf("\nContents of the file:\n");
    while (fgets(data, sizeof(data), file) != NULL) {
        printf("%s", data);
    }

    // Close the file
    fclose(file);

    return 0;
}

