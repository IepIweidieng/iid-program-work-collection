#include <iostream>
using namespace std;
int main(){
  char on[16];
  for(int i=0,j=48;i<16;i++){
    on[i]=j;
    j==57?j=65:j++;
  }
  int i16;
  cin>>i16;
  if(i16==0){
    cout<<'0';
  }else{
    int cn=1;
    if(i16<0){
      cout<<'-';
      i16*=-1;
    }
    if(i16>=268435456){
      cout<<on[i16/268435456];
      i16%=268435456;
      cn=268435456;
    }else{
      while(cn<=i16){
        cn*=16;
      }
    }
    while(1){
      cn/=16;
      if(!cn){break;}
      cout<<on[i16/cn];
      i16%=cn;
    }
  }
  cout<<endl;
  return 0;
}
