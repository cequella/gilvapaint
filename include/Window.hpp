#ifndef GILVAPAINT_WINDOW_HPP
#define GILVAPAINT_WINDOW_HPP

#include <iostream>

#include <SDL2/SDL.h>

#include "MouseListener.hpp"

namespace GilvaPaint {

  class Window {
  private:
	const char*  m_title;
	const int    m_width;
	const int    m_height;
	const Uint32 m_flags = SDL_WINDOW_SHOWN;//|SDL_WINDOW_OPENGL;;

	bool m_running = true;
	
	SDL_Window*  m_window        = nullptr;
	SDL_Surface* m_windowSurface = nullptr;

	MouseListener m_mouseListener = MouseListener(*this);
	
  public:
	Window(const char* title, unsigned int width, unsigned int height) noexcept;
	~Window() noexcept;
	
    bool init()  noexcept;
	void clear() noexcept;
	void quit()  noexcept;

	void draw(void(*func)(Window&, SDL_Surface*)) noexcept;

	// Mouse events
	Window& addEventListener(const MouseEvent& mouseEvent) noexcept;
  };
}

#endif //GILVAPAINT_WINDOW_HPP
