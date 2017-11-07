#include "Window.hpp"

//--------------------------------------------------------------------
GilvaPaint::Window::Window(const char* title, unsigned int width, unsigned int height) noexcept
  : m_title(title),
	m_width( static_cast<int>(width) ),
	m_height( static_cast<int>(height) ){}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
GilvaPaint::Window::~Window() noexcept {
  SDL_FreeSurface(m_windowSurface);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
bool
GilvaPaint::Window::init() noexcept {
  if( SDL_Init(SDL_INIT_VIDEO)<0 ){
	std::cerr << SDL_GetError() << std::endl;
	return false;
  }

  m_window = SDL_CreateWindow(m_title,
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  m_width, m_height,
							  m_flags);
  if( m_window==NULL ){
	std::cerr << SDL_GetError() << std::endl;
	return false;
  }
  m_windowSurface = SDL_GetWindowSurface( m_window );

  return true;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GilvaPaint::Window::clear() noexcept {
  SDL_FillRect( m_windowSurface, NULL, SDL_MapRGB(m_windowSurface->format, 0, 0, 0) );
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GilvaPaint::Window::draw(void(*func)(Window&, SDL_Surface*, SDL_Event)) noexcept {
  while(m_running){
	
	SDL_Event e;
	while( SDL_PollEvent(&e) not_eq 0 ){
	  if( e.type == SDL_QUIT ) quit();
	  
	  if(e.type == SDL_KEYDOWN){
		if(e.key.keysym.sym == SDLK_ESCAPE) quit();
	  }

	  func(*this, m_windowSurface, e);
	  SDL_UpdateWindowSurface(m_window);
	}
	
  }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void
GilvaPaint::Window::quit() noexcept {
  m_running = false;
}
//--------------------------------------------------------------------
