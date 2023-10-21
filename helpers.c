#include "helpers.h"
#include <stdio.h>
#include <math.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            int avg = round((float)(image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}



// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width/2; j++)
        {
            RGBTRIPLE temp = image[i][width-j-1];
            image[i][width-j-1] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}




// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE source[height][width];

    for (int i=0; i<height; i++)
    {
        for (int j=0; j<height; j++)
        {
            source[i][j] = image[i][j];
        }
    }

    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            // Marco de arriba con esquinas
            if (i==0)
            {
                // Esquina izquierda
                if (j==0)
                {
                    image[i][j].rgbtRed = round((float)(source[i][j].rgbtRed + source[i][j+1].rgbtRed + source[i+1][j].rgbtRed + source[i+1][j+1].rgbtRed)/4);
                    image[i][j].rgbtGreen = round((float)(source[i][j].rgbtGreen + source[i][j+1].rgbtGreen + source[i+1][j].rgbtGreen + source[i+1][j+1].rgbtGreen)/4);
                    image[i][j].rgbtBlue = round((float)(source[i][j].rgbtBlue + source[i][j+1].rgbtBlue + source[i+1][j].rgbtBlue + source[i+1][j+1].rgbtBlue)/4);
                    continue;
                }
                // Esquina derecha
                else if (j==width-1)
                {
                    image[i][j].rgbtRed = round((float)(source[i][j].rgbtRed + source[i][j-1].rgbtRed + source[i+1][j].rgbtRed + source[i+1][j-1].rgbtRed)/4);
                    image[i][j].rgbtGreen = round((float)(source[i][j].rgbtGreen + source[i][j-1].rgbtGreen + source[i+1][j].rgbtGreen + source[i+1][j-1].rgbtGreen)/4);
                    image[i][j].rgbtBlue = round((float)(source[i][j].rgbtBlue + source[i][j-1].rgbtBlue + source[i+1][j].rgbtBlue + source[i+1][j-1].rgbtBlue)/4);
                    continue;
                }
                // Solo marco de arriba
                else
                {
                    image[i][j].rgbtRed = round((float)(source[i][j-1].rgbtRed + source[i][j].rgbtRed + source[i][j+1].rgbtRed + source[i+1][j-1].rgbtRed + source[i+1][j].rgbtRed + source[i+1][j+1].rgbtRed)/6);
                    image[i][j].rgbtGreen = round((float)(source[i][j-1].rgbtGreen + source[i][j].rgbtGreen + source[i][j+1].rgbtGreen + source[i+1][j-1].rgbtGreen + source[i+1][j].rgbtGreen + source[i+1][j+1].rgbtGreen)/6);
                    image[i][j].rgbtBlue = round((float)(source[i][j-1].rgbtBlue + source[i][j].rgbtBlue + source[i][j+1].rgbtBlue + source[i+1][j-1].rgbtBlue + source[i+1][j].rgbtBlue + source[i+1][j+1].rgbtBlue)/6);
                    continue;
                }
            }

            // Marco de Abajo con esquinas
            else if (i==height-1)
            {
                // Esquina izquierda
                if (j==0)
                {
                    image[i][j].rgbtRed = round((float)(source[i][j].rgbtRed + source[i][j+1].rgbtRed + source[i-1][j].rgbtRed + source[i-1][j+1].rgbtRed)/4);
                    image[i][j].rgbtGreen = round((float)(source[i][j].rgbtGreen + source[i][j+1].rgbtGreen + source[i-1][j].rgbtGreen + source[i-1][j+1].rgbtGreen)/4);
                    image[i][j].rgbtBlue = round((float)(source[i][j].rgbtBlue + source[i][j+1].rgbtBlue + source[i-1][j].rgbtBlue + source[i-1][j+1].rgbtBlue)/4);
                    continue;
                }
                // Esquina derecha
                else if (j==width-1)
                {
                    image[i][j].rgbtRed = round((float)(source[i][j].rgbtRed + source[i][j-1].rgbtRed + source[i-1][j].rgbtRed + source[i-1][j-1].rgbtRed)/4);
                    image[i][j].rgbtGreen = round((float)(source[i][j].rgbtGreen + source[i][j-1].rgbtGreen + source[i-1][j].rgbtGreen + source[i-1][j-1].rgbtGreen)/4);
                    image[i][j].rgbtBlue = round((float)(source[i][j].rgbtBlue + source[i][j-1].rgbtBlue + source[i-1][j].rgbtBlue + source[i-1][j-1].rgbtBlue)/4);
                    continue;
                }
                // solo marco de abajo
                 else
                {
                    image[i][j].rgbtRed = round((float)(source[i][j-1].rgbtRed + source[i][j].rgbtRed + source[i][j+1].rgbtRed + source[i-1][j-1].rgbtRed + source[i-1][j].rgbtRed + source[i-1][j+1].rgbtRed)/6);
                    image[i][j].rgbtGreen = round((float)(source[i][j-1].rgbtGreen + source[i][j].rgbtGreen + source[i][j+1].rgbtGreen + source[i-1][j-1].rgbtGreen + source[i-1][j].rgbtGreen + source[i-1][j+1].rgbtGreen)/6);
                    image[i][j].rgbtBlue = round((float)(source[i][j-1].rgbtBlue + source[i][j].rgbtBlue + source[i][j+1].rgbtBlue + source[i-1][j-1].rgbtBlue + source[i-1][j].rgbtBlue + source[i-1][j+1].rgbtBlue)/6);
                    continue;
                }
            }

            //Centro y bordes
            else
            {
                // Borde derecho
                if (j==0)
                {
                    image[i][j].rgbtRed = round((float)(source[i-1][j].rgbtRed + source[i-1][j+1].rgbtRed + source[i][j].rgbtRed + source[i][j+1].rgbtRed + source[i+1][j].rgbtRed + source[i+1][j+1].rgbtRed)/6);
                    image[i][j].rgbtGreen = round((float)(source[i-1][j].rgbtGreen + source[i-1][j+1].rgbtGreen + source[i][j].rgbtGreen + source[i][j+1].rgbtGreen + source[i+1][j].rgbtGreen + source[i+1][j+1].rgbtGreen)/6);
                    image[i][j].rgbtBlue = round((float)(source[i-1][j].rgbtBlue + source[i-1][j+1].rgbtBlue + source[i][j].rgbtBlue + source[i][j+1].rgbtBlue + source[i+1][j].rgbtBlue + source[i+1][j+1].rgbtBlue)/6);
                }

                // Borde izquierdo
                else if (j==width-1)
                {
                    image[i][j].rgbtRed = round((float)(source[i-1][j-1].rgbtRed + source[i-1][j].rgbtRed + source[i][j-1].rgbtRed + source[i][j].rgbtRed + source[i+1][j-1].rgbtRed + source[i+1][j].rgbtRed)/6);
                    image[i][j].rgbtGreen = round((float)(source[i-1][j-1].rgbtGreen + source[i-1][j].rgbtGreen + source[i][j-1].rgbtGreen + source[i][j].rgbtGreen + source[i+1][j-1].rgbtGreen + source[i+1][j].rgbtGreen)/6);
                    image[i][j].rgbtBlue = round((float)(source[i-1][j-1].rgbtBlue + source[i-1][j].rgbtBlue + source[i][j-1].rgbtBlue + source[i][j].rgbtBlue + source[i+1][j-1].rgbtBlue + source[i+1][j].rgbtBlue)/6);
                }

                // Todo lo del centro
                else
                {
                    image[i][j].rgbtRed = round((float)(source[i-1][j-1].rgbtRed + source[i-1][j].rgbtRed + source[i-1][j+1].rgbtRed + source[i][j-1].rgbtRed + source[i][j].rgbtRed + source[i][j+1].rgbtRed + source[i+1][j-1].rgbtRed + source[i+1][j].rgbtRed + source[i+1][j+1].rgbtRed)/9);
                    image[i][j].rgbtGreen = round((float)(source[i-1][j-1].rgbtGreen + source[i-1][j].rgbtGreen + source[i-1][j+1].rgbtGreen + source[i][j-1].rgbtGreen + source[i][j].rgbtGreen + source[i][j+1].rgbtGreen + source[i+1][j-1].rgbtGreen + source[i+1][j].rgbtGreen + source[i+1][j+1].rgbtGreen)/9);
                    image[i][j].rgbtBlue = round((float)(source[i-1][j-1].rgbtBlue + source[i-1][j].rgbtBlue + source[i-1][j+1].rgbtBlue + source[i][j-1].rgbtBlue + source[i][j].rgbtBlue + source[i][j+1].rgbtBlue + source[i+1][j-1].rgbtBlue + source[i+1][j].rgbtBlue + source[i+1][j+1].rgbtBlue)/9);
                }
            }
        }
    }
    return;
}


