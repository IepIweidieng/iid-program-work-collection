//一些數值交換方法，不使用暫存變數
//2015.8.31 by Iep Iweidieng
typedef long double LD;
typedef long long LL;
#include <iostream>
class A{ public:
  virtual char swap(LD &q, LD &w, LL &e, LL &r){
    return 3;
  }  /*顯示原數
函數型別是 char()(LD&, LD&, LL&, LL&)。
如果不把繼承型別中的 swap 函數宣告成
  具有與虛擬函數相同的型別的函數，
  則會在呼叫時呼叫到
  被繼承型別中的虛擬函數。
*/
};
class B: public A{ public:
  char swap(LD&, LD&, LL &a, LL &b){
    return b+=(a-b)<<1, //需使用整數或定點數型別
           a+=(a-b)   , //c++ 沒有定點數型別
           b+=(a-b)>>1,
           2          ;
  }  //交換差距
};
class C: public A{ public:
  char swap(LD &a, LD &b, LL&, LL&){
    return b=-b  +a*2,
           a=-b  +a*2,
           b= b/2+a/2,
           1         ;
  }  //A::swap 的移項板
};
class D: public A{ public:
  char swap(LD &a, LD &b, LL&, LL&){
    return b+=(a-b)/2, //需使用有點數型別
           a-=(a-b)*2,
           b-=(a-b)  ,
           1         ;
  }  //交換差距二
};
class E: public A{ public:
  char swap(LD &a, LD &b, LL&, LL&){
    return b= a/2+b/2, //需使用有點數型別
           a=-a  +b*2,
           b=-a  +b*2,
           1         ;
  }  //C::swap 的移項板
};
class F: public A{ public:
  char swap(LD&, LD&, LL &a, LL &b){
    return b=b+a,
           a=b-a,
           b=b-a,
           2    ;
  } //加法和減法
};
class G: public A{ public:
  char swap(LD&, LD&, LL &a, LL &b){
    return b= b-a,
           a= b+a,
           b=-b+a,
           2     ;
  } //減法和加法
};
class H: public A{ public:
  char swap(LD&, LD&, LL &a, LL &b){
    try{
      if (!a|!b) throw 0;
  //檢查 a 和 b 是否皆不為 0，否則丟出整數 0
      return b=      b*a,
             a=      b/a,
             b=      b/a,
             2          ;
    } catch (int errlv){
      return errlv;
    }
  } //乘法和除法
};
class I: public A{ public:
  char swap(LD &a, LD &b, LL&, LL&){
    try{
      if (!a|!b) throw 0;
      return b=      b/a, //需使用有點數型別
             a=      b*a,
             b=    1/b*a,
             1          ;
    } catch (int errlv){
      return errlv;
    }
  } //除法和乘法
};
class J: public A{ public:
  char swap(LD&, LD&, LL &a, LL &b){
    return b=b^a, //需使用整數或定點數型別
           a=b^a, //c++ 沒有定點數型別
           b=b^a,
           2    ;
  } //異或（ＸＯＲ）法
};
namespace input{
  LD in_1=LD(),
     in_2=LD(),
     in_v=LD(
       (std::cout<<
             "Input two numbers: ",
        std::cin>> in_1>> in_2    ,
        0                         )
     );
}
void to_swap(A &a){
  using std::cout;
  LD   q=LD   (input::in_1)          ,
       w=LD   (input::in_2)          ;
  LL   e=LL   (q)                    ,
       r=LL   (w)                    ;
  char t=char (a.swap(q, w, e, r))   ;
  (!t)  && cout<< "Failed to swap."  ,
  (t&1) && cout<< "q == "<< q<< ", "<<
                  "w == "<< w        ,
  !(t^3)&& cout<< ", "               ,
  (t&2) && cout<< "e == "<< e<< ", "<<
                  "r == "<< r        ,
                     cout<< std::endl;
}
typedef A* K; /*
K 型別將會有一個 a 陣列實體。
  a 陣列不可被直接宣告為
  一個儲存 被繼承型別實體 的陣列，
  否則在陣列中，
  所有的 繼承型別實體
  都將被轉換成 被繼承型別實體。
  那樣就只能呼叫 被繼承型別 中的函數了。
因此以下將會將 a 陣列宣告為
  一個儲存 被繼承型別實體的「地址」 的陣列。
  而在呼叫副函式 to_swap(A&) 時，
  再去取 陣列中的相對應地址實體
  所儲存的地址上 儲存的繼承型別實體。
*/
typedef unsigned L;
int main(){
  A q;
  B w;
  C e;
  D r;
  E t;
  F y;
  G u;
  H i;
  I o;
  J p;
  K a[]={&p, &o, &i, &u, &y,
                 &t, &r, &e, &w, &q};
  L d         (sizeof(a)/sizeof(*a)),
    f                          (d-1);
  while (d--)  std::cout<< f-d<< ' ',
                      to_swap(*a[d]);
  return + + + + + - - - - * & * & d;
}