/*2016/9/18 Coded for GNU GCC Compiler and by Iep Iweidieng.
  2016/9/18 Fixed errs in comments and add new comments.
            Made some code better.*/
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

namespace{
  double (a3_4)  (1.5d)     ;
  int    (a_1)   (true)     ,
         (a3_5_1)(a_1&~a_1) ;
  bool   (a3_5_2)(+a3_5_1)  ;
  int    (fa_1()){return 0;}
         (fa_2()){return 0;}
         (fa_3()){return 0;}


/*◼變數宣告定義 versus 函式宣告定義　～ 符之雨*/


/*◆變數宣告與定義
  ⚪變數宣告式
  「extern 型別」 變數名（, 變數或函式名, ……）;　如：*/
  extern int n1_1;
  extern int(n1_2);
  int extern(((((((((((((((((((((((((((((((n1_3)))))))))))))))))))))))))))))));


/*⚪變數定義式
  型別 變數名（, 變數或函式名, ……）;  如；*/
  int n1_1;
  int(n1_2);
  /*int(n1_2);                //int(n1_2) 為定義式
    int(n1_2), 0;             //int(n1_2) 為定義式，由於尾隨的 0，編譯出錯
//「error: expected unqualified-id before numeric constant」
    0, int(n1_2);             //int(n1_2) 為運算式
    int value=int(n1_2);      //int(n1_2) 為運算式
    int value(int(n1_2));     //int(n1_2) 為函式宣告式之參數*/
  int((((((((((((((((((((((((((((((((n1_3))))))))))))))))))))))))))))))));


/*⚪變數賦值定義式
  型別 變數名 初始值（, 變數或函式名, ……）;　如：*/
  int n2_1=1;
  int(n2_2)=1;
  /*int(n2_2)=1;              //int(n1_2) 為定義式
    int(n2_2)=1, 0;           //int(n1_2) 為定義式，由於尾隨的 0，編譯出錯
//「error: expected unqualified-id before numeric constant」
    0, int(n2_2)=1;           //int(n1_2) 為運算式，由於將運算結果賦值，編譯出錯
//「error: lvalue required as left operand of assignment」
    int value=int(n2_2)=1;    //int(n2_2) 為運算式，由於將運算結果賦值，編譯出錯
//「error: lvalue required as left operand of assignment」
    int value(int(n2_2)=1);   //int(n1_2) 為函式宣告式之參數*/
//※賦值運算子（=、+=、-= 等）的運算順序是由右往左。
  int n2_3=int();             //使用轉換建構函式先建構出整數 0（預設建構引數值）
  int n2_4=int(1);            //使用轉換建構函式先建構出整數 1
  int n2_5=int(a3_4);         //使用轉換建構函式將 a3_4 轉換為整數型別
  int((n2_6))=((int)((int((((int((((int)((((1))))))))))))));
  int((((n2_7))))=(long((unsigned int)(((long long int)(float(double(2e7)))))));
  /*使用轉換建構函式時，不可有一個以上的識別子單字，如「long long(1);」；
      但可以使用括號，也就是可以使用「(long long)(1);」，
      這時它變成了 C 語言式的型別轉換，又稱為「隱式轉換」。*/
  int(n2_8)=(ios::sync_with_stdio(false),
              cin.tie(NULL),
              0
            );                //在初始化的同時將標準 C++ 輸出入的效能提升
  extern int n2_9=1;          //定義式，而非宣告式；出現在函式中則編譯出錯
//出現在函式中：「error: '（變數名）' has both 'extern' and initializer」


/*⚪變數建構定義式
  型別 變數名 建構引數（, 變數或函式名, ……）;　如：*/
  int n3_1(0);                 //引數不能為空，否則被視為函式宣告
  int(n3_2)(0);                //引數不能為空，否則被視為函式宣告
  int(n3_3)((int(int(1)), 2)); //初始化為 2，注意建構引數中的括號使用
  int(n3_4)((int(a3_4)));      //初始化為整數化的 a3_4，注意建構引數中的括號使用
  int((n3_5))((int)int((int)(int((int)((int((int)(int)int(((int()))))))))));
  int(n3_6)((a3_5_1=cout.precision(),
             a3_5_2=!(cout.flags()&ios::scientific),
             cout.precision(int(((int)int()))),
             cout.flags((cout.flags()&~ios::scientific)|ios::fixed),
             cout<< "Test: "<< 1e16/7e0<< 9e18/13e-1<< 7e9*8e16<< '\n'<< flush,
             cout.precision(a3_5_1),
             cout.flags(
               cout.flags()|(ios::scientific&ios_base::fmtflags(~a3_5_2))
             ),
             0
           ));                 //在初始化的同時顯示訊息
  extern int(n3_7)(1);         //定義式，而非宣告式；出現在函式中則編譯出錯
//出現在函式中：「error: '（變數名）' has both 'extern' and initializer」
}
namespace global{
  template <int val, int size> int(*f(int(&)[size]))[size]{
  /*val 是在 size 相同的狀況下還能使函式被編譯出不同的版本用的。
    如果編譯出的函式的版本是相同的話，回傳的 static 實體全都會是同一個實體
    陷阱：(&) 不能被省略，否則被轉成指標，無法判斷 size 的值
  */
    static int a[size];
    for (int i (0); i<size; a[i]=i, ++i);
    return cout<< "val: "<< val<< ", size: "<< size<< ", &a: "<<&a<< '\n', &a;
  }
  void(f_test)(){
    int((&v1)[10])(*new(int([0])[10])),
       ((&v2)[15])(*new(int([0])[15])),
       ((&v3)[15])(*new(int([0])[15]));
    /*new(int([0])[15])，也就是 new int[0][15] 的結合順序：
        分配 0 個實體的空間 [0] ⇨ 15 元素陣列 [15 ]⇨ int ⇨ new

    */
                             //陣列大小不能為 0
    f<0>(v1), f<0>(v2), f<1>(v3);
    delete &v1, delete &v2, delete &v3;
  }
  void(*f_tester)((f_test(), reinterpret_cast<void*>(NULL)));
}
namespace{
/*★變數的指標、陣列、參考
  範例：*/
  int(*(Ptr_1))(&a_1),                                              //單純指標
     (*(*(Ptr_Ptr_1)))(&Ptr_1),                                     //指標的指標
     (*((Ptr_Array_1)[]))={&a_1, Ptr_1},
  /*二元素整數指標陣列；指標陣列
    指標儲存某型別變數的地址，因此指標表示某型別變數的地址；
      也就是，某型別變數的地址和同一型別變數的指標的型別是相同的，
      都可以使用指標陣列儲存。*/
     (*(&(Ptr_Rfn_1)))(Ptr_1),                                      //指標參考

