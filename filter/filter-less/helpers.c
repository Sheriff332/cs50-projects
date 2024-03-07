#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width;j++)
        {
            int average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3;
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width;j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            if (sepiaRed> 255) {sepiaRed=255;}
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            if (sepiaGreen> 255) {sepiaGreen=255;}
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if (sepiaBlue> 255) {sepiaBlue=255;}
            image[i][j].rgbtRed= (int)sepiaRed;
            image[i][j].rgbtGreen= (int)sepiaGreen;
            image[i][j].rgbtBlue= (int)sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width/2;j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for the copy of the image
    RGBTRIPLE (*copy)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    if (copy == NULL)
    {
        // Handle memory allocation failure
        fprintf(stderr, "Failed to allocate memory for image copy\n");
        return;
    }

    // Copy the original image to the allocated memory
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Perform the blur operation on the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            int counter = 0;

            // Accumulate the sum of neighboring pixel values
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    int new_i = i + y;
                    int new_j = j + x;

                    // Check if the neighboring pixel is within the image bounds
                    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
                    {
                        sumRed += copy[new_i][new_j].rgbtRed;
                        sumBlue += copy[new_i][new_j].rgbtBlue;
                        sumGreen += copy[new_i][new_j].rgbtGreen;
                        counter++;
                    }
                }
            }

            // Ensure the counter is not zero to prevent division by zero
            if (counter == 0)
            {
                counter = 1;
            }

            // Calculate the average color values and update the original image
            image[i][j].rgbtRed = (int)(sumRed / counter);
            image[i][j].rgbtBlue = (int)(sumBlue / counter);
            image[i][j].rgbtGreen = (int)(sumGreen / counter);

            // Clamp the color values to the range [0, 255]
            image[i][j].rgbtRed = image[i][j].rgbtRed > 255 ? 255 : image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][j].rgbtBlue > 255 ? 255 : image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][j].rgbtGreen > 255 ? 255 : image[i][j].rgbtGreen;
        }
    }

    // Free the allocated memory for the image copy
    free(copy);
}
