#include <iostream>

using namespace std;

int main(){
    int n, m;
    cin>> n>> m;

    char *str = new char[n+1];
    cin>> str;

    while (m--){
        int l, r;
        char c1, c2;

        cin>> l>> r>> c1>> c2;

        for (int k = l-1; k!=r; ++k){
            if (str[k] == c1){
                str[k] = c2;
            }
        }
    }

    cout<< str<< '\n';

    delete[] str;
    return 0;
}
