//2016.9.27 by Iep Iweidieng.
#include <iostream>
#include <algorithm>
using namespace std;

struct between{
  typedef int32_t(uid);
  uid lhs, rhs;
  between(uid lhs, uid rhs):lhs(lhs), rhs(rhs){}
  bool operator()(uid val){return lhs<=val&& rhs>=val;}
};
int main(){
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.unsetf(ios::unitbuf);
  typedef int32_t(uid);
  string trash;
  uid N;

  cin>> N, getline(cin, trash);

  uid &srs(*new uid[N+1]), &dest(*new uid[N+1]);
  for (uid i={0}; i<N; ++i) cin>> (&srs)[i]>> (&dest)[i], getline(cin, trash);
  sort(&(&srs)[0], &(&srs)[N]), sort(&(&dest)[0], &(&dest)[N]);
  (&srs)[N]=(&srs)[N-1], (&dest)[N]=(&dest)[N-1];

  uid sum={0};
  for (uid *scur(&(&srs)[0]), *mcur(scur), *fcur, *dcur(&(&dest)[0]); dcur<&(&dest)[N]; ++dcur){
    fcur=find_if(mcur+1, &(&srs)[N], between(*mcur, *dcur)),
      (fcur==&(&srs)[N])? (sum+=*dcur-*scur, scur=++mcur): mcur=fcur;
  }
  cout<< sum<< endl;

  delete[] &srs, delete[] &dest;
  return 0;
}