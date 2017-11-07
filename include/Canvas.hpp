#ifndef GILVAPAINT_CANVAS_HPP
#define GILVAPAINT_CANVAS_HPP

#include <algorithm>
#include <vector>

#include <SDL2/SDL.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#else
#define RMASK 0x000000ff
#define GMASK 0x0000ff00
#define BMASK 0x00ff0000
#define AMASK 0xff000000
#endif

namespace GilvaPaint {
  class Canvas {
  private:
    int          m_dimen[2];
    SDL_Surface* m_content         = nullptr;
    Uint32       m_currentColor[2] = {0, 0};
	
    // --- Helpers
    int correctPosition(int position)      const noexcept;
    int clamp(int value, int MAX, int MIN) const noexcept;
	
    // --- Unsafe Operations
    Canvas& setPixel(int position, Uint32 color) noexcept;
    Canvas& setPixel(int x, int y, Uint32 color) noexcept;
	
  public:
    // --- Memory Management
    Canvas(unsigned int width, unsigned int height) noexcept; // Default Constructor
    Canvas(const Canvas& that)                      noexcept; // Assign Constructor
    ~Canvas()                                       noexcept; // Destructor

	
	
    // --- Operators
    Canvas& operator = (const Canvas& that) noexcept; // Assign Operator
	

    // --- Getters
    inline int    width()             const noexcept;
    inline int    height()            const noexcept;
    inline int    size()              const noexcept;
    inline Uint32 pixel(int position) const noexcept;
    inline Uint32 pixel(int x, int y) const noexcept;
    inline Uint32 lineColor()         const noexcept;
    inline Uint32 fillColor()         const noexcept;



    // --- Setters
    inline Canvas& lineColor(Uint32 color)           noexcept;
    inline Canvas& fillColor(Uint32 color)           noexcept;
    inline Canvas& pixel(int position, Uint32 color) noexcept;
    inline Canvas& pixel(int x, int y, Uint32 color) noexcept;
	


    // --- Methods
    Canvas& clear(Uint32 color)                            noexcept;
    Canvas& horizontalLine(int y, int xStart, int xEnd)    noexcept;
    Canvas& verticalLine(int x, int yStart, int yEnd)      noexcept;
    Canvas& rectangle(int x, int y, int width, int height) noexcept;
    Canvas& line(int x1, int y1, int x2, int y2)           noexcept;
    Canvas& circle(int x, int y, int r)                    noexcept;
    Canvas& ellipse(int x, int y, int rh, int rv)          noexcept;
    Canvas& polygon(std::vector<int> coord)                noexcept;
    void    drawOver(SDL_Surface* surface)                 const noexcept;
  };
  
}



// --- Getters
//-----------------------------------------------------------------------------
int
GilvaPaint::Canvas::width()  const noexcept { return m_dimen[0]; }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int
GilvaPaint::Canvas::height() const noexcept { return m_dimen[1]; }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int
GilvaPaint::Canvas::size() const noexcept { return width()*height(); }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Uint32
GilvaPaint::Canvas::pixel (int position) const noexcept {
  position = correctPosition(position);
  Uint32* temp = (Uint32*)m_content->pixels;
  return temp[position];
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Uint32
GilvaPaint::Canvas::pixel (int x, int y) const noexcept { return pixel(x+ y*width()); }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Uint32
GilvaPaint::Canvas::lineColor() const noexcept { return m_currentColor[0]; }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Uint32
GilvaPaint::Canvas::fillColor() const noexcept { return m_currentColor[1]; }
//-----------------------------------------------------------------------------


// --- Setters
//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::lineColor(Uint32 color) noexcept {
  m_currentColor[0] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::fillColor(Uint32 color) noexcept {
  m_currentColor[1] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::pixel (int position, Uint32 color) noexcept {
  if(position < 0 or position>width()*height()) return *this; // Clipping
  Uint32* temp = (Uint32*)m_content->pixels;
  temp[position] = color;

  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::pixel (int x, int y, Uint32 color) noexcept {
  if(x<0 or x>=width() or y<0 or y>=height()) return *this; // Clipping

  int position = x+y*width();
  Uint32* temp = (Uint32*)m_content->pixels;
  temp[position] = color;

  return *this;
}
//-----------------------------------------------------------------------------

#endif // GILVAPAINT_CANVAS_HPP
