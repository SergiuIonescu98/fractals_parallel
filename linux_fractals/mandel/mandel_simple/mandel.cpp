#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include <SDL/SDL.h>
#include "quickcg.h"
using namespace QuickCG;
using namespace std;

#include "fractal_math.h"

static int wArg = 400;
static int hArg = 300;
static int maxIterArg = 300; //after how much iterations the function should stop


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
  screen(wArg, hArg, 0, "Mandelbrot Set");

  double zoom = 1, moveX = -0.5, moveY = 0; //you can change these to zoom and change position

  mandel_math(hArg,wArg,zoom, moveX, moveY, maxIterArg);

  //make the Mandelbrot Set visible and wait to exit
  redraw();
  sleep();
  return 0;
}