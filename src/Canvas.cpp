#include "Canvas.hpp"



// --- Memory Management
//-----------------------------------------------------------------------------
GilvaPaint::Canvas::Canvas(unsigned int width, unsigned int height, BPP canvasBPP) noexcept
: m_dimen{static_cast<int>(width), static_cast<int>(height)},
  m_bpp(canvasBPP),
  m_content( new uint8_t[size()*bytesPerPixel()] )
{}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas::Canvas(unsigned int width, unsigned int height) noexcept
: GilvaPaint::Canvas(width, height, BPP::MONOCHROME)
{}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*GilvaPaint::Canvas
  GilvaPaint::Canvas::BPP8(unsigned int width, unsigned int height) noexcept {
  return GilvaPaint::Canvas(width, height, 8);
  }*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*GilvaPaint::Canvas
  GilvaPaint::Canvas::BPP24(unsigned int width, unsigned int height) noexcept {
  return GilvaPaint::Canvas(width, height, 24);
  }*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*GilvaPaint::Canvas
  GilvaPaint::Canvas::BPP32(unsigned int width, unsigned int height) noexcept {
  return GilvaPaint::Canvas(width, height, 32);
  }*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas::Canvas(const Canvas& that) noexcept
: m_dimen{that.width(), that.height()},
  m_bpp( static_cast<BPP>(that.bytesPerPixel()) ),
  m_content( new uint8_t[size()*bytesPerPixel()] )
{
  //for(unsigned int i=0; i<that.size(); i++) m_content[i]=that.m_content[i];
  memcpy(m_content, that.m_content, that.size()*that.bytesPerPixel());
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas::~Canvas() noexcept {
  delete[] m_content;
  m_content = nullptr;
}
//-----------------------------------------------------------------------------



// --- Operator
//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::operator = (const Canvas& that) noexcept {
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
GilvaPaint::Canvas&
GilvaPaint::Canvas::setPixel(int position, uint8_t color) noexcept {
  m_content[position] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::setPixel(int x, int y, uint8_t color) noexcept {
  const int position = x+ y*width();
  return setPixel(position, color);
}
//-----------------------------------------------------------------------------

// --- Helpers
//-----------------------------------------------------------------------------
int
GilvaPaint::Canvas::correctPosition(int position) const noexcept {
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
GilvaPaint::Canvas::clamp(int value, int MIN, int MAX) const noexcept {
  return std::max(std::min(value, MAX), MIN);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::clear(uint8_t color) noexcept {
  for(int i=0; i<size(); i++) {
    setPixel(i, color);
  }
  
  return *this; 
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::horizontalLine(int y, int xStart, int xEnd) noexcept {
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
GilvaPaint::Canvas&
GilvaPaint::Canvas::verticalLine(int x, int yStart, int yEnd) noexcept {
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
GilvaPaint::Canvas&
GilvaPaint::Canvas::rectangle(int x, int y, int t_width, int t_height) noexcept {
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
GilvaPaint::Canvas&
GilvaPaint::Canvas::line(int x1, int y1, int x2, int y2) noexcept {
  const int dx = x2-x1; // =-b
  const int dy = y2-y1; // =a

  int px=x1, py=y1, dM;
  if(dx>0){
    dM=2*dy-dx;
    
    if(dy<=dx){

      /* Primeiro octante */
      for(; px<=x2; px++){
	setPixel(px, py, m_currentColor[0]);
	if(dM>0){
	  py++;
	  dM += 2*(dy-dx); // Move right
	} else {
	  dM += 2*dy; // Move up-right
	}
      }
    
    } else { 

      /* Segundo octante */
      for(; py<=y2; py++){
	setPixel(px, py, m_currentColor[0]);
	if(dM>0){
	  dM -= 2*dx; // Move up
	} else {
	  px++;
	  dM += 2*(dy-dx); // Move up-right
	}
      }
    
    }
  } else {
    if(dy<=dx){
      /* Quarto octante */
    } else {
      /* Terceiro octante */
    }
  }
  
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void
GilvaPaint::Canvas::draw() const noexcept {
  for(int line=0; line<height(); line++){
    for(int column=0; column<width(); column++){

      std::cout << pixel(column, line);
      if(column < width()-1) std::cout << ", ";
      
    }
    std::cout << std::endl;
  }
}
//-----------------------------------------------------------------------------
