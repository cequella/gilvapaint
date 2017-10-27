#include <iostream>

#include "Canvas.hpp"

using namespace std;

int main(){
  Gilvapaint::Canvas canvas = Gilvapaint::Canvas::BPP8(8, 8);
  
  canvas.clear(0)
    .lineColor(9)
    .horizontalLine(2, 0, 8);
    //.verticalLine(3, -1, 40);
  canvas.draw();
  
  return 0;
}
