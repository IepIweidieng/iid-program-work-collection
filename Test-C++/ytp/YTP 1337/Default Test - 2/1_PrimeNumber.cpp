#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int a;
  cin>>a;
  bool atype = false;
  for(int i=2;i<=sqrt(a);i++)
  {
    if(a%i == 0)
      atype = true;
  }
  if(atype == true)   //輸出非質數
  {
    cout <<a;
    for(int i=a-1;i>2;i--)
    {
      bool itype = false;
      if(i%2==0)
      {
        cout <<" "<<i;
        continue;
      }
      for(int j=3;j<=sqrt(i);j=j+2)
      {
        if(i%j == 0)
        {
          itype = true;
        }
      }
      if(itype == true)
      {
        cout <<" "<<i;
      }
    }
    cout<<" 1";
  }
  else
  {
    if(a==2)
    {
      cout <<"2"<<endl;
      return 0;
    }
    cout <<a;
    for(int i=a-1;i>=2;i--)
    {
      bool itype = false;
      if(i%2==0)
      {
        continue;
      }
      for(int j=3;j<=sqrt(i);j=j+2)
      {
        if(i%j == 0)
        {
          itype = true;
        }
      }
      if(itype == false)
      {
        cout <<" "<<i;
      }
    }
    cout <<" 2"<<endl;
  }
  return 0;
}