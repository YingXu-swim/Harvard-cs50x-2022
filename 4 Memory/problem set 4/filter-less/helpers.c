#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each line
    for (int i = 0; i < height; i++)
    {
        //for each num in line
        for (int j = 0; j < width; j++)
        {
            // get avg
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            // resign
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;

    // for each line
    for (int i = 0; i < height; i++)
    {
        //for each num in line
        for (int j = 0; j < width; j++)
        {
            // resign
            sepiaRed = 0.393 * (float) image[i][j].rgbtRed + 0.769 * (float) image[i][j].rgbtGreen + 0.189 * (float) image[i][j].rgbtBlue;
            sepiaGreen = 0.349 * (float) image[i][j].rgbtRed + 0.686 * (float) image[i][j].rgbtGreen + 0.168 * (float) image[i][j].rgbtBlue;
            sepiaBlue = 0.272 * (float) image[i][j].rgbtRed + 0.534 * (float) image[i][j].rgbtGreen + 0.131 * (float) image[i][j].rgbtBlue;

            // resign
            if (sepiaRed > 255)
            {
                sepiaRed = 255.0;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255.0;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255.0;
            }

            image[i][j].rgbtBlue = round(sepiaBlue);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtRed = round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int w = round(width * 0.5);

    if (width % 2 != 0)
    {
        w = (width - 1) * 0.5;
    }

    RGBTRIPLE *temp1 = malloc(1 * sizeof(RGBTRIPLE));

    // for each line
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // exchange value
            *temp1 = image[i][j];
            image[i][j] = image[i][width-1-j];
            image[i][width-1-j] = *temp1;
        }
    }
    free(temp1);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy
    RGBTRIPLE *new_image = (RGBTRIPLE *)malloc(height * width *sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            *(new_image + i * width + j) = image[i][j];
        }
    }

    float value_r = 0;
    float value_g = 0;
    float value_b = 0;
    // sign if it is in the edge of square
    int up = 1;
    int down = 1;
    int left = 1;
    int right = 1;

    int cnt = 1;

    // for each line
    for (int i = 0; i < height; i++)
    {
        // for each num in line
        for (int j = 0; j < width; j++)
        {
            up = 1;
            down = 1;
            left = 1;
            right = 1;
            cnt = 1;

            value_r = (new_image + i * width + j)->rgbtRed;
            value_g = (new_image + i * width + j)->rgbtGreen;
            value_b = (new_image + i * width + j)->rgbtBlue;

            // first line
            if (i == 0)
            {
                up = 0;
            }
            else if (i == height - 1) // last line
            {
                down = 0;
            }
            // first column
            if (j == 0)
            {
                left = 0;
            }
            else if (j == width - 1)// last column
            {
                right = 0;
            }

            if (up == 1)
            {
                value_r += (new_image + (i-1)*width + j)->rgbtRed;
                value_g += (new_image + (i-1)*width + j)->rgbtGreen;
                value_b += (new_image + (i-1)*width + j)->rgbtBlue;
                cnt += 1;
            }
            if (down == 1)
            {
                value_r += (new_image + (i+1)*width + j)->rgbtRed;
                value_g += (new_image + (i+1)*width + j)->rgbtGreen;
                value_b += (new_image + (i+1)*width + j)->rgbtBlue;
                cnt += 1;
            }
            if (left == 1)
            {
                value_r += (new_image + i*width + j-1)->rgbtRed;
                value_g += (new_image + i*width + j-1)->rgbtGreen;
                value_b += (new_image + i*width + j-1)->rgbtBlue;
                cnt += 1;
            }
            if (right == 1)
            {
                value_r += (new_image + i*width + j+1)->rgbtRed;
                value_g += (new_image + i*width + j+1)->rgbtGreen;
                value_b += (new_image + i*width + j+1)->rgbtBlue;
                cnt += 1;
            }

            if (up == 1 && right == 1)
            {
                value_r += (new_image + (i-1)*width + j+1)->rgbtRed;
                value_g += (new_image + (i-1)*width + j+1)->rgbtGreen;
                value_b += (new_image + (i-1)*width + j+1)->rgbtBlue;
                cnt += 1;
            }
            if (up == 1 && left == 1)
            {
                value_r += (new_image + (i-1)*width + j-1)->rgbtRed;
                value_g += (new_image + (i-1)*width + j-1)->rgbtGreen;
                value_b += (new_image + (i-1)*width + j-1)->rgbtBlue;
                cnt += 1;
            }
            if (down == 1 && right == 1)
            {
                value_r += (new_image + (i+1)*width + j+1)->rgbtRed;
                value_g += (new_image + (i+1)*width + j+1)->rgbtGreen;
                value_b += (new_image + (i+1)*width + j+1)->rgbtBlue;
                cnt += 1;
            }
            if (down == 1 && left == 1)
            {
                value_r += (new_image + (i+1)*width + j-1)->rgbtRed;
                value_g += (new_image + (i+1)*width + j-1)->rgbtGreen;
                value_b += (new_image + (i+1)*width + j-1)->rgbtBlue;
                cnt += 1;
            }

            image[i][j].rgbtRed = round(value_r / cnt);
            image[i][j].rgbtGreen = round(value_g / cnt);
            image[i][j].rgbtBlue = round(value_b / cnt);
        }
    }

    free(new_image);

    return;
}
