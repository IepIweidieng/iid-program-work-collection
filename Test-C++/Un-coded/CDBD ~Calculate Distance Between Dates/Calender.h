//by Iep Iweidieng
#ifndef WHAT_DOES_ca_MEAN
#define WHAT_DOES_ca_MEAN

#include <iostream>
class ca{
  private:
    long long Y, D;                         //儲存年份、日份
    int M;                                  //儲存月份
  public:
              ca();                         //只建立物件
              ca(long long, int, long long);//建立指定日期的物件
              ca(ca&);                      //複製物件用
    bool      great_month();                //判斷儲存月份是否為大月
    bool      great_month(int);             //判斷指定月份是否為大月
    bool      input();                      //讓使用者輸入該物件的年、月、日，輸入 EOF 字元會傳回 false
    bool      leap();                       //判斷儲存年份是否為閏年
    bool      leap(long long);              //判斷指定年份是否為閏年
    bool      operator>(ca&);               //判斷儲存日期晚於另一個物件與否
    bool      operator<(ca&);               //　〆　　　　早於　〆
    bool      operator^(ca&);               //　〆　　　　異於　〆
    bool      operator=(ca&);               //將儲存日期設為另一個物件的儲存日期，然後傳回 true
    ca&       operator~();                  //暫時產生對某物件儲存的年、月、日都進行位元取反的另一物件
    char*&    c_str(unsigned&);             //以字元陣列形式表示物件，並將傳入的參數設為字串長度
    long long close_to(ca&, bool&);         //使該物件的日份增加以接近指定的物件，並傳回增加的日數。NP 指定總時間距離的增加或減少
    void      carry();                      //將月份、日份進位
    void      show();                       //利用字元陣列顯示物件
    void      swap_with(ca&);               //和指定物件交換儲存值
};
template<typename type> int num_length(type&);
template<typename type> int num_to_char(type&, char*);
#endif //WHAT_DOES_ca_MEAN