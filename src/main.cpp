#include <iostream>

#include "Canvas.hpp"

using namespace std;

int main(){
  Gilvapaint::Canvas canvas = Gilvapaint::Canvas::BPP8(8, 8);
  
  canvas.clear(0)
    .lineColor(1)
    .horizontalLine(2, -1, 12)
    .verticalLine(7, 3, 40);
  canvas.draw();
  
  return 0;
}
