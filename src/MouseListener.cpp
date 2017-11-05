#include "MouseListener.hpp"

//------------------------------------------------------------------------
GilvaPaint::MouseListener&
GilvaPaint::MouseListener::attach(const MouseEvent& event) noexcept {
  m_events.push_back( const_cast<MouseEvent*>(&event) );
  return *this;
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
GilvaPaint::MouseListener&
GilvaPaint::MouseListener::detach(const MouseEvent& event) noexcept {
  for(auto it=m_events.begin(); it not_eq m_events.end(); ++it){
	if(*it == &event) m_events.erase(it);
  }

  return *this;
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void
GilvaPaint::MouseListener::notify(SDL_Event event) const noexcept {
  for(auto it=m_events.begin(); it not_eq m_events.end(); ++it){
	(*it)->react(m_window, event);
  }
}
//------------------------------------------------------------------------
