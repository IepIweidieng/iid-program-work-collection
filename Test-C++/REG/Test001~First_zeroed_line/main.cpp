//終於完成了，但這一行可有可無。
#include <iostream>
using namespace std;
int i,j,n;int a=-1;
int main(){
cin>>n;
int *l=new int[n];int *s=new int[n];
for(i=0;i<n;i++){
for(j=0;j<n;j++){cin>>*(s+j);}
for(j=0;j<n;j++){
if(*(s+j)){*(l+i)=0;break;}
else{*(l+i)=1;}}}
for(i=0;i<n;i++){if(*(l+i)){a=i;break;}}
cout<<a;
delete[]s;delete[]l;}
