#ifndef GILVAPAINT_CANVAS_HPP
#define GILVAPAINT_CANVAS_HPP

#include <cstdint>
#include <cstring>
#include <iostream> // --- Temp
#include <algorithm>

namespace GilvaPaint {

  enum class BPP : short {MONOCHROME=1, RGB=3, ARGB=4};
  
  class Canvas {
  private:
    int      m_dimen[2];
    BPP      m_bpp;
    uint8_t *m_content;
    uint8_t  m_currentColor[2] = {0, 0};
	
    Canvas(unsigned int width, unsigned int height, BPP canvasBPP) noexcept; // Default Constructor

    // --- Helpers
    int correctPosition(int position)      const noexcept;
    int clamp(int value, int MAX, int MIN) const noexcept;
	
    // --- Unsafe Operations
    Canvas& setPixel(int position, uint8_t color) noexcept;
    Canvas& setPixel(int x, int y, uint8_t color) noexcept;
	
  public:
    // --- Memory Management
    Canvas(unsigned int width, unsigned int height)              noexcept; // Default Constructor
    Canvas(const Canvas& that)                                   noexcept; // Assign Constructor
    ~Canvas()                                                    noexcept; // Destructor

	
	
    // --- Operators
    Canvas& operator = (const Canvas& that) noexcept; // Assign Operator
	

    // --- Getters
    inline int     width()             const noexcept;
    inline int     height()            const noexcept;
    inline int     size()              const noexcept;
    inline short   bytesPerPixel()     const noexcept;
    inline uint8_t pixel(int position) const noexcept;
    inline uint8_t pixel(int x, int y) const noexcept;
    inline uint8_t lineColor()         const noexcept;
    inline uint8_t fillColor()         const noexcept;



    // --- Setters
    inline Canvas& lineColor(uint8_t color)           noexcept;
    inline Canvas& fillColor(uint8_t color)           noexcept;
    inline Canvas& pixel(int position, uint8_t color) noexcept;
    inline Canvas& pixel(int x, int y, uint8_t color) noexcept;
	


    // --- Methods
    Canvas& clear(uint8_t color)                           noexcept;
    Canvas& horizontalLine(int y, int xStart, int xEnd)    noexcept;
    Canvas& verticalLine(int x, int yStart, int yEnd)      noexcept;
    Canvas& rectangle(int x, int y, int width, int height) noexcept;
    Canvas& line(int x1, int y1, int x2, int y2)           noexcept;
    Canvas& circle(int x, int y, int r)                    noexcept;
    void    draw()                                         const noexcept;
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
short
GilvaPaint::Canvas::bytesPerPixel() const noexcept { return static_cast<short>(m_bpp); }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t
GilvaPaint::Canvas::pixel (int position) const noexcept {
  position = correctPosition(position);
  return m_content[position];
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t
GilvaPaint::Canvas::pixel (int x, int y) const noexcept { return pixel(x+ y*width()); }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t
GilvaPaint::Canvas::lineColor() const noexcept { return m_currentColor[0]; }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint8_t
GilvaPaint::Canvas::fillColor() const noexcept { return m_currentColor[1]; }
//-----------------------------------------------------------------------------


// --- Setters
//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::lineColor(uint8_t color) noexcept {
  m_currentColor[0] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::fillColor(uint8_t color) noexcept {
  m_currentColor[1] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::pixel (int position, uint8_t color) noexcept {
  position = static_cast<int>( correctPosition(position) );

  m_content[position] = color;

  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::pixel (int x, int y, uint8_t color) noexcept {
  int position = x*width()+y;
  position = static_cast<int>( correctPosition(position) );

  m_content[position] = color;

  return *this;
}
//-----------------------------------------------------------------------------

#endif // GILVAPAINT_CANVAS_HPP
