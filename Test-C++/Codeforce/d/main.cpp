#include <iostream>

using namespace std;

int main(){
    int n, m, c, *papers, *ph, *psum;
    cin>> n>> m>> c;

    papers = new int[n]();
    ph = new int[c]();
    psum = new int[c]();

    while (m--){
        int pi, res;
        cin>> pi;

        s = (n*(pi-1))/c;
        if (papers[s]){
            if (pi<papers[s])

        }

        papers[s]=pi;

        cout<< res<< endl;
    }


    delete[] papers;
    return 0;
}
