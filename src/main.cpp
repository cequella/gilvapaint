#include <iostream>
#include <SDL2/SDL.h>

#include "Canvas.hpp"
#include "Window.hpp"
#include "MouseEvent.hpp"

const char* SCREEN_TITLE  = "GilvaPaint";
const int   SCREEN_WIDTH  = 640;
const int   SCREEN_HEIGHT = 480;

using namespace std;

class MyEvent final : public GilvaPaint::MouseEvent {
private:
public:
  MyEvent() =default;
  ~MyEvent() noexcept {}
  
  void react(GilvaPaint::Window&, SDL_Event event) noexcept final {
	if(event.type != SDL_MOUSEBUTTONDOWN) return;
	std::cout << event.button.x << " " << event.button.y << std::endl;
  }
};

void draw(GilvaPaint::Window& window, SDL_Surface* surface){
  window.clear();

  GilvaPaint::Canvas canvas = GilvaPaint::Canvas(SCREEN_WIDTH, SCREEN_HEIGHT);

  canvas
	.lineColor(0xff0000ff)
	.horizontalLine(50, 0, 300)
	.verticalLine(50, 0, 300)
	.line(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2-50)
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