     ((Array_1)[])={0, 1, 2},                                       //單純陣列
  //陷阱：函式不能夠回傳陣列
     ((*(Array_Ptr_1))[sizeof(Array_1)/sizeof(*Array_1)])(&Array_1),//陣列指標
  /*一個指向元素量數為 Array_1 的元素數量的整數陣列的指標。
    注意括號的使用，最先和變數名稱結合的修飾符號表示著變數的根本樣貌。

  在這裡，變數名先與 * 號結合，表示它是一個指標；
    再與 [（陣列的元素數量）] 結合，表示它是指向一個陣列的指標，
    最後與 int 結合，表示它是指向一個整數陣列的指標，

  因為陣列的元素數是陣列的型別的一部分，因此對應的指標也要宣告成
    只能指向特定元素數的陣列的指標。

  陷阱（？）一：當陣列初始化時，如果在 [] 中不填上 0，
    而將陣列初始化為空陣列時，該陣列就無法被指標指向，也無法被參考參考。

    如：
     int((Array_1)[])={},
        ((*(Array_Ptr_1))[sizeof(Array_1)/sizeof(*Array_1)])(&Array_1),
//「error: cannot convert 'int (*)[0]' to 'int (*)[0]' in initialization」
        ((&(Array_Rfn_1))[sizeof(Array_1)/sizeof(*Array_1)])(Array_1);
//「error: invalid initialization of reference of type 'int (&)[0]'
//          from expression of type 'int [0]'」
    可行修正：
     int((Array_1)[0]),        //（下略）
    或：
     int((Array_1)[0])={},     //（下略）
    兩者皆可通過編譯。

    ※函式不能夠回傳陣列，但能回傳陣列的指標。
    回傳陣列指標的函式看起來像這樣：
     int((*((f)()))[]);
    也就是：
     int (*f())[];
  */
     (((Array_Array_1)[2])[sizeof(Array_1)/sizeof(*Array_1)])=
       {{Array_1[0], Array_1[1], Array_1[2]}, 3, 4, 5},             //陣列的陣列
  /*三元素整數陣列的二元素陣列；是通稱的二維陣列。

  陷阱一：雖然是陣列的陣列，初始化的列表中要放入陣列時，
    只能使用花括弧列表，在列表中使用陣列變數中的元素，不可直接使用陣列變數。

  陷阱二：陣列的初始化列表中的每一組花括弧都代表一個陣列，
    因此不可隨意地使用花括弧。

    如：
      int Array_Array_1[2][3]={{0, 1}, 2, 3, 4, 5};
    裡面的 {0, 1} 會被視為三元素陣列而由右向右地被填滿，
    因此這個陣列中實際上有七個元素，超出了 2 × 3 = 6 個元素數，編譯時會出錯。
    一種可行修正：
      int Array_Array_1[2][3]={{0, 1}, 3, 4, 5};

    又如：
      int Array_Array_1[2][3]={{0, 1, 2, 3}, 4, 5};
    內層的花括弧代表三元素陣列，但有四個元素，超出了三個元素數，編譯時會出錯。
    一種可行修正：
      int Array_Array_1[2][3]={{0, 1, 2}, 4, 5};

    又：
      int Array_Array_1[2][3]={0, 1, {2, 3, 4}};
    在花括弧前的元素不能完全組成三元素陣列，編譯時會出錯。
    一種可行修正：
      int Array_Array_1[2][3]={{0, 1}, {2, 3, 4}};

    正確的範例：
      int Array_Array_1[2][3]={{}, {});
      int Array_Array_1[2][3]={{}, 1);
      int Array_Array_1[2][3]={1);
      int Array_Array_1[2][3]={};
    這四者實際上都是六個元素，皆可通過編譯。
  */
     ((&(Array_Rfn_1))[sizeof(Array_1)/sizeof(*Array_1)])(Array_1), //陣列參考

