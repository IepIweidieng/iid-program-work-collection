//2016.9.27 by Iep Iweidieng.
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.unsetf(ios::unitbuf);
  string trash;
  short R, C, M, state;
  bool RF, CF;

  cin>> R>> C>> M, getline(cin, trash);

  short &B(*new short[R*C]);
  for (short i={0}; i<R; ++i){
    for (short j={0}; j<C; ++j) cin>> (&(&B)[i*C])[j];
    getline(cin, trash);
  }

  short &Ms(*new short[M]);
  for (short i={0}; i<M; ++i) cin>> (&Ms)[i];

  for (short i((state=0, RF=CF=false, M-1)); i>=0; --i){
    (&Ms)[i]? (state%2? CF: RF)^=true: state=(state+1)%4;
  }
  if (CF){
    for (short j={0}; j<C/2; ++j) for (short k={0}; k<R; ++k) swap((&(&B)[k*C])[j], (&(&B)[k*C])[C-1-j]);
  }
  if (RF){
    for (short j={0}; j<R/2; ++j) swap_ranges(&(&B)[j*C], &(&B)[(j+1)*C], &(&B)[(R-1-j)*C]);
  }

  switch (state){
    case 0:{
      cout<< R<< ' '<< C<< '\n';
      for (short i={0}; i<R; ++i){
        for (short j={0}; j+1<C; ++j) cout<< (&(&B)[i*C])[j]<< ' ';
        cout<< (&(&B)[i*C])[C-1]<< '\n';
      }
      break;
    }
    case 1:{
      cout<< C<< ' '<< R<< '\n';
      for (short i={0}; i<C; ++i){
        for (short j={0}; j+1<R; ++j) cout<< (&(&B)[C-1-i])[j*C]<< ' ';
        cout<< (&(&B)[C-1-i])[(R-1)*C]<< '\n';
      }
      break;
    }
    case 2:{
      cout<< R<< ' '<< C<< '\n';
      for (short i={0}; i<R; ++i){
        for (short j={0}; j+1<C; ++j) cout<< (&(&B)[(R-1-i)*C])[C-1-j]<< ' ';
        cout<< (&(&B)[(R-1-i)*C])[0]<< '\n';
      }
      break;
    }
    case 3:{
      cout<< C<< ' '<< R<< '\n';
      for (short i={0}; i<C; ++i){
        for (short j={0}; j+1<R; ++j) cout<< (&(&B)[i])[(R-1-j)*C]<< ' ';
        cout<< (&(&B)[i])[0*C]<< '\n';
      }
      break;
    }
  }

  delete[] &B, delete[] &Ms;
  cout.flush();
  return 0;
}