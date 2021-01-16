#include <iostream>
using namespace std;
string* stack=NULL;
int size=0,sizeI=0,index=0;

string* CreateStack(int _size){
  if(stack!=NULL){
    cout<<"Error: There's already a stack."<<endl;
    return NULL;
  }
  if(_size<=0){
    cout<<"Error: The stack is too small."<<endl;
    return NULL;
  }
  size=_size;index=0;
  return new string[size];
}
bool IfFull(){
  if(index>=size){
    return true;
  }else{
    return false;
  }
}
bool IfEmpty(){
  if(index<=0){
    return true;
  }else{
    return false;
  }
}
void DeleteStack(){
  if(stack==NULL){
    cout<<"Error: There's no stack."<<endl;
    return;
  }
  delete [] stack;
  stack=NULL;
}
string* Push(int value){
  if(IfFull()){
    cout<<"=>The stack is full."<<endl;
    return NULL;
  }
  stack[index]=value;
  index++;
  return &stack[index-1];
}
string* Pop(){
  if(IfEmpty()){
    cout<<"=>The stack is empty."<<endl;
    return NULL;
  }
  index--;
  return &stack[index];
}
string* Top(){
  if(IfEmpty()){
    cout<<"=>The stack is empty."<<endl;
    return NULL;
  }
  return &stack[index-1];
}
void ShowStack(){
  cout<<"Stack:";
  for(int i=0;i<index;i++){
    cout<<" "<<stack[i];
  }
  cout<<endl;
}

int main(){
  cout<<"Please enter the size of the stack you want: ";
  cin>>sizeI;
  stack=CreateStack(sizeI);
  if(stack==NULL){
    cout<<"Error: Failed to create the stack."<<endl;
    return 1;
  }else{
    cout<<"=>The "<<size<<"-spaced stack has been created successfully."<<endl;
  }
  string* Output=NULL;
  int Input=0,PKeeper=1;
  while(PKeeper){
    cout<<"Please choice an action (1.push in; 2.pop out; 3.show out stack; 4.exit): ";
    cin>>Input;
    switch (Input){
      case 1:
        Output=Push(0);
        if(Output!=NULL){
          cout<<"Please enter a string: ";
          cin>>*Output;
          cout<<"=>The string "<<*Output<<" has been pushed into the stack."<<endl;
        }
        break;
      case 2:
        Output=Pop();
        if(Output!=NULL){cout<<"=>The string "<<*Output<<" has been pop out of the stack."<<endl;}
        break;
      case 3:
        ShowStack();
        break;
      case 4:
        PKeeper=0;
        break;
      default:
        cout<<"Error: The action you choiced doesn't exist."<<endl;
    }
  }
  DeleteStack();
  cout<<"=>The stack memory has been released; the program will be end."<<endl;
  return 0;
}
