#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false), cin.tie((ostream *)NULL), cout.unsetf(ios_base::unitbuf);
    unsigned int a, b, q, r, res, cur;

    while (cin>> a>> b){
        for (q=a, r=b; (q%=r)&& (r%=q););
        a/=q+r, b/=q+r;

        for (res=0, cur=1; b>1; cur<<=a/b, res|=cur, a%=b, swap(a, b));
        cur<<=a/b-1, res|=cur;

        cout<< res<< '\n';
    }

    cout.flush();
    return 0;
}
