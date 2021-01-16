#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <direct.h>
int main()
{
  char WorkDir[1024];
  getcwd(WorkDir, 1024);
  std::string WorkDirS=WorkDir;
  WorkDirS+="\\test.txt";
  std::ofstream File (WorkDirS.c_str(), std::ofstream::out);
  if (!File){return EXIT_FAILURE;}
  LARGE_INTEGER seed;
  QueryPerformanceCounter(&seed);
  srand(seed.QuadPart^time(NULL));
  int T=2;
  while (T--){
    int C=10000;
    while (C--){
      File<< rand();
    }
    File<< "\n";
  }
  File<< "100000\n";
  File.flush();
  std::cout<< WorkDirS.c_str()<<std::endl;
  File.close();
  return EXIT_SUCCESS;
}
