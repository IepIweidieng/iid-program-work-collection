#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <windows.h>

namespace BigNum{
    size_t Test_Intmax_Width_Exp(){                //計算最大整數位元數的二的對數
        uintmax_t target = 1;
        size_t    width  = 0,
                  exp    = 0;

        for (; target; target<<=1, ++width);
        for (; size_t(2)<<exp <= width; ++exp);

        return exp;
    }

    size_t const Intmax_W_Exp = Test_Intmax_Width_Exp(); //最大整數位元數的二的對數
    size_t const Intmax_Width = 1<<Intmax_W_Exp;         //最大整數位元數
    uintmax_t const Intmax_W_Mod = Intmax_Width-1;       //最大整數位元數模除遮罩

    typedef std::vector<uintmax_t> BigInt_base;

    class BigInt{
      public:
        class BitRef_Const{                               //對單一位元的唯讀操作
          public:
            BitRef_Const(BigInt const *const _Target, uintmax_t _Offset):
              Target (_Target), Offset (_Offset){}

            operator bool()const{
                if (Offset>>Intmax_W_Exp >= Target->Val.size()){
                    return false;
                }
                return Target->Val[Offset>>Intmax_W_Exp]&(uintmax_t(1)<<(Offset&Intmax_W_Mod));
            }

          protected:
            BigInt const *const Target;
            uintmax_t Offset;
        };

        class BitRef: public BitRef_Const{                //對單一位元的讀取操作
          public:
            BitRef(BigInt *const _Target, uintmax_t _Offset):
              BitRef_Const(_Target, _Offset), Target (_Target){}

            BitRef &operator=(bool _rhs){
                if (Target->Val.size() < (Offset>>Intmax_W_Exp)+1){Target->Val.resize((Offset>>Intmax_W_Exp)+1, 0);}
                Target->Val[Offset>>Intmax_W_Exp] &= ~(uintmax_t(1)<<(Offset&Intmax_W_Mod));
                Target->Val[Offset>>Intmax_W_Exp] |= (uintmax_t(_rhs)<<(Offset&Intmax_W_Mod));
                return *this;
            }

            BitRef &operator&=(bool _rhs){
                if (!_rhs){
                    if (Target->Val.size() < (Offset>>Intmax_W_Exp)+1){Target->Val.resize((Offset>>Intmax_W_Exp)+1, 0);}
                    Target->Val[Offset>>Intmax_W_Exp] &= ~(uintmax_t(_rhs)<<(Offset&Intmax_W_Mod));
                    return *this;
                }
                return *this;
            }

            BitRef &operator|=(bool _rhs){
                if (Target->Val.size() < (Offset>>Intmax_W_Exp)+1){Target->Val.resize((Offset>>Intmax_W_Exp)+1, 0);}
                Target->Val[Offset>>Intmax_W_Exp] |= (uintmax_t(_rhs)<<(Offset&Intmax_W_Mod));
                return *this;
            }

            BitRef &operator^=(bool _rhs){
                if (Target->Val.size() < (Offset>>Intmax_W_Exp)+1){Target->Val.resize((Offset>>Intmax_W_Exp)+1, 0);}
                Target->Val[Offset>>Intmax_W_Exp] ^= (uintmax_t(_rhs)<<(Offset&Intmax_W_Mod));
                return *this;
            }

          private:
            BigInt *const Target;
        };

        BigInt_base Val;  //0 號元素存放最小位數
        bool Neg;

        BigInt(): Val(), Neg(false){}
        BigInt(BigInt const &_val): Val(_val.Val), Neg(_val.Neg){}
        explicit BigInt(uintmax_t _val): Val(), Neg(false){
            Val.push_back(_val);
            Clear_Zero_Head();
        }
        BigInt(intmax_t _val): Val(), Neg(_val < 0){
            if (_val < 0){_val *= -1;}
            Val.push_back(_val);
            Clear_Zero_Head();
        }

