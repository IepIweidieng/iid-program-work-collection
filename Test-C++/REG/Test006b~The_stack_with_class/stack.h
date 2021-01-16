#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include<iostream>
#include<sstream>
using namespace std;

class stack{
  private:
    int* pData;
    int index,size;
  public:
    stack(int n){
      if(n>0){
        index=0,size=n;
        pData=new int[n];
      }
    }
    ~stack(){
      delete [] pData;
    }
    bool push(int data){
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
        stringstream s("");
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

#endif //STACK_H_INCLUDED
