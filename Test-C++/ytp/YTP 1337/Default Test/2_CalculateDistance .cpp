#include <iostream>
#include <cstdio>
#include <stdlib.h>
using namespace std;

int main(){

  float a;
  int t1;
  int t2;
  float b;
  int t3;
  scanf("%f,%d,%d,%f,%d",&a,&t1,&t2,&b,&t3);
  double answer = 0;
  answer += (a*t1)*t1/2.0;
  answer += (a*t1)*t2;
  answer += ((a*t1 + (a*t1-b*t3)))*t3/2.0;
  cout.setf(ios::fixed);
  cout.precision(1);
  cout <<answer<<endl;
  return 0;
}