        ~BigInt(){
            Val.clear();
        }

        BitRef operator[](uintmax_t _rhs){                //取位元，0 號位元代表最低位元
            BitRef temp = BitRef(this, _rhs);
            return temp;
        }
        BitRef_Const operator[](uintmax_t _rhs)const{     //取位元 const 版本
            return BitRef_Const(this, _rhs);
        }

        BigInt &operator=(BigInt const &_val){            //賦值運算
            Neg = _val.Neg;
            Val.clear();
            Val.assign(_val.Val.begin(), _val.Val.end());
            Clear_Zero_Head();

            return *this;
        }

        BigInt &Clear_Zero_Head(){    //去除多餘位元組
            size_t Hi_Zero = 0;
            bool   Not_Zero = false;

            for (size_t k = Val.size(); k > 0; --k){
                if (Val[k-1]){
                    Not_Zero = true;
                    Hi_Zero = k;
                    break;
                }
            }

            if (!Not_Zero){
                Val.clear();
            } else if (Hi_Zero < Val.size()){
                Val.erase(Val.begin()+Hi_Zero, Val.end());
            }

            return *this;
        }

        friend BigInt No_Zero_Head(BigInt const &_val){    //去除多餘位元組
            BigInt res = _val;
            res.Clear_Zero_Head();
            return res;
        }

        uintmax_t Highest_bit()const{                      //找最高非零位元
            BigInt temp = No_Zero_Head(*this);
            uintmax_t res = temp.Val.size()<<Intmax_W_Exp;

            for (size_t k = Intmax_Width; res > 0 && k > 0; --res, --k){
                if (temp[res-1]){return res-1;}
            }
            return -1;
        }

        friend uintmax_t Highest_bit(BigInt const &_val){  //找最高非零位元
            return _val.Highest_bit();
        }

        friend BigInt abs(BigInt const &_val){
            BigInt res = _val;
            res.Neg = false;
            return res;
        }

        friend BigInt operator&(BigInt const &_lhs, BigInt const &_rhs){  //算術與
            BigInt lhs = _lhs,
                   rhs = _rhs,
                   res;
            size_t Int_length = std::max(_lhs.Val.size(), _rhs.Val.size());

            lhs.Val.resize(Int_length, 0);  //最高位對齊
            rhs.Val.resize(Int_length, 0);
            res.Val.resize(Int_length, 0);

            for (size_t k = 0; k < Int_length; ++k){
                res.Val[k] = lhs.Val[k]&rhs.Val[k];
            }

            return res;
        }

        BigInt &operator&=(BigInt const &_rhs){  //算術與
            *this = *this&_rhs;
            return *this;
        }

        friend BigInt operator|(BigInt const &_lhs, BigInt const &_rhs){  //算術或
            BigInt lhs = _lhs,
                   rhs = _rhs,
                   res;
            size_t Int_length = std::max(_lhs.Val.size(), _rhs.Val.size());

            lhs.Val.resize(Int_length, 0);  //最高位對齊
            rhs.Val.resize(Int_length, 0);
            res.Val.resize(Int_length, 0);

            for (size_t k = 0; k < Int_length; ++k){
                res.Val[k] = lhs.Val[k]|rhs.Val[k];
            }

            return res;
        }

        BigInt &operator|=(BigInt const &_rhs){  //算術或
            *this = *this|_rhs;
            return *this;
        }

        friend BigInt operator^(BigInt const &_lhs, BigInt const &_rhs){  //算術異或
            BigInt lhs = _lhs,
                   rhs = _rhs,
                   res;
            size_t Int_length = std::max(_lhs.Val.size(), _rhs.Val.size());

            lhs.Val.resize(Int_length, 0);  //最高位對齊
            rhs.Val.resize(Int_length, 0);
            res.Val.resize(Int_length, 0);

            for (size_t k = 0; k < Int_length; ++k){
                res.Val[k] = lhs.Val[k]^rhs.Val[k];
            }

            res.Clear_Zero_Head();  //去除多餘位元組

            return res;
        }

