#ifndef GILVAPAINT_CANVAS_HPP
#define GILVAPAINT_CANVAS_HPP

#include <cstdint>

namespace Gilvapaint {
  
  class Canvas {
  private:
	unsigned int    m_dimen[2];
	unsigned short  m_bpp;
	uint8_t        *m_content;
	uint32_t        m_currentColor[2] = {0, 0};
	
	Canvas(unsigned int width, unsigned int height, unsigned short bpp) noexcept; // Default Constructor
  public:
	// --- Memory Management
	static Canvas BPP8(unsigned int width, unsigned int height)  noexcept; // 8bits  per pixel image
	static Canvas BPP24(unsigned int width, unsigned int height) noexcept; // 24bits per pixel image
	static Canvas BPP32(unsigned int width, unsigned int height) noexcept; // 32bits per pixel image
	Canvas(const Canvas& that)                                   noexcept; // Assign Constructor
	~Canvas()                                                    noexcept; // Desctructor

	
	
	// --- Operators
	Canvas&  operator = (const Canvas& that) noexcept; // Assign Operator
	

	// --- Getters
	inline unsigned int   width()             const noexcept;
	inline unsigned int   height()            const noexcept;
	inline unsigned int   size()              const noexcept;
	inline unsigned short bitsPerPixel()      const noexcept;
	inline unsigned short bytesPerPixel()     const noexcept;
	inline uint32_t       pixel(int position) const noexcept;


	
	// --- Setters
	inline Canvas& lineColor(uint32_t color)           noexcept;
	inline Canvas& fillColor(uint32_t color)           noexcept;
	inline Canvas& pixel(int position, uint32_t color) noexcept;
	


	// --- Methods
	Canvas& clear(uint32_t color) noexcept;
  };
  
}



// --- Getters
//-----------------------------------------------------------------------------
unsigned int
Gilvapaint::Canvas::width()  const noexcept { return m_dimen[0]; }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
unsigned int
Gilvapaint::Canvas::height() const noexcept { return m_dimen[1]; }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
unsigned int
Gilvapaint::Canvas::size() const noexcept { return width()*height(); }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
unsigned short
Gilvapaint::Canvas::bitsPerPixel() const noexcept {
  return m_bpp;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
unsigned short
Gilvapaint::Canvas::bytesPerPixel() const noexcept {
  return m_bpp*0.125;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint32_t
Gilvapaint::Canvas::pixel (int position) const noexcept {
  uint32_t out = 0;
  
  position = position%size();

  switch( bitsPerPixel() ){
  case 8:
	out = m_content[position];
    break;

  case 24:
	out = (m_content[position]<<2) | (m_content[position+1]<<1) | m_content[position+2];
	break;

  case 32:
	out = (m_content[position]<<3) | (m_content[position+1]<<2) | (m_content[position+2]<<1) | m_content[position+3];
	break;
  }

  return out;
}
//-----------------------------------------------------------------------------



// --- Setters
//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::lineColor(uint32_t color) noexcept {
  m_currentColor[0] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::fillColor(uint32_t color) noexcept {
  m_currentColor[1] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::pixel (int position, uint32_t color) noexcept {
  position = position%size();

  /*switch( bitsPerPixel() ){
  case 8:
	m_content[position];
    break;

  case 24:
	out = (m_content[position]<<2) | (m_content[position+1]<<1) | m_content[position+2];
	break;

  case 32:
	out = (m_content[position]<<3) | (m_content[position+1]<<2) | (m_content[position+2]<<1) | m_content[position+3];
	break;
  }*/

  return *this;
}
//-----------------------------------------------------------------------------

#endif // GILVAPAINT_CANVAS_HPP
