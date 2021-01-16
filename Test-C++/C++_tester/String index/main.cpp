#include <iostream>

int main(){
  std::cout<< &((char*)32)[intptr_t(
"\
  The testing words is here:  \n\
\n\
1. A man, a plan, a canal - Panama! \n\
\n\
2. The quick brown fox jumps over the lazy dog. \n\
"
  )]<< std::endl;

  return 0;
}
