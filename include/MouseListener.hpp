#ifndef GILVAPAINT_MOUSELISTENER_HPP
#define GILVAPAINT_MOUSELISTENER_HPP

#include <vector>

#include <SDL2/SDL.h>

#include "MouseEvent.hpp"

namespace GilvaPaint {

#ifndef GILVAPAINT_WINDOW_HPP
  class Window;
#endif
  
  class MouseListener {
  private:
	Window&                  m_window;
	std::vector<MouseEvent*> m_events;

  public:
	MouseListener(Window& window) noexcept
	  : m_window(window) {}

	MouseListener& attach(const MouseEvent& event) noexcept;
	MouseListener& detach(const MouseEvent& event) noexcept;
	void           notify(SDL_Event event)         const noexcept;
  };
  
}

#endif //GILVAPAINT_MOUSELISTENER_HPP
