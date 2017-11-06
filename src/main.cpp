#include <iostream>
#include <SDL2/SDL.h>

#include "Canvas.hpp"
#include "Window.hpp"
#include "MouseEvent.hpp"

const char* SCREEN_TITLE  = "GilvaPaint";
const int   SCREEN_WIDTH  = 640;
const int   SCREEN_HEIGHT = 480;

int mouse_x1=0, mouse_x2=0, mouse_y1=0, mouse_y2=0;

using namespace std;

class MyEvent final : public GilvaPaint::MouseEvent {
 private:
 public:
  MyEvent() =default;
  ~MyEvent() noexcept {}
  
  void react(GilvaPaint::Window&, SDL_Event event) noexcept final {
    if(event.type == SDL_MOUSEBUTTONDOWN){
      mouse_x1 = event.button.x;
      mouse_y1 = event.button.y;
    }
    if(event.type == SDL_MOUSEMOTION){
      mouse_x2 = event.button.x;
      mouse_y2 = event.button.y;
    }
  }
};

void draw(GilvaPaint::Window& window, SDL_Surface* surface){
  window.clear();

  GilvaPaint::Canvas canvas = GilvaPaint::Canvas(SCREEN_WIDTH, SCREEN_HEIGHT);

  const int delta_x = pow(mouse_x2-mouse_x1, 2);
  const int delta_y = pow(mouse_y2-mouse_y1, 2);
  const int delta = sqrt( delta_x+delta_y );

  canvas
    .lineColor(0xff0000ff)
    //.line(mouse_x1, mouse_y1, mouse_x2, mouse_y2)
    //.circle(mouse_x1, mouse_y1, delta)
    //.ellipse(mouse_x1, mouse_y1, mouse_x2-mouse_x1, mouse_y2-mouse_y1)
    .drawOver(surface);
}

int main(int, char**){
  GilvaPaint::Window window = GilvaPaint::Window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

  MyEvent my_event;
  
  if( !window.init() ){
    return 1;
  }

  window.addEventListener(my_event);
  window.draw(draw);

  return 0;
}