        BigInt &operator^=(BigInt const &_rhs){  //算術異或
            *this = *this^_rhs;
            return *this;
        }

        friend BigInt operator>>(BigInt const &_lhs, size_t _rhs){        //邏輯右移
            BigInt res = _lhs;
            uintmax_t temp;
            size_t d_ints = _rhs>>Intmax_W_Exp,
                   d_bits = _rhs&Intmax_W_Mod;

            for (size_t k = 0, n = res.Val.size(); k < n; ++k){
                if (k+d_ints < n){
                    temp = res.Val[k+d_ints]>>d_bits;
                    if (d_bits != 0 && k+d_ints+1 < n){  //注意左移一個位元組是未定義行為
                        temp |= res.Val[k+d_ints+1]<<(Intmax_Width-d_bits);
                    }

                    res.Val[k] = temp;
                } else {
                    res.Val.erase(res.Val.begin()+k, res.Val.end());
                    break;
                }
            }

            return res;
        }

        BigInt &operator>>=(size_t _rhs){  //邏輯右移
            *this = *this>>_rhs;
            return *this;
        }

        friend BigInt operator<<(BigInt const &_lhs, size_t _rhs){        //邏輯左移
            BigInt res = _lhs;
            uintmax_t temp;
            size_t d_ints = _rhs>>Intmax_W_Exp,
                   d_bits = _rhs&Intmax_W_Mod;

            res.Val.resize(res.Val.size()+d_ints+(d_bits != 0), 0);
            for (size_t k = res.Val.size(); k > d_ints; --k){
                temp = res.Val[k-d_ints-1]<<d_bits;
                if (d_bits != 0 && k > d_ints+1){  //注意左移一個位元組是未定義行為
                    temp |= res.Val[k-d_ints-2]>>(Intmax_Width-d_bits);
                }

                res.Val[k-1] = temp;
            }

            for (size_t k = d_ints; k > 0; --k){
                res.Val[k-1] = 0;
            }

            return res;
        }

        BigInt &operator<<=(size_t _rhs){  //邏輯左移
            *this = *this<<_rhs;
            return *this;
        }

        friend bool operator!=(BigInt const &_lhs, BigInt const &_rhs){ //不等於
            BigInt temp = No_Zero_Head(_lhs)^No_Zero_Head(_rhs);
            if (_lhs.Val.size() == 0 && _rhs.Val.size() == 0){return false;}
            if (_lhs.Neg != _rhs.Neg){return true;}

            size_t Hi_difference = temp.Val.size()<<Intmax_W_Exp;

            return Hi_difference != 0;
        }

        friend bool operator>(BigInt const &_lhs, BigInt const &_rhs){ //大於
            BigInt temp = No_Zero_Head(_lhs)^No_Zero_Head(_rhs);
            if (_lhs.Val.size() == 0 && _rhs.Val.size() == 0){return false;}
            if (_lhs.Neg > _rhs.Neg){return false;}
            if (_lhs.Neg < _rhs.Neg){return true;}

            size_t Hi_difference = temp.Val.size()<<Intmax_W_Exp;

            if (Hi_difference == 0){return false;}

            for (size_t n = Hi_difference; Hi_difference+Intmax_Width > n; --Hi_difference){
                if (temp[Hi_difference-1]){
                    --Hi_difference;
                    break;
                }
            }

            return _lhs[Hi_difference];
        }

        friend bool operator>=(BigInt const &_lhs, BigInt const &_rhs){ //大於等於
            BigInt temp = No_Zero_Head(_lhs)^No_Zero_Head(_rhs);
            if (_lhs.Val.size() == 0 && _rhs.Val.size() == 0){return true;}
            if (_lhs.Neg > _rhs.Neg){return false;}
            if (_lhs.Neg < _rhs.Neg){return true;}

            size_t Hi_difference = temp.Val.size()<<Intmax_W_Exp;

            if (Hi_difference == 0){return true;}

            for (size_t n = Hi_difference; Hi_difference+Intmax_Width > n; --Hi_difference){
                if (temp[Hi_difference-1]){
                    --Hi_difference;
                    break;
                }
            }

            return _lhs[Hi_difference];
        }

