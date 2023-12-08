#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char character;

    // Open the input file in read mode
    inputFile = fopen("input.txt", "r");
    
    // Check if the input file exists
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1; // Return an error code
    }

    // Open the output file in write mode
    outputFile = fopen("output.txt", "w");
    
    // Check if the output file was created successfully
    if (outputFile == NULL) {
        printf("Error opening the output file.\n");
        fclose(inputFile); // Close the input file before returning
        return 2; // Return an error code
    }

    // Read each character from the input file and write it to the output file
    while ((character = fgetc(inputFile)) != EOF) {
        printf("%c",character);
        fputc(character, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0; // Return success
}

