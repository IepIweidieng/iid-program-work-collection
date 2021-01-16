//2016.9.25 by Iep Iweidieng.
#include <iostream>

//定義一個巨集。執行它會得到一些輸出入函數的參考。也就是簡寫化。
#define STD_SHORTER \
  typedef std::ostream(OS);\
  typedef OS&((IOM)(OS(&)));\
  IOM(&(el))(std::endl),\
     (&(es))(std::ends),\
     (&(fl))(std::flush);
//巨集定義的結尾多加上分號是為了（相對的）安全。

//用來簡寫化 std::cout 的模板。
template <std::ostream(&(O))=std::cout> class go_homer{
  private:static size_t(nnc);
  private:char(*(name));
  private:bool no_name:1;
  public: ((go_homer)()             ):name   ((char(*))("無名")),
                                      no_name(true)    {((ctor_com)());}
  public: ((go_homer)(char(*(name)))):name   (name)    ,
                                      no_name(false)   {((ctor_com)());}
  public: ((~go_homer)()){
    ((nnshow)((--nnc, (O<< name)<< ' '))<<"回歸。");
  }
  private:void ctor_com(){
    ((nnshow)(((O<< name)<< ' '))<<"出現！", ++nnc);
  }
  private:template <typename OS> OS&((nnshow)(OS(&(rhs)))){
    return(no_name&&(rhs<< nnc<< " 號"),rhs);
  }
};
typedef go_homer<>(GH);
//在使用模板的類別外定義成員時需要使用模板。static 變數成員不能在類別中定義。
template <> size_t (GH::nnc)(0);

//用來簡寫化 std::ios_base::sync_with_stdio() 的模板。
template <bool((&SWS)(bool))=std::ios_base::sync_with_stdio>
 struct faster_c_plusplus_IO_setter{
  typedef std::istream(IS);
  typedef std::ostream(OS);
  typedef std::ios_base::fmtflags(iof);
  static unsigned(ub);
  ((faster_c_plusplus_IO_setter)(IS(&I)=std::cin, OS(&O)=std::cout)){
    (((SWS)(false)), ((I.tie)(NULL)), (O.unsetf(iof(ub))));
  }
};
typedef faster_c_plusplus_IO_setter<>(FIOS);
template <> unsigned (FIOS::ub)(std::ios_base::unitbuf);  //同理。

int main(int(argc), char(*((argv)[]))){
  (FIOS());
  STD_SHORTER;
  OS(&(O))(std::cout);
  size_t const(sz)(4);
  size_t(obj_count)(0);  //二式的最終表象型別不同，不能合併。

  (((O<< es)<< argv[0])<< ':');  //顯示目前執行程式的檔案位置。

  ((O<< el)<< "\n\n一個指標。\n\n");
  GH(*(ptr))(new(GH)((char(*))("指標"))); //New 得一個變數位址，沒什麼特別之處。
  (delete(ptr));

  ((O<< el)<< "\n\n一個參考。\n\n");
  GH(&(rfr))(*new(GH)((char(*))"參考")); //對 new 得的變數位址取值以初始化參考。
  (delete(&rfr));

  ((O<< el)<< "\n\n三個一組的一個指標。\n\n");
/*New 出 1 個 GH 類別的 3 元素陣列。
  注意 new 運算子中最內層的 [] 運算子表示物件的申請數量，不表示陣列。
  因為 GH 是類別（使用者定義型別）的緣故，即使沒有加上 ()，
建立出的物件也會被初始化。
*/
  GH((*(_3_ptr))[3])(new(GH(([1])[3])));
  (delete(_3_ptr));

  ((O<< el)<< "\n\n三個一組的一個參考。\n\n");
  GH((&(_3_rfr))[3])(*new(GH(([1])[3])));  //同理。
  (delete(&_3_rfr));

  ((O<< el)<< "\n\n請觀賞指標指向的十維陣列的初始化、出現與回歸。\n\n");
/*本文重點：如何真正地 new 得多維陣列，而不是多維指標。
  這裡以十次方陣示範。它可以表示十維空間中單邊長為 sz 的正 20 胞體。
*/
  GH(((((((((((*(_10D_sz_ptr))[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])
    (
      new(GH((((((((((([1])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz]))
      ()
    );
  ((obj_count=sizeof*_10D_sz_ptr/sizeof(GH)),
  (delete(_10D_sz_ptr)),
  ((((O<< el)<< "\n陣列元素總數： ")<< obj_count)<< "個。"));

  ((O<< el)<< "\n\n請觀賞參考參考的十維陣列的初始化、出現與回歸。\n\n");
  GH(((((((((((&(_10D_sz_rfr))[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])
   (
     *new(GH((((((((((([1])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz])[sz]))
     ()
   );                                                   //同理，只不過改成參考。
  ((obj_count=sizeof _10D_sz_rfr/sizeof(GH)),
  (delete(&_10D_sz_rfr)),
  ((((O<< el)<< "\n陣列元素總數： ")<< obj_count)<< "個。\n\n"));

  return(O<< fl, 0);  //Return 不是運算子，構成的句子不能被括號括起。
}

//關閉對一個巨集的定義。這是為了（相對的）安全。
#undef STD_SHORTER