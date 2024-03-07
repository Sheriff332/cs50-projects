#include "helpers.h"

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
    RGBTRIPLE copy[height][width];
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
                    if ((i+x) >= 0 || (i+x) < width || (j+y) >= 0 || (j+y) < height)
                    {
                        sumRed+=copy[(i+x)][(j+y)].rgbtRed;
                        sumBlue+=copy[(i+x)][(j+y)].rgbtBlue;
                        sumGreen+=copy[(i+x)][(j+y)].rgbtGreen;
                        counter+=1;
                    }

                }
            }
            image[i][j].rgbtRed= (int)(sumRed/counter);
            if (image[i][j].rgbtRed > 255) {image[i][j].rgbtRed = 255;}
            image[i][j].rgbtBlue= (int)(sumBlue/counter);
            if (image[i][j].rgbtBlue > 255) {image[i][j].rgbtBlue = 255;}
            image[i][j].rgbtGreen= (int)(sumGreen/counter);
            if (image[i][j].rgbtGreen > 255) {image[i][j].rgbtGreen = 255;}
        }
    }
}
