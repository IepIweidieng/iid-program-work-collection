#include<iostream>
#include<sstream>
#include<string>
using namespace std;

void dex_to_binn(string& input,char* output,int& ob){
  istringstream iss(input);
  int iN;
  iss>>iN;
  unsigned oFliter=1;
  for(int i=1;i<ob;i++){
    oFliter<<=1;
    oFliter++;
  }
  int j=32%ob,k=32/ob-1;
  if(j){k++;}
  bool nZ=false;
  for(int i=k;i>=0;i--){
    if(iN&(oFliter<<(i*ob))){nZ=true;cout<<output[(iN&(oFliter<<(i*ob)))>>(i*ob)];
    }else if(nZ){cout<<output[0];
    }
  }
  cout<<endl<<endl;
}

void binn_to_dex(string& input,char* output,int& ib,int& ob){
  int oN=0,j=input.size();
  for(int i=0;i<j;i++){
    int k=input[i]-'0';
    if(input[i]>='A'){k=input[i]-'A'+10;}
    if(input[i]>='a'){k=input[i]-'a'+36;}
    oN+=k<<((j-1-i)*ib);
  }
  if(ob){
    stringstream ss;
    ss<<oN;
    string ioN=ss.str();
    dex_to_binn(ioN,output,ob);
  }else{cout<<oN<<endl<<endl;
  }
}

bool getb(int& b){
  string input;
  while(getline(cin,input)){
    if(input==""){continue;}
    if(input=="10"){b=0;return true;}
    if(input[0]!='2'||input[1]!='^'){cerr<<"錯誤："<<input<<" 進制不受支援"<<endl<<endl;return false;}
    int j=input.size();
    input.assign(input,2,j-2);
    if(input==""){cerr<<"錯誤：\"^\" 是二元運算子，請輸入 n 值"<<endl<<endl;return false;}
    if(input=="n"){cerr<<"錯誤：請以數字代替 n"<<endl<<endl;return false;}
    istringstream iss(input);
    if(!(iss>>b)){cerr<<"錯誤："<<input<<" 不是正確的 n 值"<<endl<<endl;return false;}
    if(b>6){cerr<<"錯誤："<<(1<<b)<<" 進制不受支援"<<endl<<endl;return false;}
    if(b==0){cerr<<"錯誤："<<(1<<b)<<" 進制僅能表示等於 0 的數"<<endl<<endl;return false;}
    if(b<0){cerr<<"錯誤：2^"<<b<<" 進制僅能表示小於 3 的非負數"<<endl<<endl;return false;}
    return true;
  }
  cin.clear();
  return false;
}

int main(){
  string input;
  int ib,ob;
  char output[64];
  char outc='0';
  bool LKeeper=true;
  for(int i=0;i<64;i++){
    if(i==10){outc='A';}
    if(i==36){outc='a';}
    output[i]=outc;
    outc++;
  }
  while(LKeeper){
    while(1){
      cout<<"請輸入要輸入的數值的進制（10 或 2^n）：";
      if(getb(ib)){break;}
    }
    cout<<endl;
    while(1){
      cout<<"請輸入要輸出的數值的進制（10 或 2^n）：";
      if(getb(ob)){break;}
    }
    cout<<endl;
    while(1){
      bool iCorrect=false;
      if(ib==0){cout<<"請輸入一個 10 進制數值：";
      }else{cout<<"請輸入一個 "<<(1<<ib)<<" 進制數值：";
      }
      getline(cin,input);
      if(ib==0){
        for(unsigned i=0;i<input.size();i++){
          iCorrect=true;
          if((input[i]<'0'||input[i]>'9')&&(i!=0||input[i]!='-')){
            iCorrect=false;
            cerr<<"錯誤："<<input<<" 不是一個正確的 10 進制數值"<<endl<<endl;
            break;
          }
        }
      }else{
        for(unsigned i=0;i<input.size();i++){
          iCorrect=true;
          if(!((input[i]>='0'&&input[i]<='9')||(input[i]>='A'&&input[i]<='Z')||(input[i]>='a'&&input[i]<='|'))||(input[i]>output[(1<<ib)-1])){
            iCorrect=false;
            cerr<<"錯誤："<<input<<" 不是一個正確的 "<<(1<<ib)<<" 進制數值"<<endl;
            break;
          }
        }
      }
      if(iCorrect){break;}
      cin.clear();
    }
    if(ib==ob){cout<<input<<endl<<endl;
    }else if(ib==0){dex_to_binn(input,output,ob);
    }else{binn_to_dex(input,output,ib,ob);
    }
    while(1){
      cout<<"請選擇動作（C－繼續；E－離開）：";
      getline(cin,input);
      if(input[0]=='C'||input[0]=='c'){break;}
      if(input[0]=='E'||input[0]=='e'){LKeeper=false;break;}
      cin.clear();
    }
    cout<<endl;
  }
  return 0;
}
