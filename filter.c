#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int h = height;
    int w = width;
    for (int i = 0; i < h; i++) // loop through rows
    {
        for (int j = 0; j < w; j++) // loop throug colums within the row
        {
            int r = image[i][j].rgbtRed; // get red value
            int g = image[i][j].rgbtGreen; // get green value
            int b = image[i][j].rgbtBlue; // get blue value

            int avg = round((r + g + b) * 0.33333333); // compute average of rgb values

            // set rgb values to the average
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int h = height;
    int w = width;
    for (int i = 0; i < h; i++) // loop through rows
    {
        for (int j = 0; j < w; j++) // loop throug colums within the row
        {
            int r = image[i][j].rgbtRed; // get red value
            int g = image[i][j].rgbtGreen; // get green value
            int b = image[i][j].rgbtBlue; // get blue value

            // compute and assign sepia values to colors
            int newR = round(.393 * r + .769 * g + .189 * b);
            int newG = round(.349 * r + .686 * g + .168 * b);
            int newB = round(.272 * r + .534 * g + .131 * b);

            // check if sepia values are bigger than 255, and cap the values at 255
            if (newR > 255)
            {
                newR = 255;
            }

            if (newG > 255)
            {
                newG = 255;
            }

            if (newB > 255)
            {
                newB = 255;
            }
            image[i][j].rgbtRed = newR;
            image[i][j].rgbtGreen = newG;
            image[i][j].rgbtBlue = newB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int h = height;
    for (int i = 0; i < h; i++) // loop through rows
    {
        int w = width;
        int hw = round(w / 2); // half width
        for (int j = 0; j < hw; j++) // loop throug colums within the row
        {
            int r = image[i][j].rgbtRed; // get red value left side
            int g = image[i][j].rgbtGreen; // get green value left side
            int b = image[i][j].rgbtBlue; // get blue value left side

            // swap red value
            image[i][j].rgbtRed = image[i][w - j - 1].rgbtRed;
            image[i][w - j - 1].rgbtRed = r;

            // swap green value
            image[i][j].rgbtGreen = image[i][w - j - 1].rgbtGreen;
            image[i][w - j - 1].rgbtGreen = g;

            // swap blue value
            image[i][j].rgbtBlue = image[i][w - j - 1].rgbtBlue;
            image[i][w - j - 1].rgbtBlue = b;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int h = height;
    int w = width;
    RGBTRIPLE copyimage[height][width];
    // copy image
    for (int i = 0; i < h; i++) // loop through rows
    {
        for (int j = 0; j < w; j++) // loop throug colums within the row
        {
            copyimage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < h; i++) // loop through rows
    {
        for (int j = 0; j < w; j++) // loop throug colums within the row
        {
            float r = 0;
            float g = 0;
            float b = 0;
            int c = 0;

            for (int a = -1; a < 2; a++) // loop through neighbouring pixels
            {
                for (int s = -1; s < 2; s++)
                {
                    int x = i + a;
                    int y = j + s;

                    if (x < 0 || y < 0 || x == h || y == w) // check if neighbouring pixels are out of bounds
                    {
                        continue;
                    }

                    r += image[x][y].rgbtRed;
                    g += image[x][y].rgbtGreen;
                    b += image[x][y].rgbtBlue;
                    c++;
                }
            }

            float ravg = round(r / c);
            float gavg = round(g / c);
            float bavg = round(b / c);

            copyimage[i][j].rgbtRed = ravg;
            copyimage[i][j].rgbtGreen = gavg;
            copyimage[i][j].rgbtBlue = bavg;

        }
    }

    for (int i = 0; i < h; i++) // loop through rows
    {
        for (int j = 0; j < w; j++) // loop throug colums within the row
        {
            image[i][j] = copyimage[i][j];
        }
    }

    return;
}
