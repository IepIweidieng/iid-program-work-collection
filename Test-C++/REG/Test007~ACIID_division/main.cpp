#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;
int main(){
LARGE_INTEGER QPF;
QueryPerformanceFrequency(&QPF);
  string sa, sb;
  unsigned N, size, asize, bsize, Msz;
  while (cin>>sa>>sb>>N){
stringstream dqCMcase ("");
string dqCMc;
LARGE_INTEGER exeT, finT, exeI, finI, exeO, finO, exe, fin;
unsigned dqM (0), dqCM (0), dqCT (0);
QueryPerformanceCounter(&exeT);
QueryPerformanceCounter(&exeI);
    stringstream rInt (""),rDcm (""),*rslt (&rInt);
    bool size_a_E (false), size_b_E (false);
    if (1){
      unsigned k (sa.size());
      if (k&3){k=(k>>2)+1;} else {k>>=2;}
      unsigned l (sb.size());
      if (l&3){l=(l>>2)+1;} else {l>>=2;}
      for (unsigned i (1), j=1<<30; i<=j; i<<=1){
        if (i>k&& i>l){
          size=i;
          Msz=size-1;
          break;
        }
        if (i==j){
          size_a_E=(i<=k);
          size_b_E=(i<=l);
        }
      }
    }
    if (size_a_E&& size_b_E){QueryPerformanceCounter(&finI);cerr<< "Error: Both the dividend \""<< sa<< "\" and the divisor \""<< sb<< "\" are too long\n";
    } else if (size_a_E){QueryPerformanceCounter(&finI);cerr<< "Error: The dividend \""<< sa<< "\" is too long\n";
    } else if (size_b_E){QueryPerformanceCounter(&finI);cerr<< "Error: The divisor \""<< sb<< "\" is too long\n";
    } else {
      int *a (new int[size]()), *b (new int[size]()), apc (0), bpc (0);
      bool a_equ_0 (true), b_equ_0 (true);
      for (unsigned i (0);i<size;i++){
        if (sa==""&& sb==""){break;}
        string ta, tb;
        if (sa!=""){
          if (sa.size()>=4){ta.assign(sa, (sa.size()-4), 4); sa.assign(sa, 0, (sa.size()-4));} else {ta=sa; sa="";}
          istringstream issa(ta);
          issa>>a[i];
          if (a[i]){a_equ_0=false;}
          asize=i;
        }
        if (sb!=""){
          if (sb.size()>=4){tb.assign(sb, (sb.size()-4), 4); sb.assign(sb, 0, sb.size()-4);} else {tb=sb; sb="";}
          istringstream issb(tb);
          issb>>b[i];
          if (b[i]){b_equ_0=false;}
          bsize=i;
        }
      }
QueryPerformanceCounter(&finI);
      if (a_equ_0&& b_equ_0){QueryPerformanceCounter(&exe); QueryPerformanceCounter(&fin); cout<< "An undefined complex"<< endl;
      } else if (b_equ_0){QueryPerformanceCounter(&exe); QueryPerformanceCounter(&fin); cout<< "Infinity"<< endl;
      } else {
QueryPerformanceCounter(&exe);
        while (bsize<asize){bpc++; bsize++;}
        bsize+=size;
        int Nc (N>>2);
        bool q_neq_0 (false),r (true);
        if (N&3){Nc++;}
        while (apc-bpc<=Nc){
          int ap (apc&Msz), bp (bpc&Msz), q (0);
          unsigned dq (0);
unsigned dqC (0);
dqCMcase.str("");
dqCMcase.clear();
dqCMcase<< "apc: "<< apc<< ", bpc: "<< bpc<< ", apc-bpc: "<< apc-bpc<< "\na: ";
for (unsigned i ((size<<1)-1); i>=size; i--){
  if (((i-ap)&Msz)==((bsize-ap)&Msz)){dqCMcase<< "(bsize)";}
  dqCMcase<< a[(i-ap)&Msz]<< ", ";
}
dqCMcase<< "\nb: ";
for (unsigned i ((size<<1)-1); i>=size; i--){
  if (((i-bp)&Msz)==((bsize-bp)&Msz)){dqCMcase<< "(bsize)";}
  dqCMcase<< b[(i-bp)&Msz]<< ", ";
}
dqCMcase<< '\n'; //For debugging
          while (true){
            dq=(a[(bsize+1-ap)&Msz]*10000+a[(bsize-ap)&Msz])/b[(bsize-bp)&Msz];
dqC++;
dqCT+=1;
if (dqC>dqCM){
    dqCM=dqC;
    dqCMc=dqCMcase.str();
}
            if (r&& dq==1){
              bool a_geq_b (true);
              for (unsigned i (bsize+1); i>=size; i--){
                if (a[(i-ap)&Msz]!=(b[(i-bp)&Msz])){
                  if (a[(i-ap)&Msz]<(b[(i-bp)&Msz])){a_geq_b=false;}
                  break;
                }
              }
              if (a_geq_b){
                for (unsigned i (size); i<bsize+1; i++){
                  a[(i-ap)&Msz]-=b[(i-bp)&Msz];
                  a[(i+1-ap)&Msz]+=a[(i-ap)&Msz]/10000;
                  a[(i-ap)&Msz]%=10000;
                  if (a[(i-ap)&Msz]<0){a[(i+1-ap)&Msz]-=1; a[(i-ap)&Msz]+=10000;}
                }
                q++;
              }
              break;
            }
            if (dq==0){break;}
            if (r){dq--;}
/*¡u*/      for (unsigned i (((bsize-1)&Msz)+size); i>=size; i--){
/*©}*/        if (b[(i-bp)&Msz]){
/*­ì*/          unsigned temq ((a[(i+1-ap)&Msz]*10000+a[(i-ap)&Msz])/b[(i-bp)&Msz]);
/*¡v*/          if (temq&& temq<dq){dq=temq;}
/*¸Ñ*/        }
/*--*/      }
//º®//      if (b[(size-bp)&Msz]){
//¤Ò//       unsigned temq ((a[(size+1-ap)&Msz]*10000+a[(size-ap)&Msz])/b[(size-bp)&Msz]);
//¸Ñ//       if (temq&& temq<dq){dq=temq;}
//--//      }
if (dq>dqM){dqM=dq;}
            for (unsigned i (size); i<bsize+1; i++){
              a[(i-ap)&Msz]-=b[(i-bp)&Msz]*dq;
              a[(i+1-ap)&Msz]+=a[(i-ap)&Msz]/10000;
              a[(i-ap)&Msz]%=10000;
              if (a[(i-ap)&Msz]<0){a[(i+1-ap)&Msz]-=1; a[(i-ap)&Msz]+=10000;}
            }
            if (r){q+=dq;} else {q-=dq;}
            bool a_h_lss_0 (false);
            for (unsigned i (bsize+1-ap); i>=size-ap; i--){
              if (a[i&Msz]){
                if (a[i&Msz]<0){a_h_lss_0=true;}
                break;
              }
            }
            if (a_h_lss_0){
              for (unsigned i (size-ap); i<bsize+1-ap; i++){
                a[(i+1)&Msz]+=a[i&Msz]/10000;
                a[i&Msz]%=10000;
                if (a[i&Msz]>0){a[(i+1)&Msz]+=1; a[i&Msz]-=10000;}
                a[i&Msz]*=-1;
              }
              r=!r;
            }
          }
          a_equ_0=true;
          for (unsigned i (size-ap); i<=bsize+1-ap; i++){
            if (a[i&Msz]){a_equ_0=false; break;}
          }
          if (!(r|| a_equ_0)){
            for (unsigned i (size); i<bsize+1; i++){
              a[(i-ap)&Msz]-=b[(i-bp)&Msz];
              a[(i+1-ap)&Msz]+=a[(i-ap)&Msz]/10000;
              a[(i-ap)&Msz]%=10000;
              if (a[(i-ap)&Msz]>0){a[(i+1-ap)&Msz]+=1; a[(i-ap)&Msz]-=10000;}
              a[(i-ap)&Msz]*=-1;
            }
            q--;
            r=!r;
          }
          if (q_neq_0){
            if (q<1000){*rslt<< '0';}
            if (q<100){*rslt<< '0';}
            if (q<10){*rslt<< '0';}
            *rslt<< q;
          } else if (q|| bpc==apc){
            q_neq_0=true;
            *rslt<< q;
          }
          if (bpc==apc&& N>0){rslt=&rDcm; *rslt<< '.';}
          if (bpc){bpc--; bsize=((bsize-1)&Msz)+size;} else {apc++;}
        }
QueryPerformanceCounter(&fin);
QueryPerformanceCounter(&exeO);
        string srDcm (rDcm.str());
        if (N>0){srDcm.resize(N+1);} else {srDcm="";}
        cout<< rInt.str()<< srDcm<< endl;
QueryPerformanceCounter(&finO);
      }
      delete[] a;
      delete[] b;
    }
QueryPerformanceCounter(&finT);
long double QPT (1000/static_cast<long double>(QPF.QuadPart));
ios DefaultCout (0);
DefaultCout.copyfmt(cout);
cout<< fixed<< setprecision(10)<<
 left<< "Total duration: "<< setw(29)<< right<< QPT*(finT.QuadPart-exeT.QuadPart)<< " ms\n"<<
 left<< "Input processing duration: "<< setw(18)<< right<< QPT*(finI.QuadPart-exeI.QuadPart)<< " ms\n"<<
 left<< "Output processing duration: "<< setw(17)<< right<<QPT*(finO.QuadPart-exeO.QuadPart)<< " ms\n"<<
 left<< "Calculation duration: "<< setw(23)<< right<< QPT*(fin.QuadPart-exe.QuadPart)<< " ms\n"<<
 setprecision(6)<<
 left<< "The largest quotient taken: "<< setw(6)<< right<< dqM<< "\n"<<
 left<< "The maximum count: "<< setw(15)<< right<< dqCM<< "\n"<<
 left<< "The sum of count: "<< setw(16)<< right<< dqCT<< "\n"<<
 left<< "The worst situation: "<< dqCMc<< endl;
cout.copyfmt(DefaultCout);
  }
}
