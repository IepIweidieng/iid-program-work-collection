#include <iostream>

using namespace std;

int main(){
    int k, p, sum=0;
    cin>> k>> p;

    for (int m=1; m<=k; ++m){
        long long palindrome = m;
        int om=m;

        while (om){
            palindrome*=10, palindrome+=om%10;
            om/=10;
        }

        sum+=palindrome%p, sum%=p;
    }

    cout<< sum<< '\n';
    return 0;
}
