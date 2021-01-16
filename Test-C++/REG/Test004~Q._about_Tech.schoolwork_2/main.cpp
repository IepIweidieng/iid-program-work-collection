#include<iostream>
#include<string>
using namespace std;
int MbN;

main(){
 cout<<"請問組員數量？";
 cin>>MbN;
 string st[MbN*2];
 string *ss=st;
 cout<<endl;
 for(int i=0;i<MbN;i++){
  for(int r=0;r<2;r++){
   cin>>*(ss+i*2+r);
  }
  cout<<endl;
 }
 for(int i=0;i<MbN*2;i+=2){
  cout<<*(ss+i)<<" "<<*(ss+i+1)<<endl;
 }
}