        friend bool operator==(BigInt const &_lhs, BigInt const &_rhs){ //等於
            BigInt temp = No_Zero_Head(_lhs)^No_Zero_Head(_rhs);
            if (_lhs.Val.size() == 0 && _rhs.Val.size() == 0){return true;}
            if (_lhs.Neg != _rhs.Neg){return false;}

            size_t Hi_difference = temp.Val.size()<<Intmax_W_Exp;

            return Hi_difference == 0;
        }

        friend bool operator<=(BigInt const &_lhs, BigInt const &_rhs){ //小於等於
            BigInt temp = No_Zero_Head(_lhs)^No_Zero_Head(_rhs);
            if (_lhs.Val.size() == 0 && _rhs.Val.size() == 0){return true;}
            if (_lhs.Neg < _rhs.Neg){return false;}
            if (_lhs.Neg > _rhs.Neg){return true;}

            size_t Hi_difference = temp.Val.size()<<Intmax_W_Exp;

            if (Hi_difference == 0){return true;}

            for (size_t n = Hi_difference; Hi_difference+Intmax_Width > n; --Hi_difference){
                if (temp[Hi_difference-1]){
                    --Hi_difference;
                    break;
                }
            }

            return _rhs[Hi_difference];
        }

        friend bool operator<(BigInt const &_lhs, BigInt const &_rhs){ //小於
            BigInt temp = No_Zero_Head(_lhs)^No_Zero_Head(_rhs);
            if (_lhs.Val.size() == 0 && _rhs.Val.size() == 0){return false;}
            if (_lhs.Neg < _rhs.Neg){return false;}
            if (_lhs.Neg > _rhs.Neg){return true;}

            size_t Hi_difference = temp.Val.size()<<Intmax_W_Exp;

            if (Hi_difference == 0){return false;}

            for (size_t n = Hi_difference; Hi_difference+Intmax_Width > n; --Hi_difference){
                if (temp[Hi_difference-1]){
                    --Hi_difference;
                    break;
                }
            }

            return _rhs[Hi_difference];
        }

        BigInt operator+()const{ //原數
            return *this;
        }

        BigInt operator-()const{ //相反數
            BigInt res = *this;
            res.Neg ^= 1;
            return res;
        }

