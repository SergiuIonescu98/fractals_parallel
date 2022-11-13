#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;
using namespace std;

static int wArg = 400;
static int hArg = 300;
static int maxIterArg = 300;

static void getargs(int argc, char *argv[]);                  /* gets command-line args */

static void getargs(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage:   %s <w> <h> <max_iterations>\n", argv[0]);
        printf("Example: %s 400 300 3000\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* The window in the plane. */
    wArg = atof(argv[1]);
    hArg = atof(argv[2]);
    maxIterArg = atof(argv[3]);
}

int main(int argc, char *argv[])
{
    getargs(argc, argv);

    screen(wArg, hArg, 0, "Mandelbrot Set"); //make larger to see more detail!

    ColorRGBA color; //the RGB color value for the pixel

    //each iteration, it calculates: newz = oldz*oldz + p, where p is the current pixel, and oldz stars at the origin
    double pr, pi;           //real and imaginary part of the pixel p
    double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
    double zoom = 1, moveX = -0.5, moveY = 0; //you can change these to zoom and change position
    int maxIterations = maxIterArg;//after how much iterations the function should stop
    int w = wArg;
    int h = hArg;

    //loop through every pixel
    for(int y = 0; y < h; y++)
        for(int x = 0; x < w; x++)
        {
            //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
            pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
            pi = (y - h / 2) / (0.5 * zoom * h) + moveY;
            newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
            //"i" will represent the number of iterations
            int i;
            //start the iteration process
            for(i = 0; i < maxIterations; i++)
            {
                //remember value of previous iteration
                oldRe = newRe;
                oldIm = newIm;
                //the actual iteration, the real and imaginary part are calculated
                newRe = oldRe * oldRe - oldIm * oldIm + pr;
                newIm = 2 * oldRe * oldIm + pi;
                //if the point is outside the circle with radius 2: stop
                if((newRe * newRe + newIm * newIm) > 4) break;
            }
            //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
            color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations), 255));
            //draw the pixel
            pset(x, y, color);
        }
    //make the Mandelbrot Set visible and wait to exit
        redraw();
        sleep();


    return 0;
}