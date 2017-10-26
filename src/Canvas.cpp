#include "Canvas.hpp"



// --- Memory Management
//-----------------------------------------------------------------------------
Gilvapaint::Canvas::Canvas(unsigned int width, unsigned int height, unsigned short bpp) noexcept
  : m_dimen{width, height},
	m_bpp(bpp),
	m_content( new uint8_t[size()*bytesPerPixel()] )
{}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas
Gilvapaint::Canvas::BPP8(unsigned int width, unsigned int height) noexcept {
  return Gilvapaint::Canvas(width, height, 8);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas
Gilvapaint::Canvas::BPP24(unsigned int width, unsigned int height) noexcept {
  return Gilvapaint::Canvas(width, height, 24);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas
Gilvapaint::Canvas::BPP32(unsigned int width, unsigned int height) noexcept {
  return Gilvapaint::Canvas(width, height, 32);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas::Canvas(const Canvas& that) noexcept
  : m_dimen{that.width(), that.height()},
	m_bpp(that.bitsPerPixel()),
	m_content( new uint8_t[size()*bytesPerPixel()] )
{
  for(unsigned int i=0; i<that.size(); i++) m_content[i]=that.m_content[i];
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas::~Canvas() noexcept {
  delete[] m_content;
  m_content = nullptr;
}
//-----------------------------------------------------------------------------



// --- Operator
//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::operator = (const Canvas& that) noexcept {
  m_dimen[0] = that.width();
  m_dimen[1] = that.height();
  
  m_bpp = that.bitsPerPixel();

  m_content = new uint8_t[size()*bytesPerPixel()];
  for(unsigned int i=0; i<that.size(); i++) m_content[i]=that.m_content[i];
  
  return *this;
}
//-----------------------------------------------------------------------------



// --- Methods
Gilvapaint::Canvas&
Gilvapaint::Canvas::clear(uint32_t color) noexcept {
  return *this; 
}
