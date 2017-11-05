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
GilvaPaint::Canvas::Canvas(const Canvas& that) noexcept
  : m_dimen{that.width(), that.height()},
	m_bpp( static_cast<BPP>(that.bytesPerPixel()) ),
	m_content( new uint8_t[size()*bytesPerPixel()] )
{
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

  for(int i=xStart; i<=xEnd; i++) setPixel(i, y, lineColor());
  
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

  for(int i=yStart; i<=yEnd; i++) setPixel(x, i, lineColor());

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
  // If delta Y is negative, swap value. Simetry properties.
  if(y2<y1) {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }

  const int dx = x2-x1;
  const int dy = y2-y1;
  int px=x1, py=y1, dM;

  auto moveRight= [dy](){ return 2*dy; };
  auto moveUp   = [dx](){ return -2*dx; };
  
  if( dx > 0 ){

    if( dy<=dx ){

      /* Primeiro octante */
      dM=2*dy-dx;
      for(; px<=x2; px++){
		setPixel(px, py, lineColor());
		if(dM>0){
		  py++;
		  dM += moveUp();
		}
		dM += moveRight();
      }
    
    } else {

      /* Segundo octante */
      dM=dy-2*dx;
      for(; py<=y2; py++){
		setPixel(px, py, lineColor());
		if(dM<0) {
		  px++;
		  dM += moveRight();
		}
		dM += moveUp();
      }
    
    }
  } else {
    
    if( abs(dx)<=abs(dy) ){
      
      /* Terceiro octante */
      dM=-2*dx-dy;
      for(; py<=y2; py++){
		setPixel(px, py, lineColor());
		if(dM>0){
		  px--;
		  dM -= moveRight();
		}
		dM += moveUp();
      }
      
    } else {
	  
      /* Quarto octante */
      dM=-2*dy-dx;
      for(; px>=x2; px--){
		setPixel(px, py, lineColor());
		if(dM<0) {
		  py++;
		  dM += moveUp();
		}
		dM -= moveRight();
      }
      
    }
  }
  
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::circle(int x, int y, int r) noexcept {
  int dM = 3-2*r;
    
  for(int px=r, py=0; px>=py; py++){
    setPixel(x+px, y+py, lineColor());
    setPixel(x+px, y-py, lineColor());
    setPixel(x-px, y-py, lineColor());
    setPixel(x-px, y+py, lineColor());

    setPixel(x+py, y+px, lineColor());
    setPixel(x+py, y-px, lineColor());
    setPixel(x-py, y-px, lineColor());
    setPixel(x-py, y+px, lineColor());

    
    if(dM>0){
      px--;
	  dM+= -4*px +4;
    }
	dM+= 4*py +6;
  }
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::ellipse(int x, int y, int rh, int rv) noexcept {
  const int qrt_rh = rh*rh;
  const int qrt_rv = rv*rv;

  auto tangent  = [qrt_rh, qrt_rv](int x, int y){ return (not y)?0:(-2*qrt_rv*x)/(2*qrt_rh*y); };
  auto moveUp   = [qrt_rh](int y){ return qrt_rh*(1 +2*y); };
  auto moveRight= [qrt_rv](int x){ return qrt_rv*(1 +2*x); };
  
  int px, py, dM;
  
  // First iteration
  px = rh;
  py = 0;
  dM = qrt_rv*(1/4 -px) +qrt_rh*(1+ 2*py);
  for(; tangent(px, py) not_eq -1; py++){
	setPixel(x+px, y+py, lineColor());
	setPixel(x+px, y-py, lineColor());
	setPixel(x-px, y-py, lineColor());
	setPixel(x-px, y+py, lineColor());
	
	if(dM > 0){
	  px--;
	  dM -= moveRight(px);
	}
	dM += moveUp(py);
  }

  // Second iteration
  px = 0;
  py = rv;
  dM = qrt_rv*(1 +2*px) +qrt_rh*(1/4 -2*py);
  for(; tangent(px, py) not_eq -1; px++){
	setPixel(x+px, y+py, lineColor());
	setPixel(x+px, y-py, lineColor());
	setPixel(x-px, y-py, lineColor());
	setPixel(x-px, y+py, lineColor());
	
	if(dM > 0){
	  py--;
	  dM -= moveUp(py);
	}
	dM += moveRight(px);
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
