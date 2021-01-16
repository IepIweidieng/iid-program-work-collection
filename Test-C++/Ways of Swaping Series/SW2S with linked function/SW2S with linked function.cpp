//一些數值交換方法，不使用暫存變數
//類串列函式版本
//2015.9.1 by Iep Iweidieng
typedef long double LD;
typedef long long   LL;
namespace A{
  typedef char (CDL)(LD&, LD&, LL&, LL&);
  CDL swap_0,
      swap_1,
      swap_2,
      swap_3,
      swap_4,
      swap_5,
      swap_6,
      swap_7,
      swap_8,
      swap_9,
      *swap_X (&swap_0); /*
  宣告指向 char()(LD&, LD&, LL&, LL&) 型別實體的地址實體。
  地址實體型別為 char(*)(LD&, LD&, LL&, LL&)。
  內容初始化為函式 swap_1 的地址，也就是函式串列的起點。
*/
  char swap_0(LD&, LD&, LL&, LL&){
    return swap_X=&swap_1,
           3             ;
  }  //顯示原數
  char swap_1(LD&, LD&, LL &a, LL &b){
    return swap_X=&swap_2,
           b+=(a-b)<<1   , //需使用定點數型別
           a+=(a-b)      , //c++ 的定點數型別
           b+=(a-b)>>1   ,     //只有整數型別
           2             ;
  }  //交換差距
  char swap_2(LD &a, LD &b, LL&, LL&){
    return swap_X=&swap_3,
           b=-b  +a*2    ,
           a=-b  +a*2    ,
           b= b/2+a/2    ,
           1             ;
  }  //swap_1 的移項版
  char swap_3(LD &a, LD &b, LL&, LL&){
    return swap_X=&swap_4,
           b+=(a-b)/2    , //需使用有點數型別
           a-=(a-b)*2    ,
           b-=(a-b)      ,
           1             ;
  }  //交換差距二
  char swap_4(LD &a, LD &b, LL&, LL&){
    return swap_X=&swap_5,
           b= a/2+b/2    , //需使用有點數型別
           a=-a  +b*2    ,
           b=-a  +b*2    ,
           1             ;
  }  //swap_3 的移項版
  char swap_5(LD &a, LD &b, LL&, LL&){
    return swap_X=&swap_6,
           b= b+a        ,
           a= b-a        ,
           b= b-a        ,
           1             ;
  } //加法和減法
  char swap_6(LD &a, LD &b, LL&, LL&){
    return swap_X=&swap_7,
           b= b-a        ,
           a= b+a        ,
           b=-b+a        ,
           1             ;
  } //減法和加法
  char swap_7(LD &a, LD &b, LL&, LL&){
    try{
      if (!a|!b) throw 0;
  //檢查 a 和 b 是否皆不為 0，否則丟出整數 0
      return swap_X=&swap_8,
             b=  b*a       ,
             a=  b/a       ,
             b=  b/a       ,
             1             ;
    } catch (int errlv){
      return swap_X=&swap_8,
             errlv         ;
    }
  } //乘法和除法
  char swap_8(LD &a, LD &b, LL&, LL&){
    try{
      if (!a|!b) throw 0;
      return swap_X=&swap_9,
             b=  b/a       , //需使用有點數型別
             a=  b*a       ,
             b=1/b*a       ,
             1             ;
    } catch (int errlv){
      return swap_X=&swap_9,
             errlv         ;
    }
  } //除法和乘法
  char swap_9(LD&, LD&, LL &a, LL &b){
    return swap_X=0, //函式串列的結尾
           b= b^a  , //需使用定點數型別
           a= b^a  , //c++ 的定點數型別
           b= b^a  ,     //只有整數型別
           2       ;
  } //異或（ＸＯＲ）法
}
#include <iostream>
namespace input{
  LD in_1=LD()                    ,
     in_2=LD()                    ,
     in_v=LD(
       (std::cout<<
             "Input two numbers: ",
        std::cin>> in_1>> in_2    ,
        0                         )
     );
}
int main(int argc, char *argv[]){
  using  std::cout                       ;
  LL     _=LL  ()                        ;
  while (A::swap_X){
    LD   a=LD  (input::in_1)             ,
         b=LD  (input::in_2)             ;
    LL   c=LL  (a)                       ,
         d=LL  (b)                       ;
    char e=char((*A::swap_X)(a, b, c, d));
    cout<< _++<<' '                      ;
    ! e    &&  cout<< "Failed to swap."  ,
     (e&1) &&  cout<< "a == "<< a<< ", "<<
                      "b == "<< b        ,
    !(e^3) &&  cout<< ", "               ,
     (e&2) &&  cout<< "c == "<< c<< ", "<<
                      "d == "<< d        ,
                         cout<< std::endl;
  }
  return + + + - - - * & * &(input::in_v);
}