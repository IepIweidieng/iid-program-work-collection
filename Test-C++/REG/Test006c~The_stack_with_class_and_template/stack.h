#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

void raise(string* typeIC,string s,int TICL);

template<class Type>class stack{
  private:
    Type* pData;
    int index,size;
  public:
    stack(int n){
      if(n>0){
        index=0,size=n;
        pData=new Type[n];
      }
    }
    ~stack(){
      delete [] pData;
    }
    bool push(Type data){
      if(!isFull()){
        pData[index]=data;
        index++;
        return true;
      }
      return false;
    }
    bool pop(){
      if(!isEmpty()){
        index--;
        return true;
      }
      return false;
    }
    string top(){
      if(!isEmpty()){
        ostringstream s("");
        s<<pData[index-1];
        return s.str();
      }
      return "";
    }
    bool isEmpty(){
      if(index>0){return false;}else{return true;}
    }
    bool isFull(){
      if(index<size){return false;}else{return true;}
    }
    void show(){
      cout<<"[Bottom]->";
      for(int i=0;i<index;i++){cout<<pData[i]<<"->";}
      cout<<"[Top]"<<endl;
    }
  protected:
};

template<class Type>Type nGetData(Type& IDI){
  string InputLine;
  Type InputData(IDI);
  while(getline(cin,InputLine)){
    istringstream Input(InputLine);
    Input>>InputData;
    break;
  }
  return InputData;
}

template<class Type>Type wGetData(Type& IDI){
  wstring InputLine;
  Type InputData(IDI);
  while(getline(wcin,InputLine)){
    wistringstream Input(InputLine);
    Input>>InputData;
    break;
  }
  return InputData;
}

template<class Type>Type sGetData(Type& IDI){
  Type InputData(IDI);
  getline(cin,InputData);
  return InputData;
}

template<class UIType>void UI(string& typeI,short& PKeeper,UIType IDI,UIType (*GD)(UIType&)){
  int sizeI=0;
  while(sizeI<=0){
    cout<<"Please enter the size of the stack you want: ";
    for(string InputLine;getline(cin,InputLine);){
      istringstream Input(InputLine);
      Input>>sizeI;
      break;
    }
    if(sizeI<=0){
      cerr<<"Error: Invalid integer "<<sizeI<<endl;
    }
  }
  stack<UIType>S(sizeI);
  cout<<"=>The "<<sizeI<<"-spaced "<<typeI<<" stack has been created."<<endl;
  string Output="";
  char method='0';
  PKeeper=1;
  while(PKeeper){
    cout<<"Please choice a method (1.push; 2.pop; 3.show; 4.exit): ";
    for(string InputLine;getline(cin,InputLine);){
      method=InputLine[0];
      break;
    }
    switch (method){
      case '1':
        if(S.isFull()){
          cerr<<"=>The stack is full."<<endl;
        }else{
          cout<<"Please enter a "<<typeI<<": ";
          UIType InputData(GD(IDI));
          if(S.push(InputData)){
            cout<<"=>The "<<typeI<<" \""<<InputData<<"\" has been pushed into the stack."<<endl;
          }else{
            cerr<<"Error: Failed to push "<<typeI<<" \""<<InputData<<"\" into the stack"<<endl;
          }
        }
        PKeeper=1;
        break;
      case '2':
        Output=S.top();
        if(S.pop()){
          cout<<"=>The "<<typeI<<" \""<<Output<<"\" has been pop out of the stack."<<endl;
        }else if(Output==""){
          cerr<<"=>The stack is empty."<<endl;
        }else{
          cerr<<"=>The stack is empty."<<endl;
        }
        break;
      case '3':
        S.show();
        break;
      case '4':
        PKeeper=0;
        break;
      default:
        cout<<"Error: Invalid method \""<<method<<"\""<<endl;
    }
  }
  PKeeper=-1;
  return;
}

#endif //STACK_H_INCLUDED