        friend BigInt operator+(BigInt const &_lhs, BigInt const &_rhs){  //整數加法
            BigInt  lhs = _lhs,
                    rhs = _rhs,
                    res;
            size_t  Int_length = std::max(_lhs.Val.size(), _rhs.Val.size());
            uint8_t Hi_bit;     //存放最高位元的加法結果
            bool    Carry = 0;  //進位

            lhs.Val.resize(Int_length, 0);  //最高位對齊
            rhs.Val.resize(Int_length, 0);
            res.Val.resize(Int_length, 0);

            if (Int_length){Carry = lhs.Neg^rhs.Neg;}  //負數與一補數間的誤差
            if (!Carry){                               //如果被加數與加數同號
                res.Neg = lhs.Neg;                 //結果的正負與被加數相同
                lhs = abs(lhs);                    //轉換為正數相加
                rhs = abs(rhs);
            }

            for (size_t k = 0; k < Int_length; ++k){          //加法實作
                if (rhs.Neg){rhs.Val[k] = ~rhs.Val[k];}     //若為負數則取一補數
                if (lhs.Neg){lhs.Val[k] = ~lhs.Val[k];}
                Hi_bit = lhs[((k+1)<<Intmax_W_Exp)-1]+rhs[((k+1)<<Intmax_W_Exp)-1];
                lhs[((k+1)<<Intmax_W_Exp)-1] = false;       //消去最高位元
                rhs[((k+1)<<Intmax_W_Exp)-1] = false;
                res.Val[k] = lhs.Val[k]+rhs.Val[k]+Carry;   //待處理的結果
                Hi_bit += res[((k+1)<<Intmax_W_Exp)-1];
                res[((k+1)<<Intmax_W_Exp)-1] = Hi_bit&1;    //加上已處理的最高位元
                Carry = Hi_bit>>1;                          //計算進位
            }

            if (lhs.Neg^rhs.Neg){                  //如果是正數相減
                res.Neg = !Carry;                  //溢位則結果為正數，否則為負數
            } else {                               //如果是正數相加
                if (Carry){res.Val.push_back(1);}  //溢位則進位
            }

            if (res.Neg){  //如果結果為負數，則把結果轉回正數
                if (Int_length){Carry = true;}  //負數與一補數間的誤差
                for (size_t k = 0; k < Int_length; ++k){
                    res.Val[k] = ~res.Val[k];   //取一補數
                    Hi_bit = res[((k+1)<<Intmax_W_Exp)-1];
                    res[((k+1)<<Intmax_W_Exp)-1] = false;  //消去最高的位元
                    res.Val[k] += Carry;                   //待處理的結果
                    Hi_bit += res[((k+1)<<Intmax_W_Exp)-1];
                    res[((k+1)<<Intmax_W_Exp)-1] = Hi_bit&1;  //加上已處理的最高的位元
                    Carry = Hi_bit>>1;                        //計算進位
                }
            }

            return res;
        }

        BigInt &operator+=(BigInt const &_rhs){  //整數加法
            *this = *this+_rhs;
            return *this;
        }

        BigInt &operator++(){  //整數加法
            *this = *this+1;
            return *this;
        }

        BigInt operator++(int){  //整數加法
            BigInt res = *this;
            *this = *this+1;
            return res;
        }

        friend BigInt operator-(BigInt const &_lhs, BigInt const &_rhs){  //整數減法
            return _lhs+(-_rhs);
        }

        BigInt &operator-=(BigInt const &_rhs){  //整數減法
            *this = *this+(-_rhs);
            return *this;
        }

        BigInt &operator--(){  //整數減法
            *this = *this-1;
            return *this;
        }

        BigInt operator--(int){  //整數減法
            BigInt temp = *this;
            *this = *this-1;
            return temp;
        }
        friend BigInt operator*(BigInt const &_lhs, BigInt const &_rhs){  //整數乘法
            BigInt    lhs = abs(abs(_rhs) > abs(_lhs)? _rhs: _lhs),
                      rhs = No_Zero_Head(abs(abs(_rhs) > abs(_lhs)? _lhs: _rhs)),
                      temp = lhs,
                      res;
            uintmax_t rhs_h_bits = rhs.Highest_bit()+1;

            temp <<= rhs_h_bits;  //先將結果設為被乘數左移到比乘數高一位元處之數
            res = temp;

/*          位元乘法解說
    被乘數 0011 1100 1010 1001 0010
    乘數        0101 1110 1011 1011
    索引                         1+ -

  這裡的乘法，是透過 1+- 索引以及被乘數的移動，並使用加減法來完成。
  開始時，先將 + 索引移到乘數的開頭位元上，並依照 1+- 三個索引的狀態，
    將結果加上或減去被乘數，再進行擦除動作。
  完成一個位元後，將 1+- 索引和被乘數一齊左移。
  + 索引始終與被乘數最低位元對齊。

可能狀態 說明         加減被乘數  擦除
    000  全 0         不動作      無
    010  單獨的 1     + 索引加    + 索引
    011  連續 1 的頭  1 索引加    +- 索引
    100  單或連續 1   不動作      無
    110  連續 1 的尾  + 索引減    無
    111  連續 1 中間  不動作      - 索引
*/

            for (uintmax_t k = 0; k < rhs_h_bits; lhs <<= 1, ++k){  //乘法實作
                if (rhs.Val[k>>Intmax_W_Exp] == 0){  //如果已經處理好該位元組則跳到其末端
                    lhs <<= Intmax_Width-(k&Intmax_W_Mod)-1;
                    k += Intmax_Width-(k&Intmax_W_Mod)-1;
                    continue;
                }
                if (rhs[k+1] && rhs[k]){
                    if (k == 0 || !rhs[k-1]){  //0b110 連續 1 尾
                        res -= lhs;
                    } else {                   //0b111 連續 1 體
                        rhs[k-1] = false;
                    }
                } else if (!rhs[k+1]&&rhs[k]){
                    if (k > 0 && rhs[k-1]){    //0b011 連續 1 頭
                        res += lhs<<1;
                        rhs[k] = false;
                        rhs[k-1] = false;
                    } else {                   //0b010 單獨 1
                        res += lhs;
                        rhs[k] = false;
                    }
                }
            }
            res -= temp;          //將結果減回

            res.Neg = _lhs.Neg^_rhs.Neg;  //處理結果的正負

            return res;
        }

