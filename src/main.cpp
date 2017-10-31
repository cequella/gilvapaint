#include <iostream>

#include "Canvas.hpp"

using namespace std;

int main(){
  Gilvapaint::Canvas canvas = Gilvapaint::Canvas(8, 8);
  
  canvas.clear('0')
	.lineColor('1')
	.rectangle(1, 1, 3, 4)
	.draw();
  
  return 0;
}
