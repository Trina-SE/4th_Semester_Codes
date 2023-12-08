#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 4096 // You can adjust the buffer size as needed

int main() {
    int file_descriptor;
    char *buffer;
    ssize_t bytesRead;

    // Open the file for reading
    file_descriptor = open("example.txt", O_RDONLY);
    
    if (file_descriptor == -1) {
        perror("Error opening file for reading");
        return 1;
    }

    // Determine the file size
    off_t file_size = lseek(file_descriptor, 0, SEEK_END);
    lseek(file_descriptor, 0, SEEK_SET); // Reset file position to the beginning

    // Allocate memory for the buffer based on the file size
    buffer = (char *)malloc(file_size + 1); // +1 for null terminator

    if (buffer == NULL) {
        perror("Error allocating memory");
        close(file_descriptor);
        return 1;
    }

    // Read data from the file
    bytesRead = read(file_descriptor, buffer, file_size);

    if (bytesRead == -1) {
        perror("Error reading from file");
        close(file_descriptor);
        free(buffer);
        return 1;
    }

    // Null-terminate the buffer
    buffer[bytesRead] = '\0';

    // Print the contents of the file
    printf("\nContents of the file:\n%s\n", buffer);

    // Close the file and free allocated memory
    close(file_descriptor);
    free(buffer);

    return 0;
}

