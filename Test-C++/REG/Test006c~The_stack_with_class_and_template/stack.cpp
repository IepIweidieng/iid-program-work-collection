#include"stack.h"
using namespace std;

void raise(string* typeIC,string s,int TICL){
  for(int i=0;i<TICL;i++){
    if(typeIC[i]==s){
      for(int j=TICL;j>0;j--){
        typeIC[j]=typeIC[j-1];
      }
      typeIC[0]=typeIC[i+1];
      for(int j=i+1;j<TICL;j++){
        typeIC[j]=typeIC[j+1];
      }
    }
  }
}
