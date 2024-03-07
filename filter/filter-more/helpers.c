#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    grayscale(height, width, image);//CS50 did not greyscale the image first... but this makes code small so black and white it is!

    //Gaussian Blur and Sobel in the same loop
    RGBTRIPLE copy[height][width];
    int gx[height][width];
    int gy[height][width];
    int sobel[height][width];
    int factor;
    int gfactor;
    double sobelval;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed=0;
            int sumBlue=0;
            int sumGreen=0;
            int counter = 0;
            for (int x=-1; x<=1; x++)
            {
                for (int y=-1; y<=1; y++)
                {
                    if ((i+y) >= 0 && (i+y) < height && (j+x) >= 0 && (j+x) < width)
                    {
                        factor=1;
                        if (x==0){factor*=2;}
                        if (y==0){factor*=2;}
                        sumRed+=factor*copy[(i+y)][(j+x)].rgbtRed;
                        sumBlue+=factor*copy[(i+y)][(j+x)].rgbtBlue;
                        sumGreen+=factor*copy[(i+y)][(j+x)].rgbtGreen;
                        counter+=factor;
                        gfactor=x;
                        if (y==0){gfactor*=2;}
                        gx[i][j]+=gfactor*copy[(i+y)][(j+x)].rgbtRed;
                        gfactor=y;
                        if (x==0){gfactor*=2;}
                        gy[i][j]+=gfactor*copy[(i+y)][(j+x)].rgbtRed;
                    }

                }
            }
            image[i][j].rgbtRed= (int)(sumRed/counter);
            if (image[i][j].rgbtRed > 255) {image[i][j].rgbtRed = 255;}
            image[i][j].rgbtBlue= (int)(sumBlue/counter);
            if (image[i][j].rgbtBlue > 255) {image[i][j].rgbtBlue = 255;}
            image[i][j].rgbtGreen= (int)(sumGreen/counter);
            if (image[i][j].rgbtGreen > 255) {image[i][j].rgbtGreen = 255;}
            sobelval=(pow(gx[i][j], 2)+pow(gy[i][j], 2));
            sobelval=(int) sqrt(sobelval);
            if (sobelval>255){sobelval=255;}
            image[i][j].rgbtRed=sobelval;
            image[i][j].rgbtBlue=sobelval;
            image[i][j].rgbtGreen=sobelval;
        }
    }
}