     (&(Rfn_1))(a_1);                                               //單純參考
  /*陷阱：& 後不能加上 const，因為它就是被參考物，不能有獨有的屬性。*/
     //參考指標不存在，因為參考就是被參考物，它並不是特有的型別
     //參考陣列不存在，參考不是一種資料型別
     //參考的參考不存在，參考不是一種資料型別
  /*只有在函式的參數列中，參考才會被當作一種資料型別，
    但參考的指標、陣列及參考仍不存在。*/

  void(*(Ptr_2))(NULL),
      (*(&(Ptr_Rfn_2)))(Ptr_2),
      (*((Ptr_Array_2)[]))={Ptr_2, Ptr_Rfn_2},
      (*((*(Ptr_Array_Ptr_2))[2]))(&Ptr_Array_2);
  /*指向二元素 void* 陣列的指標；指標陣列指標。
    結合順序：Ptr_Array_Ptr_2 ⇨指標 * ⇨二元素陣列 [2] ⇨指標 * 。*/

  //括號展開 + 建構初始化改賦值初始化後：
  void *Ptr_3=NULL,
       *&Ptr_Rfn_3=Ptr_3,
       *Ptr_Array_3[]={Ptr_3, Ptr_Rfn_3},
       *(*Ptr_Array_Ptr_3)[2]=&Ptr_Array_3;
  /*中間的括號不能省去，不然變數名稱會先與 [2] 結合，變成二元素 void** 陣列。
    無括號的結合順序：Ptr_Array_Ptr_3 ⇨二元素陣列 [2] ⇨指標 * ⇨指標 * ；
    括號後的結合順序：Ptr_Array_Ptr_3 ⇨指標 * ⇨二元素陣列 [2] ⇨指標 * 。*/


/*◆函式宣告定義
  ⚪函式宣告式
  回傳值型別 函式名稱 參數型別（, 變數或函式名, ……）;　如：*/
  int f1_1();                  //被判斷為函數而非變數
  int(f1_2)();                 //被判斷為函數而非變數
  int(f1_3());
  int((f1_4)());
  /*int((f1_4)());             //int((f1_4)()) 為宣告式
    int((f1_4)()), 0;          //int((f1_4)()) 為宣告式，由於尾隨的 0，編譯出錯
//「error: expected unqualified-id before numeric constant」
    0, int((f1_4)());          //int((f1_4)()) 為運算式
    int value=int((f1_4)());   //int((f1_4)()) 為運算式
    int value(int((f1_4)()));  //int((f1_4)()) 為函式宣告式之參數*/
  int f1_5(char);
  int(f1_6)(char(c)='\1');     //使用了預設引數的函式宣告
  int f1_7(char(*), char(*(&)));
  int(((((f1_8))))(char((((&)))), char(((*)))=(char*)((char(((char)char()))))));
  int((*((f1_9)(int((*)(int)))))(int));
  /*傳入一個指向 int()(int) 函式型別的函式指標（型別為 int(*)(int) ），
      會回傳一個 int()(int) 函式型別的地址（型別為 int(*)(int) ）。

    將全式分解如下：
      int    (( * ((f1_9 )(    int    ((     *     )(  int  )) ) ))(  int    ));
{最終表象型別|指標{真函式{參數回傳型別|參數函式指標|參數參數   }  }回傳值參數}
{最終表象型別|指標{真函式{參數回傳前部|   參數    |參數回傳後部}  }回傳值參數}
{最終表象型別|指標{真函式{             參數完全體              }  }回傳值參數}
{  回傳型別前部   {真函式{             參數完全體              }  }回傳型別後部}
{                                 真函式完全體                                 }
  */

