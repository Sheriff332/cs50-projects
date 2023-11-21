// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t header[44];
    fread(header,sizeof(uint8_t), 44, input);
    fwrite(header,sizeof(uint8_t), 44, output);
    int16_t buffer;
    while (fread(&buffer,sizeof(int16_t),1, input))
    {
        printf("Scaled Sample: %d\n", buffer);
        buffer = buffer * factor;
        printf("Scaled Sample: %d\n", buffer);
        fwrite(&buffer,sizeof(int16_t),1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
