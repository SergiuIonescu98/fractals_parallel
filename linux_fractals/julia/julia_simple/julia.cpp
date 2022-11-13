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
  screen(wArg, hArg, 0, "Julia Set"); //make larger to see more detail!
  // //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
  
  double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
  double zoom = 1, moveX = 0, moveY = 0; //you can change these to zoom and change position

  // //pick some values for the constant c, this determines the shape of the Julia Set
  cRe = -0.7;
  cIm = 0.27015;

  julia_math(hArg, wArg, zoom, moveX, moveY, cRe, cIm, maxIterArg);


  //make the Julia Set visible and wait to exit
  redraw();
  sleep();
  return 0;
}