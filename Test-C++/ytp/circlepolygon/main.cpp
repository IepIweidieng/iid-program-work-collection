#include <iostream>
#include <cmath>

using namespace std;

int main(){
    cout.setf(ios::fixed);
    cout.precision(3);

    int N, L;
    long double pi = acos(-1);
    while (cin>> N>> L){
        cout<< sqrt(L*L/(long double)2/((long double)1-cos(2*pi/(long double)N)))<< endl;
    }

    return 0;
}