        BigInt &operator*=(BigInt const &_rhs){  //整數乘法
            *this = *this*_rhs;
            return *this;
        }

        friend BigInt operator/(BigInt const &_lhs, BigInt const &_rhs){  //整數除法，向零捨入
            BigInt    lhs = abs(_lhs),
                      rhs = No_Zero_Head(abs(_rhs)),
                      res;
            uintmax_t rhs_l_bit = 0;

            if (rhs == 0){
                throw std::invalid_argument("Division by zero!");
            }

            for (size_t k = Intmax_Width; k > 0; ){  //先把除數左移至大於等於被除數
                for (size_t m = 0; m+1 < k; ++m){    //二分搜尋法
                    if ((rhs<<(rhs_l_bit|(uintmax_t(1)<<(m+1)))) > lhs){
                        rhs_l_bit |= uintmax_t(1)<<m;
                        k = m;
                        goto For_k_Continue;
                    }
                }
                rhs_l_bit |= uintmax_t(1)<<(k-1);
                --k;
                if (rhs<<(rhs_l_bit+1) > lhs){
                    ++rhs_l_bit;
                    break;
                }

              For_k_Continue:;
            }

            rhs <<= rhs_l_bit;

            for (; rhs_l_bit+1 > 0; rhs >>= 1, --rhs_l_bit){  //除法實作
                if (lhs>=rhs){
                    res[rhs_l_bit] = true;
                    lhs -= rhs;
                }
            }

            res.Neg = _lhs.Neg^_rhs.Neg;  //處理結果的正負

            return res;
        }

        BigInt &operator/=(BigInt const &_rhs){  //整數除法
            *this = *this/_rhs;
            return *this;
        }

        friend BigInt operator%(BigInt const &_lhs, BigInt const &_rhs){  //整數取模，恆正
            try{
                BigInt res = _lhs-_lhs/_rhs*_rhs;
                if (res.Neg){res += _rhs;}
                return res;
            } catch (std::invalid_argument const &Error){
                if (std::string(Error.what()) == "Division by zero!"){
                    throw std::invalid_argument("Modulo by zero!");
                } else {
                    throw Error;
                }
            }
        }

        BigInt &operator%=(BigInt const &_rhs){  //整數取模
            *this = *this%_rhs;
            return *this;
        }