// For the edges function
int gxy(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9)
{
    int gx = (-1*p1 +p3 -2*p4 +2*p6 -1*p7 + p9);
    int gy = (-1*p1 -2*p2 -1+p3 +p7 +2*p8 + p9);
    int new_channel = sqrt((gx*gx) + (gy*gy));

    if (new_channel > 255)
    {
        return 255;
    }

    return new_channel;
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // printf("Control: %i\n", gxy(image[-1][-1].rgbtRed,200,300,400,500,600,700,800,900));
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {

            int red[9];
            int green[9];
            int blue[9];
            int iter = 0;

            // inicializando el array de los index con los respectivos índices
            for (int k=-1; k<2; k++)
            {
                for (int l=-1; l<2; l++)
                {
                    red[iter] = image[k][l].rgbtRed;
                    green[iter] = image[k][l].rgbtGreen;
                    blue[iter] = image[k][l].rgbtBlue;
                    iter++;
                }
            }

            // Columna de hasta arriba
            if (i == 0)
            {
                red[0] = 0;
                red[1] = 0;
                red[2] = 0;

                green[0] = 0;
                green[1] = 0;
                green[2] = 0;

                blue[0] = 0;
                blue[1] = 0;
                blue[2] = 0;
            }

            // Columna de hasta abajo
            else if (i == height-1)
            {
                red[6] = 0;
                red[7] = 0;
                red[8] = 0;

                green[6] = 0;
                green[7] = 0;
                green[8] = 0;

                blue[6] = 0;
                blue[7] = 0;
                blue[8] = 0;
            }

            // Bordes
            if (j == 0)
            {
                red[3] = 0;
                red[6] = 0;

                green[3] = 0;
                green[6] = 0;

                blue[3] = 0;
                blue[6] = 0;
            }

            else if (j == width-1)
            {
                red[5] = 0;
                red[8] = 0;

                green[5] = 0;
                green[8] = 0;

                blue[5] = 0;
                blue[8] = 0;
            }


            image[i][j].rgbtRed = gxy(red[0], red[1], red[2], red[3], red[4], red[5], red[6], red[7], red[8]);
            image[i][j].rgbtGreen = gxy(green[0], green[1], green[2], green[3], green[4], green[5], green[6], green[7], green[8]);
            image[i][j].rgbtBlue = gxy(blue[0], blue[1], blue[2], blue[3], blue[4], blue[5], blue[6], blue[7], blue[8]);



            /*
            image[i][j].rgbtRed = (image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed);
            image[i][j].rgbtGreen = (image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen);
            image[i][j].rgbtBlue = (image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue);
            */
        }
    }
    return;
}
