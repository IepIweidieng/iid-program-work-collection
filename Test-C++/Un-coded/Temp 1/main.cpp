#include <iostream>
#include <stack>

using namespace std;

struct mate{
    long double weight;
    short obj, num, deep;
};

int main(){
    ios_base::sync_with_stdio(false), cin.tie((ostream *)NULL), cout.setf(ios::unitbuf);
    cout.unsetf(ios_base::floatfield);

    stack<mate> dfs;
    mate cur;
    long double expect;
    short N, *C, possible;
    char in;

    while (cin>> N){
        expect = 0.0L;
        C = new short[N]();

        for (short k = 0, n = N*N; k < n && cin>> in; ++k){
            if (in == 'Y'){C[k/N] |= 1<<(k%N);}
        }

        mate C1 = {1.0L, short(((1<<N)-1) & ~1), 0, 1};
        dfs.push(C1);
        while (!dfs.empty()){
            cur = dfs.top();
            dfs.pop();

            if (!(C[cur.num] & cur.obj)){
                expect += cur.weight * cur.deep;
            } else {
                possible = 0;
                for (short k = C[cur.num] & cur.obj; k && ++possible; k &= k-1);
                cur.weight /= (long double)possible;

                possible = C[cur.num] & cur.obj;

                for (short k = 0; k < N; ++k){
                    if (possible & (1<<k)){
                        mate Ci = {cur.weight, short(cur.obj & ~(1<<k)), k, short(cur.deep+1)};
                        dfs.push(Ci);
                    }
                }
            }
        }
        if (short(expect) == expect){
            cout<< short(expect)<< ".0\n";
        } else {
            if (expect >= 10.0L){
                cout.precision(5);
            } else {
                cout.precision(4);
            }
            cout<< short(expect * 1000) * 0.001L<< '\n';
        }
    }

    return 0;
}