        friend BigInt Pow(BigInt const &_lhs, BigInt const &_rhs){  //整數乘冪
            BigInt    lhs = No_Zero_Head(_lhs),
                      rhs = No_Zero_Head(_rhs),
                      temp = lhs,
                      res;
            uintmax_t rhs_h_bits = rhs.Highest_bit()+1;

            if (lhs == 0){
                if (rhs.Neg){                       //0^負數 = 無限
                    throw std::invalid_argument("Negative exponentiation of zero!");
                }
                if (rhs == 0){return 1;}
                return 0;                           //0^正數 = 0
            }
            if (rhs.Neg){                           //整數^負數
                if (lhs ==  1){return 1;}
                if (lhs == -1){return -1*_rhs[0];}
                return 0;
            }

            for (uintmax_t k = rhs_h_bits; k > 0; --k){
                temp *= temp;
            }
            res = temp;  //先將結果設為底數之次數左移到比指數高一位元處之數

/*          位元乘冪解說
    底數   0011 1100 1010 1001 0010
    指數        0101 1110 1011 1011
    索引                         1+ -

  這裡的乘冪法，是透過 1+- 索引以及底數次方的移動，並使用乘除法來完成。
  開始時，先將 + 索引移到指數的開頭位元上，並依照 1+- 三個索引的狀態，
    將結果乘上或除去底數的某次方，再進行擦除動作。
  完成一個位元後，將 1+- 索引和底數次方一齊左移。
  + 索引始終與底數次方的最低位元對齊。

可能狀態 說明         乘除底數    擦除
    000  全 0         不動作      無
    010  單獨的 1     + 索引乘    + 索引
    011  連續 1 的頭  1 索引乘    +- 索引
    100  單或連續 1   不動作      無
    110  連續 1 的尾  + 索引除    無
    111  連續 1 中間  不動作      - 索引
*/

            for (uintmax_t k = 0; k < rhs_h_bits; lhs *= lhs, ++k){  //乘冪實作
                if (rhs.Val[k>>Intmax_W_Exp] == 0){  //如果已經處理好該位元組則跳到其末端
                    for (uintmax_t m = Intmax_Width-(k&Intmax_W_Mod)-1; m > 0; --m){
                        lhs *= lhs;
                    }
                    k += Intmax_Width-(k&Intmax_W_Mod)-1;
                    continue;
                }
                if (rhs[k+1] && rhs[k]){
                    if (k == 0 || !rhs[k-1]){  //0b110 連續 1 尾
                        res /= lhs;
                    } else {                   //0b111 連續 1 體
                        rhs[k-1] = false;
                    }
                } else if (!rhs[k+1]&&rhs[k]){
                    if (k > 0 && rhs[k-1]){    //0b011 連續 1 頭
                        res *= lhs*lhs;
                        rhs[k] = false;
                        rhs[k-1] = false;
                    } else {                   //0b010 單獨 1
                        res *= lhs;
                        rhs[k] = false;
                    }
                }
            }
            res /= temp;          //將結果除回

            res.Neg = _lhs.Neg*_rhs[0];  //處理結果的正負

            return res;
        }

        friend std::ostream &operator<<(std::ostream &_lhs, BigInt const &_rhs){  //轉換進制
            BigInt      lhs = abs(_rhs),
                        rhs;
            intmax_t    base,
                        temp;
            std::string res;
            uintmax_t   rhs_exp = 0;
            bool        Not_Zero = false;

            switch(_lhs.flags()&intmax_t(std::ostream::basefield)){
              case std::ostream::oct:
                base = 8;
              case std::ostream::dec:
                base = 10;
              case std::ostream::hex:
                base = 16;
              default:
                base = 10;
            }
            rhs = base;

            if (_rhs.Neg){
                res += '-';
            } else if (_lhs.flags()&std::ostream::showpos){
                res += '+';
            }

            for (uintmax_t k = Intmax_Width; k > 0; ){  //先把底數次數左移至大於等於待轉換數
                for (uintmax_t m = 0; m+1 < k; ++m){    //二分搜尋法
                    if (Pow(rhs, rhs_exp|(uintmax_t(1)<<(m+1))) > lhs){
                        rhs_exp |= uintmax_t(1)<<m;
                        k = m;
                        goto For_k_Continue;
                    }
                }
                rhs_exp |= uintmax_t(1)<<(k-1);
                --k;
                if (Pow(rhs, rhs_exp+1) > lhs){
                    ++rhs_exp;
                    break;
                }

              For_k_Continue: continue;
              For_k_Break: break;
            }

/*            rhs_exp = lhs.Highest_bit()/rhs.Highest_bit()+1;
            rhs = Pow(rhs, rhs_exp);
*/
            for (; rhs_exp+1 > 0; rhs /= base, --rhs_exp){  //轉換實作
                temp = 0;
                while (lhs>=rhs){
                    ++temp;
                    lhs -= rhs;
                }
                if (temp != 0 || Not_Zero){
                    res += '0'+temp;
                    Not_Zero = true;
                }
            }
            if (!Not_Zero){res += '0';}

            return _lhs<< res;
        }

