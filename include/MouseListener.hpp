#ifndef GILVAPAINT_MOUSELISTENER_HPP
#define GILVAPAINT_MOUSELISTENER_HPP

#include <vector>

#include <SDL2/SDL.h>

#include "MouseEvent.hpp"

namespace GilvaPaint {

  class MouseListener {
  private:
	std::vector<MouseEvent*> m_events;

  public:
	MouseListener() =default;

	MouseListener& attach(const MouseEvent& event) noexcept;
	MouseListener& detach(const MouseEvent& event) noexcept;
	void           notify(SDL_Event event)         const noexcept;
  };
  
}

GilvaPaint::MouseListener&
GilvaPaint::MouseListener::attach(const MouseEvent& event) noexcept {
  m_events.push_back( const_cast<MouseEvent*>(&event) );
  return *this;
}

GilvaPaint::MouseListener&
GilvaPaint::MouseListener::detach(const MouseEvent& event) noexcept {
  for(auto it=m_events.begin(); it not_eq m_events.end(); ++it){
	if(*it == &event) m_events.erase(it);
  }

  return *this;
}

void
GilvaPaint::MouseListener::notify(SDL_Event event) const noexcept {
  auto it=m_events.begin();
  
  switch(event.type){
  case SDL_MOUSEMOTION:
	for(; it not_eq m_events.end(); ++it){
	  (*it)->onMove(event.motion.timestamp,
					event.motion.x, event.motion.y,
					event.motion.xrel, event.motion.yrel);
	}
	break;

  case SDL_MOUSEBUTTONDOWN:
	for(; it not_eq m_events.end(); ++it){
	  (*it)->onButtonDown(event.button.timestamp,
						  event.button.x, event.button.y,
						  event.button.button);
	}	
	break;

  case SDL_MOUSEBUTTONUP:
	for(; it not_eq m_events.end(); ++it){
	  (*it)->onButtonUp(event.button.timestamp,
						event.button.x, event.button.y,
						event.button.button);
	}
	break;
	
  case SDL_MOUSEWHEEL:
	for(; it not_eq m_events.end(); ++it){
	  (*it)->onWheel(event.wheel.timestamp,
					 event.wheel.y);
	}
	break;
  }
}

#endif //GILVAPAINT_MOUSELISTENER_HPP
