#include "Canvas.hpp"



// --- Memory Management
//-----------------------------------------------------------------------------
Gilvapaint::Canvas::Canvas(unsigned int width, unsigned int height, BPP canvasBPP) noexcept
  : m_dimen{static_cast<int>(width), static_cast<int>(height)},
	m_bpp(canvasBPP),
	m_content( new uint8_t[size()*bytesPerPixel()] )
{}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas::Canvas(unsigned int width, unsigned int height) noexcept
  : Gilvapaint::Canvas(width, height, BPP::MONOCHROME)
{}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*Gilvapaint::Canvas
  Gilvapaint::Canvas::BPP8(unsigned int width, unsigned int height) noexcept {
  return Gilvapaint::Canvas(width, height, 8);
  }*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*Gilvapaint::Canvas
  Gilvapaint::Canvas::BPP24(unsigned int width, unsigned int height) noexcept {
  return Gilvapaint::Canvas(width, height, 24);
  }*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*Gilvapaint::Canvas
  Gilvapaint::Canvas::BPP32(unsigned int width, unsigned int height) noexcept {
  return Gilvapaint::Canvas(width, height, 32);
  }*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas::Canvas(const Canvas& that) noexcept
  : m_dimen{that.width(), that.height()},
	m_bpp( static_cast<BPP>(that.bytesPerPixel()) ),
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
  m_bpp      = static_cast<BPP>( that.bytesPerPixel() );

  m_content = new uint8_t[size()*bytesPerPixel()];
  //for(unsigned int i=0; i<that.size(); i++) m_content[i]=that.m_content[i];
  memcpy(m_content, that.m_content, that.size()*that.bytesPerPixel());
  
  return *this;
}
//-----------------------------------------------------------------------------



// --- Methods
//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::setPixel(int position, uint8_t color) noexcept {
  m_content[position] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::setPixel(int x, int y, uint8_t color) noexcept {
  const int position = x+ y*width();
  return setPixel(position, color);
}
//-----------------------------------------------------------------------------

// --- Helpers
//-----------------------------------------------------------------------------
int
Gilvapaint::Canvas::correctPosition(int position) const noexcept {
  const int thisSize = static_cast<int>( size() );
  
  if( position>=0 and position<thisSize ){
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
Gilvapaint::Canvas::clamp(int value, int MIN, int MAX) const noexcept {
  return std::max(std::min(value, MAX), MIN);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::clear(uint8_t color) noexcept {
  for(int i=0; i<size(); i++) {
    setPixel(i, color);
  }
  
  return *this; 
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::horizontalLine(int y, int xStart, int xEnd) noexcept {
  if( y<0 or y>=static_cast<int>(height()) ) return *this;

  const int lastColumn = static_cast<int>( width()-1 );
  if( xStart<0 or xStart>lastColumn ){
	xStart = clamp(xStart, 0, lastColumn);
  }
  if( xEnd<0 or xEnd>lastColumn ){
	xEnd = clamp(xEnd, 0, lastColumn);
  }
  if( xStart > xEnd){ // swap values
	int temp = xStart;
	xStart = xEnd;
	xEnd = temp;
  }

  for(int i=xStart; i<=xEnd; i++) setPixel(i, y, m_currentColor[0]);
  
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::verticalLine(int x, int yStart, int yEnd) noexcept {
  if( x<0 or x>=static_cast<int>(width()) ) return *this;

  const int lastLine = static_cast<int>( height()-1 );
  if( yStart<0 or yStart>lastLine ) yStart = clamp(yStart, 0, lastLine);
  if( yEnd<0   or yEnd>lastLine )   yEnd   = clamp(yEnd,   0, lastLine);

  if( yStart > yEnd){ // swap values
	int temp = yStart;
	yStart = yEnd;
	yEnd = temp;
  }

  for(int i=yStart; i<=yEnd; i++) setPixel(x, i, m_currentColor[0]);

  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Gilvapaint::Canvas&
Gilvapaint::Canvas::rectangle(int x, int y, int t_width, int t_height) noexcept {
  const int xEnd = x+t_width-1, yEnd = y+t_height-1;
  
  // Culling
  if(t_width>0){
	if( xEnd<0 or x>width() ) return *this;
  } else {
	if( xEnd>width() or x<0 ) return *this;
  }
  if(t_height>0){
	if( yEnd<0 or y>height() ) return *this;
  } else {
	if( yEnd>height() or y<0 ) return *this;
  }

  return horizontalLine( y,     x, xEnd )
	.horizontalLine(     yEnd,  x, xEnd )
	.verticalLine(       x,     y, yEnd )
	.verticalLine(       xEnd,  y, yEnd );
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void
Gilvapaint::Canvas::draw() const noexcept {
  for(int line=0; line<height(); line++){
    for(int column=0; column<width(); column++){

      std::cout << pixel(column, line);
      if(column < width()-1) std::cout << ", ";
      
    }
    std::cout << std::endl;
  }
}
//-----------------------------------------------------------------------------
