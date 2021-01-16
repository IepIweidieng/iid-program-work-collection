#include <iostream>
#include <string>
using namespace std;

int main(){
  string a;
  cin >>a;
  for(unsigned int i=0;i<a.length();i++)
  {
    if(a.length() > 5 || a[i] == 'Z' || a[i] == 'z')
    {
      cout <<"Error"<<endl;
      return 0;
    }
  }
  int numofABC = 0;
  for(unsigned int i=0;i<a.length();i++)
  {
    int buffer =0;
    if(a[i] > 'Z')
      buffer = a[i] - 'a'+1;
    else
      buffer = a[i] - 'A'+1;
    numofABC *= 25;
    numofABC += buffer;
  }

  char answer[6] = {'0', '0','0', '0','0','0'};
  int yo = 5;
  while(numofABC != 0)
  {
    if(numofABC%16 > 9 )
      answer[yo] = 'A' + (numofABC%16)-10;
    else
      answer[yo] = '0' + numofABC%16;
    yo--;
    numofABC/=16;
  }
  for(int i=0;i<6;i++)
  {
    cout <<answer[i];
  }
  cout <<endl;
  return 0;
}