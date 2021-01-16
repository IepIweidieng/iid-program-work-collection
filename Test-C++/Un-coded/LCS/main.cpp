#include <iostream>
#include <stack>
#include <set>
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
template<class ty> struct array_2d{
    array_2d(size_t _x, size_t _y):
      x (_x), y (_y), p (*new ty[x*y]()){}
    ~array_2d(){delete[] &p; }
 //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
    ty * operator[](size_t _x){return &(&p)[_x*y]; }
 //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
    size_t x, y;
    ty & p;
};
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
struct LCS_cell{size_t len; char sup; };
enum super{UP_LEFT=1<<0, LEFT=1<<1, UP=1<<2};
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
struct DFS_cur{
    size_t cur[3];
    size_t & operator[](size_t ind){return cur[ind]; }
};
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
int main(){
    using namespace std;
    ios_base::sync_with_stdio(false),
    cin.tie((ostream *)NULL),
    cout.unsetf(ios::unitbuf);
 {{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}}
    string X, Y;
    while (getline(cin, X)&& getline(cin, Y)){
        size_t m={X.length()}, n={Y.length()};
        array_2d<LCS_cell> LCS(m+1, n+1);
     {{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}}
        {
            for (size_t i={1}; i<=m; ++i){
                for (size_t j={1}; j<=n; ++j){
                    if (X[i-1]==Y[j-1]){
                        LCS[i][j].len=LCS[i-1][j-1].len+1,
                        LCS[i][j].sup|=UP_LEFT;
                        continue;
                    }
                    if (LCS[i-1][j].len>=LCS[i][j-1].len){
                        LCS[i][j].len=LCS[i-1][j].len,
                        LCS[i][j].sup|=UP;
                    }
                    if (LCS[i][j-1].len>=LCS[i-1][j].len){
                        LCS[i][j].len=LCS[i][j-1].len,
                        LCS[i][j].sup|=LEFT;
                    }
                }
            }
        }
     {{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}}
        cout<< LCS[m][n].len<< '\n';
     {{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}}
        set<string> result;
        {
            string res_cur;
            {
                string temp(" ");
                for (size_t i={1}, j=LCS[m][n].len;
                     i&& i<=j; i*=2){
                    if (j&i){res_cur+=temp;}
                    temp+=temp;
                }
            }
            stack<DFS_cur> DFS;
            DFS_cur cur={m, n, res_cur.length()-1};
            char sup;
            enum cur_attr{XI, YJ, SEEKER};
         {{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}}
            DFS.push(cur);
            while (!DFS.empty()){
                cur=DFS.top(), DFS.pop(),
                sup=LCS[cur[XI]][cur[YJ]].sup;
                if (!cur[XI]|| !cur[YJ]){
                    result.insert(res_cur);
                    continue;
                }
                if (sup&UP_LEFT){
                    res_cur[cur[SEEKER]]=X[cur[XI]-1];
                    --cur[XI], --cur[YJ], --cur[SEEKER],
                    DFS.push(cur);
                    continue;
                }
                if (sup&LEFT){
                    --cur[YJ], DFS.push(cur), ++cur[YJ];
                }
                if (sup&UP){
                    --cur[XI], DFS.push(cur), ++cur[XI];
                }
            }
        }
     {{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}}
        for (set<string>::iterator it(result.begin());
             it!=result.end(); ++it){
            cout<< *it<< '\n';
        }
 //     cout<< flush;
    }
 {{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}{{}}}
    cout<< flush;
    return 0;
}