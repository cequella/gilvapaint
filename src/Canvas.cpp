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
Gilvapaint::Canvas::Canvas(unsigned int width, unsigned int height) noexcept
: Gilvapaint::Canvas(width, height, 24)
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
  //for(unsigned int i=0; i<that.size(); i++) m_content[i]=that.m_content[i];
  memcpy(m_content, that.m_content, that.size()*that.bytesPerPixel());
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
  //for(unsigned int i=0; i<that.size(); i++) m_content[i]=that.m_content[i];
  memcpy(m_content, that.m_content, that.size()*that.bytesPerPixel());
  
  return *this;
}
//-----------------------------------------------------------------------------



// --- Methods
//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::setPixel(int position, uint32_t color) noexcept {
  uint8_t* pointer = m_content;
  pointer += position*bytesPerPixel();
  
  memcpy(pointer, &color, bytesPerPixel()); // TODO How it works?
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::setPixel(int x, int y, uint32_t color) noexcept {
  const int position = x+ y*width();
  
  uint8_t* pointer = m_content;
  pointer += position*bytesPerPixel();
  
  memcpy(pointer, &color, bytesPerPixel()); // TODO How it works?
  return *this;
}
//-----------------------------------------------------------------------------

// --- Helpers
//-----------------------------------------------------------------------------
int
Gilvapaint::Canvas::correctPosition(int position) const noexcept {
  const int thisSize = static_cast<int>( size() );
  
  if( position>0 and position<thisSize ){
    return position;
  }
  if( position>thisSize ) {
    return ( position%thisSize );
  }

  return (thisSize - position%thisSize);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int
Gilvapaint::Canvas::clamp(int value, int MAX, int MIN) const noexcept {
  return std::max(std::min(value, MAX), MIN);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::clear(uint32_t color) noexcept {
  for(unsigned int i=0; i< size(); i++) {
    setPixel(i, color);
  }
  
  return *this; 
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::horizontalLine(int y, int xStart, int xEnd) noexcept {
  if( y<0 or y>=static_cast<int>(height()) ) return *this;
  const int thisWidth = static_cast<int>( width() );

  // Clamp x coord to [ 0, width() )
  if( xStart<0 or xStart>thisWidth ){
    xStart = clamp(xStart, 0, thisWidth);
  }
  if( xEnd<0 or xEnd>thisWidth ){
    xEnd = clamp(xEnd, 0, thisWidth);
  }

  for(int i=xStart; i<xEnd; i++){
    setPixel(i, y, m_currentColor[0]);
  }
  
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::verticalLine(int x, int yStart, int yEnd) noexcept {
  if( x<0 or x>=static_cast<int>(width()) ) return *this;
  const int thisHeight = static_cast<int>( height() );

  // Clamp y coord to [ 0, height() )
  if( yStart<0 or yStart>thisHeight ){
    yStart = clamp(yStart, 0, thisHeight);
  }
  if( yEnd<0 or yEnd>thisHeight ){
    yEnd = clamp(yEnd, 0, thisHeight);
  }

  for(int i=yStart; i<yEnd; i++){
    setPixel(x, i, m_currentColor[0]);
  }

  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::rectangle(int x, int y, int width, int height) noexcept {
  if(width==0 or height==0) return *this;
  
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void
Gilvapaint::Canvas::draw() const noexcept {
  for(unsigned int line=0; line<height(); line++){
    for(unsigned int column=0; column<width(); column++){

      std::cout << pixel(line, column);
      if(column < width()-1) std::cout << ", ";
      
    }
    std::cout << std::endl;
  }
}
//-----------------------------------------------------------------------------
