#include <iostream>

#include <SDL2/SDL.h>

#include "Canvas.hpp"
#include "Window.hpp"
#include "MouseEvent.hpp"

const char* SCREEN_TITLE  = "GilvaPaint";
const int   SCREEN_WIDTH  = 640;
const int   SCREEN_HEIGHT = 480;

int mouse_x1=320, mouse_y1=240, mouse_x2=0, mouse_y2=0;
int tool = 1;
bool mousePressed = false;
std::vector<int> polygon = {0, 0};

using namespace std;

void setValues(SDL_Event event){
  switch(event.type){
  case SDL_MOUSEBUTTONDOWN:
    if(mousePressed) return; //break;
    mousePressed = true;
    mouse_x1 = event.button.x;
    mouse_y1 = event.button.y;

    if(tool==7){
      polygon.push_back(mouse_x1);
      polygon.push_back(mouse_y1);
    }
    
    break;
    
  case SDL_MOUSEBUTTONUP:
    mousePressed = false;
    break;
    
  case SDL_MOUSEMOTION:
    mouse_x2 = event.button.x;
    mouse_y2 = event.button.y;

    if(tool==7){
      polygon.at(polygon.size()-2) = mouse_x2;
      polygon.at(polygon.size()-1) = mouse_y2;
    }

    break;
    
  case SDL_KEYDOWN:
    switch(event.key.keysym.sym){
    case SDLK_1:
      tool = 1;
      break;
    case SDLK_2:
      tool = 2;
      break;
    case SDLK_3:
      tool = 3;
      break;
    case SDLK_4:
      tool = 4;
      break;
    case SDLK_5:
      tool = 5;
      break;
    case SDLK_6:
      tool = 6;
      break;
    case SDLK_7:
      tool = 7;
      break;
    }
  }
}
void draw(GilvaPaint::Window& window, SDL_Surface* surface, SDL_Event e){
  window.clear();

  if(not polygon.empty() and tool not_eq 7) {
    polygon.clear();
    polygon.push_back(0.0); polygon.push_back(0.0);
  }
  setValues(e);
  
  GilvaPaint::Canvas canvas = GilvaPaint::Canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
  canvas.lineColor(0xff0000ff);

  switch(tool){
  case 1: // horizontal line
    canvas.horizontalLine(mouse_y1, mouse_x1, mouse_x2);
    break;
  case 2: // vertical line
    canvas.verticalLine(mouse_x1, mouse_y1, mouse_y2);
    break;
  case 3: // line
    canvas.line(mouse_x1, mouse_y1, mouse_x2, mouse_y2);
    break;
  case 4: // square
    canvas.rectangle(mouse_x1, mouse_y1, mouse_x2-mouse_x1, mouse_y2-mouse_y1);
    break;
  case 5: // circle
    canvas.circle(mouse_x1, mouse_y1, sqrt( pow(mouse_x2-mouse_x1, 2) + pow(mouse_y2-mouse_y1, 2) ));
    break;
  case 6: // ellipse
    canvas.ellipse(mouse_x1, mouse_y1, mouse_x2-mouse_x1, mouse_y2-mouse_y1);
    break;
  case 7: // polygon
    canvas.polygon(polygon);
    break;
  }
  
  canvas.drawOver(surface);
}

int main(int, char**){
  GilvaPaint::Window window = GilvaPaint::Window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
  
  if( !window.init() ){
    return 1;
  }

  window.draw(draw);

  return 0;
}
