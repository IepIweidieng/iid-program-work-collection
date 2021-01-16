//by Iep Iweidieng
#include "Calender.h"
          ca::ca(){}
          ca::ca(long long y, int m, long long d){Y=y, M=m, D=d;}
          ca::ca(ca &rc){*this=rc;}
bool      ca::great_month()     {return (M<8&& M&1)|| (M>=8&& !(M&1));}          //"&1 (01)"=="%2 (10)"
bool      ca::great_month(int m){return (m<8&& m&1)|| (m>=8&& !(m&1));}
bool      ca::input()           {return std::cin>> Y>> M>> D;}                   //returns false if receives an EOF character (U+001A; ctrl+Z; ^Z)
bool      ca::leap()            {return ((Y%4000&& !(Y%400))|| Y%100)&& !(Y&3);} //"&3 (011)"=="%4 (100)"
bool      ca::leap(long long y) {return ((y%4000&& !(y%400))|| y%100)&& !(y&3);} //years of integer multiples of 4000 doesn't leap here
bool      ca::operator>(ca &rc) {return Y>rc.Y|| (Y==rc.Y&& (M>rc.M|| (M==rc.M&& D>rc.D)));}
bool      ca::operator<(ca &rc) {return Y<rc.Y|| (Y==rc.Y&& (M<rc.M|| (M==rc.M&& D<rc.D)));}
bool      ca::operator^(ca &rc) {return Y^rc.Y|| M^rc.M|| D^rc.D;}
bool      ca::operator=(ca &rc) {return Y=rc.Y, M=rc.M, D=rc.D, true;} //always returns the last value (true)
ca&       ca::operator~(){
  static ca temp;
  return temp.Y=~Y, temp.M=~M, temp.D=~D, temp;
}
char*&    ca::c_str(unsigned& length){
  length=2;
  length+=num_length<long long>(Y)+num_length<int>(M)+num_length<long long>(D)+1;
  static char *str (new char[length] ());
  int pos (length-1);
  str[pos]='\0', pos--;
  pos+=num_to_char<long long>(D, str+pos);
  str[pos]=' ', pos--;
  pos+=num_to_char<int>(M, str+pos);
  str[pos]=' ', pos--;
  pos+=num_to_char<long long>(Y, str+pos);
  return str;
}
long long ca::close_to(ca &rc, bool &NP){
  if (1+Y<rc.Y){long long Di (365*(rc.Y-Y-1)); return D+=Di, Di;}
  for (long long Di; 1+Y==rc.Y;){
    if (M<12) Di=8*(12-M);
    else      Di=32-D;
    return D+=Di, Di;
  }
  if (1+M<rc.M){long long Di (28*(rc.M-M-1)); return D+=Di, Di;}
  for (long long Di; (13+M)%12==(12+rc.M)%12;){
         if (M==2&& !leap()) Di=29-D;
    else if (M==2&& leap()) Di=30-D;
    else if (great_month()) Di=32-D;
    else                   Di=31-D;
    return D+=Di, Di;
  }
  if (D<rc.D){long long Di (rc.D-D); return D+=Di, Di;}
  this->swap_with(rc);
  return NP^=1, 0;
}
void      ca::carry(){
  Y+=4000*(D/1460969), D%=1460969;
  Y+=M/12, M%=12;
  if (M<0){Y-=1, M+=12;}
  for (ca B (~*this); B^*this? B=*this: false;){
    if (((M<=2&& leap())|| (M>2&& leap(Y+1)))&& D>366) Y++, D-=366;
    else if (D>365)                                    Y++, D-=365;
  }
  for (ca B (~*this); B^*this? B=*this: false;){
    if (M<=0)   Y+=M/12, M%=12, Y-=1, M+=12;
    if (M==3&& !leap()&& D<=0) M--, D+=28;
    if (M==3&&  leap()&& D<=0) M--, D+=29;
    if (!great_month(((M+10)%12)+1)&& D<=0) M--, D+=30;
    if (great_month(((M+10)%12)+1)&& D<=0) M--, D+=31;
  }
  for (ca B (~*this); B^*this? B=*this: false;){
    if (M>12)               Y+=M/12, M%=12;
    if (M==2&& !leap()&& D>28) M++, D-=28;
    if (M==2&&  leap()&& D>29) M++, D-=29;
    if (!great_month()&& D>30) M++, D-=30;
    if (great_month()&& D>31) M++, D-=31;
  }
}
void      ca::show(){
  unsigned length;
  char *str (c_str(length));
  for (unsigned i (0); i<length; i++){
    std::cout<< str[i];
  }
  std::cout<< std::endl;
  delete[] str;
}
void      ca::swap_with(ca &rc){
  ca sw(*this);
  *this=rc, rc=sw;
}
template<typename type> int num_length(type &lv){
  int length (1);
  if (lv>=0){for (type i (9); i<lv; i=10*i+9, length++){}
  } else {length++; for (long long i (-9); i>lv; i=10*i-9, length++){}}
  return length;
}
template<typename type> int num_to_char(type &lv, char *poschar){
  int pos (0);
  if (!lv) {
    poschar[pos]='0', pos--;
  } else if (lv>0){
    for (type i (9), j (1); i/10<lv; i=10*i+9, j*=10, pos--){
      poschar[pos]='0'+((lv/j)%10);
    }
  } else {
    for (type i (-9), j (1); i/10>lv; i=10*i-9, j*=10, pos--){
      poschar[pos]='0'-((lv/j)%10);
    }
    poschar[pos]='-';
    pos--;
  }
  return pos;
}