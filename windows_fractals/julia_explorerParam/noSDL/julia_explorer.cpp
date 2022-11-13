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
  double cRe, cIm;           //real and imaginary part of the constant c, determines shape of the Julia Set
  double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
  double zoom=1, moveX=0, moveY=0; //you can change these to zoom and change position
  ColorRGBA color; //the RGB color value for the pixel
  int maxIterations = maxIterArg;//after how much iterations the function should stop
  int w = wArg;
  int h = hArg;

  double time, oldTime, frameTime; //current and old time, and their difference (for input)
  int showText=0;

  //pick some values for the constant c, this determines the shape of the Julia Set
  cRe = -0.7;
  cIm = 0.27015;

  //begin the program loop
  while(!done())
  {
    //draw the fractal
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
      //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
      color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations), 255));
      //draw the pixel
      pset(x, y, color);
    }

    //print the values of all variables on screen if that option is enabled
    if(showText <= 1)
    {
      print("X:", 1, 1, RGB_White, 1); print(moveX, 17, 1, RGB_White, 1);
      print("Y:", 1, 9, RGB_White, 1); print(moveY, 17, 9, RGB_White, 1);
      print("Z:", 1, 17, RGB_White, 1); print(zoom, 17, 17, RGB_White, 1);
      print("R:", 1, 25, RGB_White, 1); print(cRe, 17, 25, RGB_White, 1);
      print("I:", 1, 33, RGB_White, 1); print(cIm, 17, 33, RGB_White, 1);
      print("N:", 1, 41, RGB_White, 1); print(maxIterations, 17, 41, RGB_White, 1);
    }
    //print the help text on screen if that option is enabled
    if(showText == 0)
    {
      print("Arrows move (X,Y), q,e zooms (Z)", 1, h - 33, RGB_White, 1);
      print("w a s d change shape (R,I)     ", 1, h - 25, RGB_White, 1);
      print("Keypad z,x changes iterations (N)    ", 1, h - 17, RGB_White, 1);
      print("a to z=presets (qwerty), F1=cycle texts", 1, h - 9, RGB_White, 1);
    }
    redraw();

    //get the time and old time for time dependent input
    oldTime = time;
    time = getTicks();
    frameTime = time - oldTime;
    readKeys();
    //ZOOM keys
    if(keyDown(SDLK_q))  {zoom *= pow(1.001, frameTime);}
    if(keyDown(SDLK_e)) {zoom /= pow(1.001, frameTime);}
    //MOVE keys
    if(keyDown(SDLK_DOWN))  {moveY += 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_UP))  {moveY -= 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_RIGHT)) {moveX += 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_LEFT))  {moveX -= 0.0003 * frameTime / zoom;}
    //CHANGE SHAPE keys
    if(keyDown(SDLK_s)) {cIm += 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_w)) {cIm -= 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_d)) {cRe += 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_a)) {cRe -= 0.0002 * frameTime / zoom;}
    //keys to change number of iterations
    if(keyPressed(SDLK_z)) {maxIterations *= 2;}
    if(keyPressed(SDLK_x))   {if(maxIterations > 2) maxIterations /= 2;}
    //key to change the text options
    if(keyPressed(SDLK_F1)) {showText++; showText %= 3;}
  }
  return 0;
}