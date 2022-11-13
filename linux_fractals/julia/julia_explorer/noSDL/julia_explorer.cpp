#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;
using namespace std;

#include "fractal_math.h"

int main(int argc, char *argv[])
{
  screen(320, 240, 0, "Julia  Explorer");

  //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
  double cRe, cIm;           //real and imaginary part of the constant c, determines shape of the Julia Set
  double zoom=1, moveX=0, moveY=0; //you can change these to zoom and change position
  int maxIterations=128; //after how much iterations the function should stop

  double time, oldTime, frameTime; //current and old time, and their difference (for input)
  int showText=0;

  //pick some values for the constant c, this determines the shape of the Julia Set
  cRe = -0.7;
  cIm = 0.27015;

  //begin the program loop
  while(!done())
  {
    //draw the fractal
    julia_math(h, w, zoom, moveX, moveY, cRe, cIm, maxIterations);

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
}