#include <iostream>
#include <SDL2/SDL.h>

#include "Canvas.hpp"
#include "Window.hpp"

const char* SCREEN_TITLE  = "GilvaPaint";
const int   SCREEN_WIDTH  = 640;
const int   SCREEN_HEIGHT = 480;

using namespace std;

void draw(GilvaPaint::Window& window, SDL_Surface* surface){
  window.clear();

  GilvaPaint::Canvas canvas = GilvaPaint::Canvas(SCREEN_WIDTH, SCREEN_HEIGHT);

  canvas
	.lineColor(0xff0000ff)
	.horizontalLine(50, 0, 300)
	.verticalLine(50, 0, 300)
	.line(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2-50)
	.line(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2+50)
	.line(SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT/2-50)
	.line(SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT/2+50)
	.circle(100, 100, 50)
	.rectangle(300, 300, 100, 150)
	.ellipse(0, 200, 200, 100)
	.drawOver(surface);
}

int main(int, char**){
  GilvaPaint::Window window = GilvaPaint::Window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

  if( !window.init() ){
	return 1;
  }
  window.draw(draw);

  return 0;
}
