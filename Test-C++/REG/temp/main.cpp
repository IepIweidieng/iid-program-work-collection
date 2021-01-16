int main(){
  unsigned long long int n;
  cin>>n;
}

unsigned long long int GCD(unsigned long long int a, unsigned long long int b){
  if (b==0){return a;}
  return GCD(b, a%b);
}

bool N2(unsigned long long int n){
if(n%3=2%3){return false;}
unsigned long double l=(1/2)log[3](n),r=log[2](l);
g[0]=1,s[0]=2
for(int m=1; m<=r; m++){
  g[m]%(3^2^m)=(s[m-1](g[m-1]-g[m-1]^2-n))%(3^2^m);
  s[m]%(3^2^m)=(2s[m-1]-2g[m-1]s[m-1]^2)%(3^2^m);
}
g%(3^l)=g[r-1]-s[r-1](g[r-1]^2-n)%(3^l);
if(g^2==n){return true;}
if((3^l-g)^2==n){return true;}
return false;
}

bool Nd(unsigned long long int n){
l=(1/d)log(n),r=log(l);
g[0]=1,s[0]=1;
for(int m=1, m<=r, m++){
  g[m]%(2^2^m)=s[m-1](g[m-1]-g[m-1]^d-n)%2^2^m;
  s[m]%(2^2^m)=2s[m-1]-(d-1)g[m-1]^(d-1)s[m-1]^2;
}
g%(2^l)=g[r-1]-s[r-1](g[r-1]^d-n)%2^l;
if(g^d==n){return true;}
return false;
}

bool IsPrime(unsigned long long int n){
  if (n%2==0%2){return false;}
  if (n%3==0%3){return false;}
  for (int d=3; d<(1/2)log(n); d+=2){
    if(Nd(n)==true){return false;}
  }
  r=log(n)^2;
  while(1){
    for(int t=1; t<log(n)^2; t++){
      if(n^t%r==1){r=r+1;t=1;}
    }
    break;
  }
  for (int a=3; a<=r, a++){
    if (GCD(a,n)>1&& GCD(a,n)<n){return false;}
  }
  if (n<r){return true;}
  h=0;
  for (int q=1; q<r; q++){
    if (GCD(q,r)==1){h=h+1;}
  }
  for (int c=1; c<h^(1/2)log(n); c++){
    (((X+c)^n)%(X^r-1)%n!=((X^n)+c)%(X^r-1)%n){false;}
  }
  return true;
}

 double power (double a, unsigned int n)
 {
      double y = 1;
      double f = a;
      unsigned int k = n;
      while (k != 0) {
         if (k % 2 == 1) y *= f;
         k >>= 1;
         f *= f;
      }
      return y;
 }
