#include <cmath>
#include <string>
#include <vector>
#include <iostream>

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

  //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
  double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
  double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
  double zoom = 1, moveX = 0, moveY = 0; //you can change these to zoom and change position
  int maxIterations = maxIterArg;//after how much iterations the function should stop
  int w = wArg;
  int h = hArg;

  //pick some values for the constant c, this determines the shape of the Julia Set
  cRe = -0.7;
  cIm = 0.27015;

  //loop through every pixel
  for(int y = 0; y < h; y++)
  for(int x = 0; x < w; x++)
  {
    //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
    newRe = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
    newIm = (y - h / 2) / (0.5 * zoom * h) + moveY;
    //i will represent the number of iterations
    int i;
    //start the iteration process
    for(i = 0; i < maxIterations; i++)
    {
      //remember value of previous iteration
      oldRe = newRe;
      oldIm = newIm;
      //the actual iteration, the real and imaginary part are calculated
      newRe = oldRe * oldRe - oldIm * oldIm + cRe;
      newIm = 2 * oldRe * oldIm + cIm;
      //if the point is outside the circle with radius 2: stop
      if((newRe * newRe + newIm * newIm) > 4) break;
    }
  }
  return 0;
}