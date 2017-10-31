#include <iostream>
#include <SDL2/SDL.h>

#include "Canvas.hpp"

const char*  SCREEN_TITLE  = "GilvaPaint";
const int    SCREEN_WIDTH  = 640;
const int    SCREEN_HEIGHT = 480;
const Uint32 SCREEN_FLAGS  = SDL_WINDOW_SHOWN;//|SDL_WINDOW_OPENGL;

int startSDL();

using namespace std;
int main(int, char**){

  GilvaPaint::Canvas canvas = GilvaPaint::Canvas(16, 16);

  cout << endl << endl;
  
  canvas
    .clear(' ')
    .lineColor('0')
    //.line(0, 0, 15, 10) //Primeiro octante
    //.line(0, 0, 10, 15) //Segundo octante
    .line(0, 15, 10, 0)
    .draw();

  cout << endl << endl;
  
  return 0;
  //return startSDL();
}











int startSDL(){
  SDL_Window*  window        = nullptr;
  SDL_Surface* windowSurface = nullptr;

  if( SDL_Init(SDL_INIT_VIDEO)<0 ){
    cerr << SDL_GetError() << endl;
    return 1;
  }

  window = SDL_CreateWindow(SCREEN_TITLE,
			    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SCREEN_FLAGS);
  if( window==NULL ){
    cerr << SDL_GetError() << endl;
    return 1;
  }
  windowSurface = SDL_GetWindowSurface( window );

  // ------------------------------

  SDL_FillRect( windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0, 0, 0) );
  SDL_UpdateWindowSurface(window);

  SDL_Delay(500);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
