#include <iostream>

#include "Canvas.hpp"

using namespace std;

int main(){
  Gilvapaint::Canvas canvas = Gilvapaint::Canvas(9, 5);
  
  canvas.clear('0')
	.lineColor('1')
	//.rectangle(5, 5, 5, 5)
	.line(0, 0, 8, 4)
	.draw();
  
  return 0;
}
