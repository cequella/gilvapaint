#include "Canvas.hpp"



// --- Memory Management
//-----------------------------------------------------------------------------
GilvaPaint::Canvas::Canvas(unsigned int width, unsigned int height) noexcept
  : m_dimen{static_cast<int>(width), static_cast<int>(height)} {
  
  m_content = SDL_CreateRGBSurface(0,
								   width, height,
								   32,
								   RMASK, GMASK, BMASK, AMASK);

  SDL_FillRect(m_content, NULL, SDL_MapRGBA(m_content->format, 0, 0, 0, 255));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas::Canvas(const Canvas& that) noexcept
  : m_dimen{that.width(), that.height()} {

  m_content = SDL_CreateRGBSurface(0,
								   that.width(), that.height(),
								   32,
								   RMASK, GMASK, BMASK, AMASK);
  
  SDL_BlitSurface(that.m_content, NULL, m_content, NULL);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas::~Canvas() noexcept {
  SDL_FreeSurface(m_content);
  m_content = nullptr;
}
//-----------------------------------------------------------------------------



// --- Operator
//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::operator = (const Canvas& that) noexcept {
  m_dimen[0] = that.width();
  m_dimen[1] = that.height();

  m_content = SDL_CreateRGBSurface(0,
								   that.width(), that.height(),
								   32,
								   RMASK, GMASK, BMASK, AMASK);

  SDL_BlitSurface(that.m_content, NULL, m_content, NULL);
  
  return *this;
}
//-----------------------------------------------------------------------------



// --- Methods
//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::setPixel(int position, uint32_t color) noexcept {
  Uint32* temp = (Uint32*)m_content->pixels;
  temp[position] = color;
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::setPixel(int x, int y, uint32_t color) noexcept {
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
  if( position>=thisSize ) {
    return ( position%thisSize );
  }

  return (thisSize + (position%thisSize));
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
GilvaPaint::Canvas::clear(uint32_t color) noexcept {
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

  SDL_LockSurface(m_content);
  for(int i=xStart; i<xEnd; i++) setPixel(i, y, lineColor());
  SDL_UnlockSurface(m_content);
  
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

  SDL_LockSurface(m_content);
  for(int i=yStart; i<yEnd; i++) setPixel(x, i, lineColor());
  SDL_UnlockSurface(m_content);
  
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


  SDL_LockSurface(m_content);
  if( dx > 0 ){

    if( dy<=dx ){

      /* Primeiro octante */
      dM=2*dy-dx;
      for(; px<x2; px++){
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
      for(; py<y2; py++){
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
      for(; py<y2; py++){
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
      for(; px>x2; px--){
		setPixel(px, py, lineColor());
		if(dM<0) {
		  py++;
		  dM += moveUp();
		}
		dM -= moveRight();
      }
      
    }
  }
  SDL_UnlockSurface(m_content);
  
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::circle(int x, int y, int radius) noexcept {
  if(radius<0) radius = -radius;
  int dM = 3-2*radius;

  SDL_LockSurface(m_content);
  for(int px=radius, py=0; px>=py; py++){
    pixel(x+px, y+py, lineColor())
      .pixel(x+px, y-py, lineColor())
      .pixel(x-px, y-py, lineColor())
      .pixel(x-px, y+py, lineColor())

      .pixel(x+py, y+px, lineColor())
      .pixel(x+py, y-px, lineColor())
      .pixel(x-py, y-px, lineColor())
      .pixel(x-py, y+px, lineColor());

    
    if(dM>0){
      px--;
      dM+= -4*px +4;
    }
    dM+= 4*py +6;
  }
  SDL_UnlockSurface(m_content);
  
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
GilvaPaint::Canvas&
GilvaPaint::Canvas::ellipse(int x, int y, int a, int b) noexcept {
  if(a==0 or b==0){
	return *this;
  }
  a = std::abs(a);
  b = std::abs(b);
  
  const int a2 = a*a;
  const int b2 = b*b;

  int px, py, dM;
  
  auto moveUp       =[a2](int py){ return a2*(1 +2*py); };
  auto moveDown     =[a2](int py){ return a2*(1 -2*py); };
  auto moveRight    =[b2](int px){ return b2*(1 +2*px); };
  auto moveLeft     =[b2](int px){ return b2*(1 -2*px); };
  auto drawQuarters =[this, x, y](int px, int py){
    pixel(x+px, y+py, lineColor())
    .pixel(x+px, y-py, lineColor())
    .pixel(x-px, y-py, lineColor())
    .pixel(x-px, y+py, lineColor());
  };

  SDL_LockSurface(m_content);
  // First iteration
  px = a;
  py = 0;
  dM = b2*(1/4 -px) +a2*(1+ 2*py);
  for(; a2*py<=b2*px; py++){
    drawQuarters(px, py);
	
    if(dM > 0){
      px--;
      dM += moveLeft(px);
    }
    dM += moveUp(py);
  }

  // Second iteration
  px = 0;
  py = b;
  dM = b2*(1 +2*px) +a2*(1/4 -2*py);
  for(; b2*px<=a2*py; px++){
    drawQuarters(px, py);
	
    if(dM > 0){
      py--;
      dM += moveDown(py);
    }
    dM += moveRight(px);
  }
  SDL_UnlockSurface(m_content);
  
  return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void
GilvaPaint::Canvas::drawOver(SDL_Surface* surface) const noexcept {
  SDL_BlitSurface(m_content, NULL, surface, NULL);
}
//-----------------------------------------------------------------------------
