#include"stack.h"
using namespace std;

string typeI;
string typeIC[5];
short PKeeper=0;
int TICL=0;

int main(){
  while(PKeeper==0){
    for(int i=0;i<5;i++){
      typeIC[i]="";
    }
    cout<<"Please enter the type of the stack you want (enter \"exit\" to exit): ";
    for(string InputLine;getline(cin,InputLine);){
      for(unsigned int i=0;i<InputLine.length();i++){
        if(InputLine[i]>='A'&&InputLine[i]<='Z'){
          InputLine[i]-='A'-'a';
        }
      }
      istringstream Input(InputLine);
      Input>>typeIC[0]>>typeIC[1]>>typeIC[2]>>typeIC[3];
      break;
    }
    for(int i=4;i>=0;i--){
      if(typeIC[i]==""){TICL=i;}
    }
    raise(typeIC,"long",TICL);
    raise(typeIC,"unsigned",TICL);
    typeI=typeIC[0];
    for(int i=1;i<TICL;i++){
      typeI=typeI+" "+typeIC[i];
    }
     /*E*/ if(typeI=="bool"                         ){UI<bool>              (typeI,PKeeper,false,nGetData<bool>);
    }else if(typeI=="char"  /* There are  */        ){UI<char>               (typeI,PKeeper,'\0',nGetData<char>);
   }else if(typeI=="wchar_t"   /*  three curves! */ ){UI<wchar_t>             (typeI,PKeeper,'\0',wGetData<wchar_t>);
   }else if(typeI=="string"                        ){UI<string>                (typeI,PKeeper,"",sGetData<string>);
  }else if(typeI=="short"                          ){UI<short>                  (typeI,PKeeper,0,nGetData<short>);
  }else if(typeI=="unsigned short"                ){UI<unsigned short>          (typeI,PKeeper,0,nGetData<unsigned short>);
  }else if(typeI=="int"                          ){UI<int>                       (typeI,PKeeper,0,nGetData<int>);
   }else if(typeI=="unsigned int"               ){UI<unsigned int>               (typeI,PKeeper,0,nGetData<unsigned int>);
   }else if(typeI=="long"                      ){UI<long>  /* Perfect curves! */ (typeI,PKeeper,0,nGetData<long>);
    }else if(typeI=="long int"                 ){UI<long int>    /*   （？） */ (typeI,PKeeper,0,nGetData<long int>);
     }else if(typeI=="unsigned long"          ){UI<unsigned long>               (typeI,PKeeper,0,nGetData<unsigned long>);
      }else if(typeI=="unsigned long int"     ){UI<unsigned long int>          (typeI,PKeeper,0,nGetData<unsigned long int>);
       }else if(typeI=="long long"            ){UI<long long>                 (typeI,PKeeper,0,nGetData<long long>);
       }else if(typeI=="long long int"         ){UI<long long int>           (typeI,PKeeper,0,nGetData<long long int>);
        }else if(typeI=="unsigned long long"   ){UI<unsigned long long>     (typeI,PKeeper,0,nGetData<unsigned long long>);
        }else if(typeI=="unsigned long long int"){UI<unsigned long long int>(typeI,PKeeper,0,nGetData<unsigned long long int>);
        }else if(typeI=="float"                  ){UI<float>               (typeI,PKeeper,0,nGetData<float>);
       }else if(typeI=="double"                   ){UI<double>             (typeI,PKeeper,0,nGetData<double>);
       }else if(typeI=="long double"               ){UI<long double>       (typeI,PKeeper,0,nGetData<long double>);
      }else if(typeI=="exit"                       ){PKeeper=1                ;
     }else{
      cerr<<"Error: Unsupported data type \""<<typeI<<"\""<<endl;
   }
  }
  if(PKeeper==1){
    cout<<"=>The program is ending."<<endl;
  }else if(PKeeper==-1){
    cout<<"=>The stack memory has been released; the program is ending."<<endl;
  }else{
    cerr<<"A crucial error has occurred; the program is aborted."<<endl;
    return PKeeper-1;
  }
}
