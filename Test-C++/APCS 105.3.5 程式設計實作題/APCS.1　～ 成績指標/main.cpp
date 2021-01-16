//2016.9.27 by Iep Iweidieng.
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.unsetf(ios::unitbuf);
  string trash;
  size_t N;

  cin>> N, getline(cin, trash);

  short(&score)(*new short[N]);
  for (size_t i={0}; i<N; ++i) cin>> (&score)[i];
  sort(&score, &score+N);

  for (size_t i={0}; i+1<N; ++i) cout<< (&score)[i]<< ' ';
  cout<< (&score)[N-1]<< '\n';

  if ((&score)[0]>=60) cout<< "best case";
  else for (size_t i={N-1}; i>=0&& !((&score)[i]<60&& (cout<< (&score)[i], ~0)); --i);
  cout<< '\n';

  if ((&score)[N-1]<60) cout<< "worst case";
  else for (size_t i={0}; i<N&& !((&score)[i]>=60&& (cout<< (&score)[i], ~0)); ++i);
  cout<< '\n';

  delete[] &score;
  cout.flush();
  return 0;
}