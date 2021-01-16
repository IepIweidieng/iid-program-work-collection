#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false), cin.tie((ostream *)NULL), cout.setf(ios::unitbuf);
    typedef long double LD;
    typedef unsigned long UL;
    cout.precision(1024);

    LD a, b;
    UL exp;
    cin>> a>> b>> exp;

    for (UL i={0}; i<=exp; ++i){
      LD * aa={new LD[i+1] ()};
      aa[0]=1;

      for (UL j={1}; j<=i; ++j){
          for (UL k={j}; k; --k){
              aa[k]*=b, aa[k]+=a*aa[k-1];
          }
          aa[0]*=b;
      }

      for (UL j={i}; j; --j){
          cout<< aa[j]<< ' ';
      }
      cout<< aa[0]<< '\n';

      delete[] aa;
    }

    return 0;
}
