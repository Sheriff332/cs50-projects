#include <stdio.h>
#include <stdlib.h> // for malloc and free
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[8]; // Changed size to 8 to include space for null terminator '\0'

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Allocate memory for the plate number and copy the buffer contents
        plates[idx] = malloc(8 * sizeof(char)); // Allocate memory for 8 characters (including null terminator)
        if (plates[idx] == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
        strcpy(plates[idx], buffer);

        idx++;
    }

    fclose(infile); // Close the file after reading

    // Print plate numbers
    for (int i = 0; i < idx; i++) // Changed loop condition to 'idx'
    {
        printf("%s\n", plates[i]);
        free(plates[i]); // Free allocated memory
    }

    return 0;
}
