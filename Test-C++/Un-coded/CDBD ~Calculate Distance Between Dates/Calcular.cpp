//by Iep Iweidieng
#include "Calender.h"
long long calc_di(ca &c1, ca &c2){
  c1.carry();
  c2.carry();
  long long Di (0);
  bool NP (true);
  for (ca c (c1); c^c2;){
    Di+=(((NP<<1)-1)*(c.close_to(c2, NP)));
    c.carry();
  }
  return (((!(Di>>((sizeof(Di)<<3)-1)))<<1)-1)*Di;
}
int run(){
  using std::cout;
  for (ca c1, c2; c1.input()&& c2.input();) cout<< calc_di(c1, c2)<< "\n";
  cout.flush();
  return 0;
}