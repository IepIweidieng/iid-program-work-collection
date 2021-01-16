//2016-9-27. Original version, by Iep Iweidieng.
//2016-9-28. Reversion 1, by Iep Iweidieng.
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct family{
  vector<family*> near;
  size_t lines(){return this->near.size();}
  friend inline void link(family &lhs, family &rhs){
    lhs.near.push_back(&rhs),
      rhs.near.push_back(&lhs);
  }
};

struct bpsl{
  family * pos,
         *bpos;
  size_t  step;
  bpsl(family * pos=NULL,
       family *bpos=NULL,
       size_t  step=0  ): pos( pos           ),
                         bpos(bpos? bpos: pos),
                         step(step           ){}
};

int main(){
  ios_base::sync_with_stdio(false),
    cin.tie(NULL), cout.unsetf(ios::unitbuf);
  string trash;
  size_t n;

  cin>> n, getline(cin, trash);

  family *const &mems(new family[n]);
  for (size_t i={0}, a, b; i<n-1; ++i){
    cin>> a>> b, getline(cin, trash),
    link(mems[a], mems[b]);
  }

  intmax_t *const &max_d(new intmax_t[n]);
  fill(&max_d[0], &max_d[n], -1);

  queue<bpsl> bps;
  for (size_t i={0}; i<n; ++i)
    if (mems[i].lines()==1)
      bps.push(bpsl(&mems[i]));

  bpsl cur;
  for (size_t mems_ind, mems_bind, posst_t; !bps.empty();){
    cur=bps.front(), bps.pop(),
      mems_ind=cur.pos-&mems[0],
      mems_bind=cur.bpos-&mems[0],
      posst_t=cur.pos->lines();
    if ((bps.size()!=1||cur.step>max_d[mems_bind])&&
        cur.step>max_d[mems_ind]){
      max_d[mems_ind]=cur.step;
    } else {continue;}
    if (cur.step&& (posst_t==1|| cur.step>=n)) continue;
    for (size_t i={0}; i<posst_t; ++i)
      if (cur.pos->near[i]!=cur.bpos)
        bps.push(bpsl(cur.pos->near[i], cur.pos, cur.step+1));
  }
  cout<< (cur.step==n? 1/float(0): cur.step)<< endl;

  delete[] mems, delete[] max_d;
  return 0;
}