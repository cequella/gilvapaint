#include <iostream>
#include <cstdint>
#include <cmath>

int main(){
  std::cout << "Ola, mundo" << std::endl;

  int a = -722;
  a = abs(a)%360;

  std::cout << a << std::endl;
  
  return 0;
}
