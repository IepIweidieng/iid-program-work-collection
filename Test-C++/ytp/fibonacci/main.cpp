#include <iostream>

using namespace std;

int main(){
    uint64_t F0, F1, F2, *Pl, *Pr, *Pf, *Pt;
    int N;

    cin>> N;
    if (N < 2){cout<< N<< endl; return 0;}

    F0 = 0, F1 = 1;
    Pl = &F2, Pr = &F0, Pf = &F1;
    for (int k = 2; k <= N; ++k){
        Pt = Pl, Pl = Pr, Pr = Pf, Pf = Pt;
        *Pf = *Pl + *Pr;
    }
    cout<< *Pf<< endl;

    return 0;
}