  /*※回傳值型別和參數型別都是函式型別的一部分，但只有回傳值型別是最終表象型別，
      因此可以同時進行變數與函式的宣告及定義。*/


/*⚪函式定義式
  回傳值型別 函式名稱 參數型別 {函式內容}（函式名 參數 {內容}……）;　如：*/
  int f1_1(){return 0;}
  int(f1_2)(){return int();}
  int(f1_3()){return int(char());}
  int((f1_4)()){return int((int)(int(int(((int)(int((int()))))))));}
  int f1_5(char=0){return (int)(int(char((int((char)char())))));}
  int(f1_6)(char(c)){return (unsigned long long int)(long(c));}
  /*因為參數 c 已經有預設值，因此不能在這裡再次設定預設值。*/
  int f1_7(char(*(lhs)), char(*(&rhs))){return (int)(char((int)lhs)+(int)*rhs);}
  int((f1_8)(char(&lhs), char(*rhs))){
  /*因為參數 rhs 已經有預設值，因此只能設定參數 lhs 的預設值；
      但由於參數 rhs 在這裡沒有被設定預設值，
      在參數 rhs 前的參數 lhs 不能被設定預設值；也就是不能再次設定預設引數。*/
    return char(lhs=char((lhs-=*rhs, lhs))*int(++*rhs));
  }
  int((*((f1_9)(int((*(e1_9))(int)))))(int)){return e1_9;}

/*★函式的指標、陣列、參考
  範例：*/
  int(*(f_Ptr_1))()(&fa_1),                                     //單純指標
     (*(*(f_Ptr_Ptr_1)))()(&f_Ptr_1),                           //指標的指標
     (*((f_Ptr_Array_1a)[]))()={&fa_1, f_Ptr_1},                //指標陣列
     (*(&(f_Ptr_Rfn_1)))()(f_Ptr_1),                            //指標參考

     //函式陣列不存在，因為函式的記憶體占用大小並不固定，無法形成陣列。
     //這裡以函式指標陣列作為函式陣列的代替物
     (*((f_Ptr_Array_1)[]))()={&fa_1, fa_2, *************fa_3}, //指標陣列
  /*對函式地址型態的函式地址取值會得到函式型態的函式地址；
      而對函式型態的函式取值會得到函式型態的函式地址，
      因此不管在函式名稱前加上 & 取址運算子，不加運算子，
      或加上無限制的取值運算子，最後都會得到函式的地址。*/
     (*((*(f_Ptr_Array_Ptr_1))[sizeof(f_Ptr_Array_1)/sizeof(*f_Ptr_Array_1)]))()
       (&f_Ptr_Array_1),                                        //指標陣列指標
     (*((f_Ptr_Array_Array_1[2])[sizeof(f_Ptr_Array_1)/sizeof(*f_Ptr_Array_1)]))
       ()={{f_Ptr_Array_1[0], f_Ptr_Array_1[1], f_Ptr_Array_1[2]}, NULL, NULL},
                                                                //指標陣列的陣列
     (*((&(f_Ptr_Array_Rfn_1))[sizeof(f_Ptr_Array_1)/sizeof(*f_Ptr_Array_1)]))()
       (f_Ptr_Array_1),                                         //指標陣列參考

