#include <iostream>

namespace LLLLL{
    long long const LLLL_MASK = 1000000000000000000LL,
                    LLLL_UB   =  100000000000000000LL,
                    LLLL_SR   =          1000000000LL;

    struct LLLL{ long long h, l; };

    inline LLLL LL2LLLL(long long val){
        LLLL tmp = {0, val};
        return tmp;
    }

    inline bool operator==(LLLL lhs, LLLL rhs){
        return lhs.h == rhs.h && lhs.l == rhs.l;
    }
    inline bool operator==(LLLL lhs, long long rhs){ return lhs == LL2LLLL(rhs); }
    inline bool operator==(long long lhs, LLLL rhs){ return LL2LLLL(lhs) == rhs; }

    inline LLLL operator+(LLLL lhs, LLLL rhs){
        LLLL res = {lhs.h%LLLL_UB + rhs.h%LLLL_UB, lhs.l%LLLL_UB + rhs.l%LLLL_UB};
        res.h += lhs.l/LLLL_UB + rhs.l/LLLL_UB;
        return res;
    }
    inline LLLL operator+(LLLL lhs, long long rhs){ return lhs + LL2LLLL(rhs); }
    inline LLLL operator+(long long lhs, LLLL rhs){ return LL2LLLL(lhs) + rhs; }

    inline LLLL &operator+=(LLLL &lhs, LLLL rhs){ return lhs = lhs + rhs; }
    inline LLLL &operator+=(LLLL &lhs, long long rhs){ return lhs = lhs + LL2LLLL(rhs); }

    inline LLLL operator-(LLLL lhs, LLLL rhs){
        LLLL res = {lhs.h - rhs.h, lhs.l - rhs.l};
        if (res.l < 0){ res.h -= 1, res.l += LLLL_MASK; }
        if (res.h < 0){ res.h += LLLL_MASK; }
        return res;
    }
    inline LLLL operator-(LLLL lhs, long long rhs){ return lhs - LL2LLLL(rhs); }
    inline LLLL operator-(long long lhs, LLLL rhs){ return LL2LLLL(lhs) - rhs; }

    inline LLLL &operator-=(LLLL &lhs, LLLL rhs){ return lhs = lhs - rhs; }
    inline LLLL &operator-=(LLLL &lhs, long long rhs){ return lhs = lhs - LL2LLLL(rhs); }

    inline LLLL operator*(LLLL lhs, LLLL rhs){
        LLLL res = {((lhs.h%LLLL_SR)*(rhs.l%LLLL_SR) + (lhs.l%LLLL_SR)*(rhs.h%LLLL_SR))%LLLL_MASK, (lhs.l%LLLL_SR)*(rhs.l%LLLL_SR)};
        res.h += (lhs.l/LLLL_SR)*(rhs.l/LLLL_SR) + res.l/LLLL_MASK;
        res.l %= LLLL_MASK;
        return res;
    }
    inline LLLL operator*(LLLL lhs, long long rhs){ return lhs * LL2LLLL(rhs); }
    inline LLLL operator*(long long lhs, LLLL rhs){ return LL2LLLL(lhs) * rhs; }

    inline LLLL &operator*=(LLLL &lhs, LLLL rhs){ return lhs = lhs * rhs; }
    inline LLLL &operator*=(LLLL &lhs, long long rhs){ return lhs = lhs * LL2LLLL(rhs); }

    inline LLLL operator/(LLLL lhs, long long rhs){
        LLLL res = {lhs.h/rhs, lhs.l/rhs};
        long long hr = lhs.h%rhs, lr = lhs.l%rhs, srmr = LLLL_SR%rhs;
        res.l += hr*(LLLL_MASK/rhs), res.h += res.l/LLLL_MASK, res.l %= LLLL_MASK;
        res.l += ((hr*srmr/rhs)*srmr)%rhs, res.h += res.l/LLLL_MASK, res.l %= LLLL_MASK;
        res.l += ((hr*srmr)%rhs*srmr)/rhs, res.h += res.l/LLLL_MASK, res.l %= LLLL_MASK;
        res.l += (((hr*srmr)%rhs*srmr)%rhs + lr)/rhs, res.h += res.l/LLLL_MASK, res.l %= LLLL_MASK;
    /*
        (h*M+l)/k
        = ((kh[q]+h[r])*M + (kl[q]+l[r]))/k
        = (kh[q]*M + h[r]*M + kl[q] + l[r])/k
        = (h[q]*M + l[q]) + (h[r]*M + l[r])/k
        = (h[q]*M + l[q]) + (h[r]*(kM[q]+M[r]) + l[r])/k
        = (h[q]*M + l[q]) + (h[r]*kM[q] + h[r]*M[r] + l[r])/k
        = (h[q]*M + l[q] + h[r]*M[q]) + (h[r]*M[r] + l[r])/k
        = (h[q]*M + l[q] + h[r]*M[q]) + (h[r]*(sqrt(M)*sqrt(M))[r] + l[r])/k
        = (h[q]*M + l[q] + h[r]*M[q])
          + (((kh[r]*sqrt(M)[r]*sqrt(M)[r])[q] + (h[r]*sqrt(M)[r])[r])*sqrt(M)[r] + l[r])/k
        = (h[q]*M + l[q] + h[r]*M[q])
          + (h[r]*sqrt(M)[r])[q]*sqrt(M)[r]
          + ((h[r]*sqrt(M)[r])[r]*sqrt(M)[r] + l[r])/k
        = (h[q]*M + l[q] + h[r]*M[q])
          + (h[r]*sqrt(M)[r])[q]*sqrt(M)[r]
          + (((k(h[r]*sqrt(M)[r])[r]*sqrt(M)[r])[q]
              + ((h[r]*sqrt(M)[r])[r]*sqrt(M)[r])[r])
             + l[r])/k
        = (h[q]*M + l[q] + h[r]*M[q])
          + (h[r]*sqrt(M)[r])[q]*sqrt(M)[r]
          + (((h[r]*sqrt(M)[r])[r]*sqrt(M)[r])[q]
          + (((h[r]*sqrt(M)[r])[r]*sqrt(M)[r])[r] + l[r])/k
*/
        return res;
    }

