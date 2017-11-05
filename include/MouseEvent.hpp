#ifndef GILVAPAINT_MOUSEEVENT_HPP
#define GILVAPAINT_MOUSEEVENT_HPP

#include <SDL2/SDL.h>

namespace GilvaPaint {

  class Window;
  
  class MouseEvent {
  private:
  public:
	MouseEvent() =default;
	~MouseEvent() noexcept {}

	virtual void react(Window& window, SDL_Event event) noexcept =0;
  };

}

#endif //GILVAPAINT_MOUSEEVENT_HPP