     (&(f_Rfn_1))()(*************************************fa_1); //單純參考
  /*因為對函式型態的函式取值會得到函式型態的函式地址，
      因此不管在函式名稱前不加運算子，或加上無限制的取值運算子，
      最後都會得到函式型態的實體，可以被函式型態的參考參考。
    陷阱：因為對函式型態的函式取址會得到函式地址型態的函式地址，
      不是函式型態的實體，因此不可被函式型態的參考參考。
      如：
        (&(f_Rfn_1))()(&fa_1);
      編譯將會出錯。
//「error: invalid initialization of non-const reference of type 'int (&)()'
//         from an rvalue of type 'int (*)()'」
    */
     //參考指標不存在，因為參考就是被參考物，它並不是特有的型別
     //參考陣列不存在，參考不是一種資料型別
     //參考的參考不存在，參考不是一種資料型別

  int(*f2_1)(int(*e2_1)(int(*d2_1)(int(*c2_1)), int(*b2_1)), int(*a2_1));
  /*函式指標，可指向帶有兩個參數，其中一個是
      指向帶有一個
        指向帶有一個
          整數指標參數
        的回傳整數的函式的指標的參數
      的回傳整數的函式的函式指標，
    另一個是
      整數指標
    的回傳整數的函式*/

  //這樣會更清楚：
  typedef int((d2_)(int *c2_)),
             ((e2_)(d2_*, int *b2_)),
             ((f2_)(e2_*, int *a2_));
  f2_(*f2_2);

  //對應的函式的定義：
  int(f_d)(int(*(rhs)))           {return *rhs;}
     (f_e)(d2_(*lhs), int(*(rhs))){return lhs(rhs);}
     (f_f)(e2_(*lhs), int(*(rhs))){return lhs(f_d, rhs);}
     (f_g)(int(*(rhs)))           {return f_f(f_e, rhs);}
  /*呼叫函式的一般方式是：
      函式名(引數);

    但實際上卻是：
      函式的地址(引數);

    因此只要有運算式的結果型別是函式或函式的地址，
      就可以在右方加上括號及引數來呼叫函式。
  */

  //函式指標的設定：
  f2_(*f2_3)(f2_1=f2_2=f_f);    //在設定別的變數的同時初始化自己為函式 f_f 的地址


/*◼後語
  ★const 的使用*/
  int const(asK_1)             (1)        ,//一個整數常數
           (asK_2)             (1)        ;//還是整數常數
  const int(*(asK_Ptr_1))      (&asK_1)   ,//指向整數常數的指標
           (*const(asK_PtrK_1))(asK_Ptr_1);//指向整數常數的常指標
  //const 必須在 * 後面，且不被空白字元以外的字元分隔
  int      (as_1)              (1)        ,
           (*(as_Ptr_1))       (&as_1)    ,//指向整數變數的指標
           (*const(as_PtrK_1)) (as_Ptr_1) ,//指向整數變數的常指標
           ((*((*const(fas_PtrK_1))(int((*)(int)))))(int))(&f1_9),
  /*指向參數為 int(*)(int) 型態且回傳值為 int(*)(int) 型態的函式常指標，
      可指向函式 f1_9。*/
           ((*((*const(fasK_PtrK_1))(int((*)(int)))))(int)const)
             ((int((*((*const)(int((*)(int)))))(int)const))(&f1_9));
  /*指向參數為 int(*)(int) 型態且回傳值為 int(*)(int) 型態的常函式常指標，
      可指向函式 f1_9。
    注意函式本身雖然不是常數，卻隱含有常數屬性，因此轉換為常數時沒有效果。
    真正的常函式只能在類別成員函式中宣告及定義。
  */


/*★可以重複宣告，不能重複定義*/
  extern int as_2, as_2, as_2, as_2, as_2, as_2, as_2, as_2, as_2, as_2(1),
             fas_2(), fas_2(), fas_2(), fas_2(), fas_2(), fas_2(), fas_2();
  int        fas_2(), fas_2(), fas_2(), fas_2(), fas_2(), fas_2(), fas_2();
//※定義後就不能再次宣告。

/*★最終表象型別相同的變數或函式可以同時連續地宣告或定義*/
  int extern (as1_1), (as1_2), (as1_3);
  int        (as1_1)(1), (as1_2)(2), (as1_3)(3);
  int ((fas1_1)()), ((fas1_2)()), ((fas1_3)());
  int ((fas1_1)()){return 0;} ((fas1_2)()){return 0;} ((fas1_3)()){return 0;}

/*★不在函式中同時宣告與定義變數與宣告函式的方式*/
  extern int(as2_1)     ,      //變數宣告式
            (as2_2)(1)  ,      //變數定義式
            ((fas2_1)());      //函式宣告式

/*★在函式中同時定義變數與宣告函式的方式*/
  int(as2_1)(1)  ,             //變數定義式
     ((fas2_2)());             //函式宣告式
//※在函式中不可定義函式。