    inline LLLL &operator/=(LLLL &lhs, long long rhs){ return lhs = lhs / rhs; }

    inline LLLL operator%(LLLL lhs, long long rhs){
        long long hr = lhs.h%rhs, lr = lhs.l%rhs, srmr = LLLL_SR%rhs;
        LLLL res = {0, (hr > srmr)? (((hr*srmr)%rhs*srmr)%rhs + lr)%rhs
                                  : (hr*((srmr*srmr)%rhs) + lr)%rhs};
    /*
        (h*M+l)%k
        = ((kh[q]+h[r])*M + (kl[q]+l[r]))%k
        = (kh[q]*M + h[r]*M + kl[q] + l[r])%k
        = (h[r]*M + l[r])%k
        = (h[r]*(kM[q]+M[r]) + l[r])%k
        = (h[r]*kM[q] + h[r]*M[r] + l[r])%k
        = (h[r]*M[r] + l[r])%k
        = ((h[r]*M[r])[r] + l[r])%k
        = ((h[r]*(sqrt(M)*sqrt(M))[r])[r] + l[r])%k
        = (((h[r]*sqrt(M))[r]*sqrt(M)[r])[r] + l[r])%k
        = (((h[r]*sqrt(M)[r])[r]*sqrt(M)[r])[r] + l[r])%k
        = (((h[r]*sqrt(M)[r])[r]*sqrt(M)[r])[r] + l[r])%k
    */
        return res;
    }

    inline LLLL &operator%=(LLLL &lhs, long long rhs){ return lhs = lhs % rhs; }

    inline std::ostream &operator<<(std::ostream &lhs, LLLL const &rhs){
        if (rhs.h){
            return lhs<< rhs.h<< rhs.l;
        } else { return lhs<< rhs.l; }
    }
}

using namespace std;
using namespace LLLLL;

int main(){
    long long const M = 1000000007;
    int T, D, V;

    cin>> T;
    for (int x=1; x<=T; ++x){
        cin>> D>> V;

        LLLL y = {0, 1};
        if (D >= 1){ y += V%M, y%=M; }
        if (D >= 2){
            if (V == 1){
                LLLL tmp = {0, -1};
                y = tmp;
            } else if (V == 2){
                LLLL a1 = {0, (V%M*(V-1)%M)%M};
                y += ((D-1) * a1)%M, y%=M;
            } else {
                long long MP = M*(V-2);
                LLLL a1 = {0, (V%MP*(V-1)%MP)%MP}, b = {0, (V-1)%MP},
                     bn = {0, 1}, tmp = b;
                for (unsigned n=D-1; n; n >>= 1){
                    if (n&1){
                        if (bn *= tmp, bn.h < 0 || bn.l < 0) { cerr<< "bn: n="<< n<< '\n'; struct LLLLMulFailed{} e; throw e; }
                        if (bn %= MP, bn.h < 0 || bn.l < 0) { cerr<< "bn: n="<< n<< '\n'; struct LLLLModFailed{} e; throw e; }
                    }
                    if (tmp *= tmp, tmp.h < 0 || tmp.l < 0) { cerr<< "tmp: n="<< n<< '\n'; struct LLLLMulFailed{} e; throw e; }
                    if (tmp %= MP, tmp.h < 0 || tmp.l < 0) { cerr<< "tmp: n="<< n<< '\n'; struct LLLLModFailed{} e; throw e; }
                }
                y += (a1*((bn-1+MP)%MP))%MP / (V-2);
            }
        }

        cout<< "Case "<< x<< ": "<< y<< '\n';
    }
    return 0;
}
