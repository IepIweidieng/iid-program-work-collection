#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct dfsu{
    unsigned long long kd:60;
    unsigned int n:17;
    unsigned char ep:2;
};

int main(){
    ios_base::sync_with_stdio(false),
      cin.tie((ostream*)NULL),
      cout.unsetf(ios_base::unitbuf);

    string const f[4] = {"What are you doing at the end of the world? Are you busy? Will you save us?",
                         "What are you doing while sending \"",
                         "\"? Are you busy? Will you send \"",
                         "\"?"};
    long long const fz[4] = {f[0].length(),
                             f[1].length(),
                             f[2].length(),
                             f[3].length()};
    int const fc = sizeof(fz)/sizeof(fz[0]);
    int q;
    cin>> q;

    while (q--){
        stack<dfsu> dfs;
        dfsu tmp;
        long long k, *dp;
        int n;
        unsigned char type;

        cin>> n>> k;
        dp = new long long[n+1]();
        k-=1;

        tmp.kd = k, tmp.n = n, tmp.ep = 0, dfs.push(tmp);
        while (!dfs.empty()){
            dfsu &ind = dfs.top();
           if (ind.n){
                for (type = ind.ep+1; type<fc; ++type){
                    k -= fz[type];
                    if (k>=0){
                        if (type < fc-1){
                            if (dp[ind.n-1] && k-dp[ind.n-1] >= 0){
                                k -= dp[ind.n-1];
                            } else {
                                ind.ep = type, tmp.kd = k, tmp.n = ind.n-1, dfs.push(tmp);
                                goto dfs_continue;
                            }
                        }
                    } else {goto dfs_end;}
                }
            } else {
                type = 0;
                k -= fz[type];
                if (!(k>=0)){goto dfs_end;}
            }
            dp[ind.n] = ind.kd-k;
            dfs.pop();
          dfs_continue:;
        }
      dfs_end:
        if (k>=0){
            cout<< '.';
        } else {
            cout<< f[type][k+fz[type]];
        }
    }

    cout<< '\n';

    return 0;
}