        std::string const Raw_Output(){
            std::string res;

            if (Neg){res = "-";} else {res = "+";}
            for (uintmax_t k = Val.size()<<Intmax_W_Exp; k > 0; --k){
                res += '0'+(*this)[k-1];
            }

            return res;
        }
    };
}

using namespace std;
using namespace BigNum;

class oFile_Obj{
  public:
    std::ofstream File;

    oFile_Obj(char const *_str, ios_base::openmode _mode = ios_base::out | ios_base::app):
      File(_str, _mode){
        if (!File.is_open()){throw std::ios_base::failure((std::string)"Failed to open file: " + _str);}
    }
    ~oFile_Obj(){
        if (File.is_open()){File.close();}
    }

    template<class Type> friend oFile_Obj &operator<<(oFile_Obj &_lhs, Type const &_rhs){
        _lhs.File<< _rhs;
        return _lhs;
    }

    friend oFile_Obj &operator<<(oFile_Obj &_lhs, std::ostream &((*)(std::ostream&))){
        return _lhs;
    }
};

int main(int argc, char *argv[]){
    std::ios_base::sync_with_stdio(false);

    LARGE_INTEGER QPF;
    QueryPerformanceFrequency(&QPF);
    long double QPT (1000.0/QPF.QuadPart);

    LARGE_INTEGER exeT, finT, exe, fin, exeO, finO;

    std::string Output_Path (argv[0]);
    Output_Path.erase(Output_Path.rfind('\\')+1);
    Output_Path.append("Output.txt");

    oFile_Obj Output (Output_Path.c_str());

    std::ios DefaultOut ((std::streambuf*)NULL);
    DefaultOut.copyfmt(Output.File);

    Output.File.tie((std::ostream*)NULL);
    Output.File.unsetf(std::ios_base::unitbuf);

    QueryPerformanceCounter(&exeT);

    BigInt a = 948, b = 794;

    Output<< "a := "<< a<< '\n'
      << "b := "<< b<< "\n\n"
      << "a = "<< a.Raw_Output()<< '\n'
      << "b = "<< b.Raw_Output()<< "\n\n";

    Output<< "a := a ^ b = "<< a<< " ^ "<< b<< '\n';

    QueryPerformanceCounter(&exe);
    a = Pow(a, b);
    QueryPerformanceCounter(&fin);


    QueryPerformanceCounter(&exeO);
    Output<< "a = "<< a<< '\n'
      << "b = "<< b<< "\n\n"
      << "a = "<< a.Raw_Output()<< '\n'
      << "b = "<< b.Raw_Output()<< "\n\n\n";
    QueryPerformanceCounter(&finO);

    QueryPerformanceCounter(&finT);

    Output<< fixed<< setprecision(10)<<
       left<< "Total duration: "<< setw(29)<< right<< QPT*(finT.QuadPart-exeT.QuadPart)<< " ms\n"<<
       left<< "Calculation duration: "<< setw(23)<< right<< QPT*(fin.QuadPart-exe.QuadPart)<< " ms\n"<<
       left<< "Output processing duration: "<< setw(17)<< right<<QPT*(finO.QuadPart-exeO.QuadPart)<< " ms\n"<< endl;

    Output.File.copyfmt(DefaultOut);

    return 0;
}