  int (fas_2()){return 0;} ((fas2_1)()){return 0;} ((fas2_2)()){return 0;}
}
namespace{
//以下是顯示某個實體的地址、名稱、型別、值的函式
  template <typename T>
   void((show_vs_and_fs)(string const(&lhs), T(&rhs))){             //一般變數
    cout<< reinterpret_cast<void*>(&rhs) <<" "<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< rhs<< '\n';
  }
  template <typename T>
   void((show_vs_and_fs)(string const(&lhs), T const(&rhs))){       //常數
    cout<< reinterpret_cast<void const*>(&rhs) <<" K"<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< rhs<< '\n';
  }
  template <typename T>
   void((show_vs_and_fs)(string const(&lhs), T(*(&rhs)))){          //指標
    cout<< reinterpret_cast<void*>(&rhs) <<" "<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< reinterpret_cast<void*>(rhs)<<
           "\t(address)\n";
  }
  template <typename T>
   void((show_vs_and_fs)(string const(&lhs), T const(*(&rhs)))){    //常數的指標
    cout<< reinterpret_cast<void*>(&rhs) <<" "<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< reinterpret_cast<void const*>(rhs)<<
           "\t(address)\n";
  }
  template <typename T>
   void((show_vs_and_fs)(string const(&lhs), T(*const(&rhs)))){     //常指標
    cout<< reinterpret_cast<void const*>(&rhs) <<" K"<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< reinterpret_cast<void const*>(rhs)<<
           "\t(address)\n";
  }
  template <typename T, int A1>
   void((show_vs_and_fs)(string const&lhs,T((&rhs)[A1]))){          //陣列
    cout<< reinterpret_cast<void*>(&rhs) <<" "<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< rhs<<
           "\t("<< A1<< "-placed array)\n";
  }
  template <typename T, int A1, int A2>
   void((show_vs_and_fs)(string const(&lhs), T(((&rhs)[A1])[A2]))){ //陣列的陣列
    cout<< reinterpret_cast<void*>(&rhs) <<" "<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< rhs<<
           "\t("<< A1<< "-placed "<< A2<< "-placed array)\n";
  }
//以下是可取得函式參數型別的類別
  template <typename T> class get_parm_type{                     //一般型別
   private:T(rhs);
   public: string(type);
   public: get_parm_type():rhs (), type (typeid(rhs).name()){}
  };
  template <> class get_parm_type <char(&)>{                     //char& 型別
   private:char(rhs);
   public: string(type);
   public: get_parm_type():rhs (0), type (typeid(rhs).name()){}
  };
  template <> class get_parm_type <char(*(&))>{                  //char*& 型別
   private:char(*(rhs));
   public: string(type);
   public: get_parm_type():rhs ((char(*))("")), type (typeid(rhs).name()){}
  };
  template <typename T> class get_parm_type <T const>{           //常型別
   private:T(rhs);
   public: string(type);
   public: get_parm_type():rhs (), type ("K"+string(typeid(rhs).name())){}
  };
  template <> class get_parm_type <char const(*(&))>{            //char*& 常型別
   private:char(*(rhs));
   public: string(type);
   public: get_parm_type():rhs ((char(*))("")),
                           type ("K"+string(typeid(rhs).name())){}
  };
//回到顯示某個實體的地址、名稱、型別、值的函式
  template <typename T>
   void ((show_vs_and_fs)(string const(&lhs), T((&rhs)()))){        //無參數函式
    cout<< reinterpret_cast<void*>(&rhs) <<" "<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< reinterpret_cast<void*>(rhs)<<
           "\t(0-parmed function)\n";
  }
  template <typename T, typename A1>
   void((show_vs_and_fs)(string const(&lhs),T((&rhs)(A1)))){        //一參數函式
    cout<< reinterpret_cast<void*>(&rhs) <<" "<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< reinterpret_cast<void*>(rhs)<<
           "\t(1-parmed function: "<< get_parm_type<A1>().type<< ")\n";
  }
  template <typename T, typename A1, typename A2>
   void((show_vs_and_fs)(string const(&lhs), T((&rhs)(A1, A2)))){   //二參數函式
    cout<< reinterpret_cast<void*>(&rhs) <<" "<< typeid(rhs).name()<<
           "\t"<< lhs<< "\t==  "<< reinterpret_cast<void*>(rhs)<<
           "\t(2-parmed function: "<< get_parm_type<A1>().type<<
           " and "<< get_parm_type<A2>().type<< ")\n";
  }
}
//以下是主函式
int main(int const(argc), char const(*const((argv)[]))){
  return cout<< "Address  Type\tName\t==  Value ==========------\n\n",
         show_vs_and_fs("a3_4", a3_4),
         show_vs_and_fs("a_1", a_1),
         show_vs_and_fs("a3_5_1", a3_5_1),
         show_vs_and_fs("a3_5_2", a3_5_2),
         show_vs_and_fs("fa_1", fa_1),
         show_vs_and_fs("fa_2", fa_2),
         show_vs_and_fs("fa_3", fa_3),
         show_vs_and_fs("n1_1", n1_1),
         show_vs_and_fs("n1_2", n1_2),
         show_vs_and_fs("n1_3", n1_3),
         show_vs_and_fs("n2_1", n2_1),
         show_vs_and_fs("n2_2", n2_2),
         show_vs_and_fs("n2_3", n2_3),
         show_vs_and_fs("n2_4", n2_4),
         show_vs_and_fs("n2_5", n2_5),
         show_vs_and_fs("n2_6", n2_6),
         show_vs_and_fs("n2_7", n2_7),
         show_vs_and_fs("n2_8", n2_8),
         show_vs_and_fs("n2_9", n2_9),
         show_vs_and_fs("n3_1", n3_1),
         show_vs_and_fs("n3_2", n3_2),
         show_vs_and_fs("n3_3", n3_3),
         show_vs_and_fs("n3_4", n3_4),
         show_vs_and_fs("n3_5", n3_5),
         show_vs_and_fs("n3_6", n3_6),
         show_vs_and_fs("n3_7", n3_7),
         show_vs_and_fs("Ptr_1", Ptr_1),
         show_vs_and_fs("Ptr_Ptr_1", Ptr_Ptr_1),
         show_vs_and_fs("Ptr_Array_1", Ptr_Array_1),
         show_vs_and_fs("Ptr_Rfn_1", Ptr_Rfn_1),
         show_vs_and_fs("Array_1", Array_1),
         show_vs_and_fs("Array_Ptr_1", Array_Ptr_1),
         show_vs_and_fs("Array_Array_1", Array_Array_1),
         show_vs_and_fs("Array_Rfn_1", Array_Rfn_1),
         show_vs_and_fs("Rfn_1", Rfn_1),
         show_vs_and_fs("Ptr_2", Ptr_2),
         show_vs_and_fs("Ptr_Rfn_2", Ptr_Rfn_2),
         show_vs_and_fs("Ptr_Array_2", Ptr_Array_2),
         show_vs_and_fs("Ptr_Array_Ptr_2", Ptr_Array_Ptr_2),
         show_vs_and_fs("Ptr_3", Ptr_3),
         show_vs_and_fs("Ptr_Rfn_3", Ptr_Rfn_3),
         show_vs_and_fs("Ptr_Array_3", Ptr_Array_3),
         show_vs_and_fs("Ptr_Array_Ptr_3", Ptr_Array_Ptr_3),
         show_vs_and_fs("f1_1", f1_1),
         show_vs_and_fs("f1_2", f1_2),
         show_vs_and_fs("f1_3", f1_3),
         show_vs_and_fs("f1_4", f1_4),
         show_vs_and_fs("f1_5", f1_5),
         show_vs_and_fs("f1_6", f1_6),
         show_vs_and_fs("f1_7", f1_7),
         show_vs_and_fs("f1_8", f1_8),
         show_vs_and_fs("f1_9", f1_9),
         show_vs_and_fs("f_Ptr_1", f_Ptr_1),
         show_vs_and_fs("f_Ptr_Ptr_1", f_Ptr_Ptr_1),
         show_vs_and_fs("f_Ptr_Array_1a", f_Ptr_Array_1a),
         show_vs_and_fs("f_Ptr_Rfn_1", f_Ptr_Rfn_1),
         show_vs_and_fs("f_Ptr_Array_1", f_Ptr_Array_1),
         show_vs_and_fs("f_Ptr_Array_Ptr_1", f_Ptr_Array_Ptr_1),
         show_vs_and_fs("f_Ptr_Array_Array_1", f_Ptr_Array_Array_1),
         show_vs_and_fs("f_Ptr_Array_Rfn_1", f_Ptr_Array_Rfn_1),
         show_vs_and_fs("f_Rfn_1", f_Rfn_1),
         show_vs_and_fs("f2_1", f2_1),
         show_vs_and_fs("f2_2", f2_2),
         show_vs_and_fs("f_d", f_d),
         show_vs_and_fs("f_e", f_e),
         show_vs_and_fs("f_f", f_f),
         show_vs_and_fs("f_g", f_g),
         show_vs_and_fs("f2_3", f2_3),
         show_vs_and_fs("asK_1", asK_1),
         show_vs_and_fs("asK_2", asK_2),
         show_vs_and_fs("asK_Ptr_1", asK_Ptr_1),
         show_vs_and_fs("asK_PtrK_1", asK_PtrK_1),
         show_vs_and_fs("as_1", as_1),
         show_vs_and_fs("as_Ptr_1", as_Ptr_1),
         show_vs_and_fs("as_PtrK_1", as_PtrK_1),
         show_vs_and_fs("fas_PtrK_1", fas_PtrK_1),
         show_vs_and_fs("fasK_PtrK_1", fasK_PtrK_1),
         show_vs_and_fs("as_2", as_2),
         show_vs_and_fs("fas_2", fas_2),
         show_vs_and_fs("as1_1", as1_1),
         show_vs_and_fs("as1_2", as1_2),
         show_vs_and_fs("as1_3", as1_3),
         show_vs_and_fs("fas1_1", fas1_1),
         show_vs_and_fs("fas1_2", fas1_2),
         show_vs_and_fs("fas1_3", fas1_3),
         show_vs_and_fs("as2_1", as2_1),
         show_vs_and_fs("as2_2", as2_2),
         show_vs_and_fs("fas2_1", fas2_1),
         show_vs_and_fs("fas2_2", fas2_2),
         show_vs_and_fs("main", main),             //使用 Windows Batch 程式輸出
/*「show.cmd」
@echo off& >nul chcp 950& setlocal EnableExtensions
>"%~dp0Out.txt" (
  for /f "tokens=* usebackq" %%a in ("%~dp0In.txt") do (
    echo;         show_vs_and_fs^("%%a", %%a^),
  )
)
*/
/*◼GNU GCC Compiler 的 typeid().name() 的輸出
  ★範例解釋一：PA3_PFivE
  FivE      表示回傳值為 i (int)，參數為 v (void；沒有參數) 的函式；
  P         表示指標 (Pointer)
  PFivE     表示指向 FivE 的指標
  A3_       表示大小為 3 的陣列 (Array)
  A3_PFivE  表示大小為 3 的 PFivE 陣列
  PA3_PFivE 表示指向大小為 3 的 PFivE 陣列的指標

  ★範例解釋二：KPKi
  i    表示整數 (int)
  K    表示常數 (const)
  Ki   表示整數常數
  P    表示指標 (Pointer)
  PKi  表示指向整數常數的指標
  KPKi 表示指向整數常數的常指標
*/
          cout<< "\nAddress  Type\tName\t==  Value ==========------\n"<< flush,
          0;
}