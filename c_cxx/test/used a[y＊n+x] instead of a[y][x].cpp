#include<cstdio>
#include<cstdlib>

const long long N = 1e3;

FILE *f;

void add(long long n, long long a[], long long b[], long long *c) {
  for(int y = 0; y < n; y++)
    for(int x = 0; x < n; x++)
      c[y*n+x] = a[y*n+x] + b[y*n+x];
}

void sub(long long n, long long a[], long long b[], long long *c) {
  for(int y = 0; y < n; y++)
    for(int x = 0; x < n; x++)
      c[y*n+x] = a[y*n+x] - b[y*n+x];
}

void mul(long long n, long long a[], long long b[], long long *c) {
  for(int y = 0; y < n; y++)
    for(int x = 0; x < n; x++)
      for(int z = 0; z < n; z++)
        c[y*n+x] += a[y*n+z] * b[z*n+x];
}

void strassen(long long n, long long a[], long long b[], long long *c) {
  if(n == 1) { c[0*n+0] = a[0*n+0] * b[0*n+0]; return; }

  long long a11[N], a12[N], a21[N], a22[N];
	long long b11[N], b12[N], b21[N], b22[N];
	long long c11[N], c12[N], c21[N], c22[N];
  long long aa[N], bb[N], m1[N], m2[N], m3[N], m4[N], m5[N], m6[N], m7[N];

  // partition a and b
  for(int y = 0; y < n/2; y++) for(int x = 0; x < n/2; x++) {
    a11[y*n/2+x] = a[y*n+x];
    b11[y*n/2+x] = b[y*n+x];
    a12[y*n/2+x] = a[y*n+n/2+x];
    b12[y*n/2+x] = b[y*n+n/2+x];
    a21[y*n/2+x] = a[(n/2+y)*n+x];
    b21[y*n/2+x] = b[(n/2+y)*n+x];
    a22[y*n/2+x] = a[(n/2+y)*n+n/2+x];
    b22[y*n/2+x] = b[(n/2+y)*n+n/2+x];
  }

  // compute m1 ~ m7
  add(n/2, a11, a22, aa); add(n/2, b11, b22, bb);
  strassen(n/2, aa, bb, m1);

  add(n/2, a21, a22, aa);
  strassen(n/2, aa, b11, m2);

  sub(n/2, b12, b22, bb);
  strassen(n/2, a11, bb, m3);

  sub(n/2, b21, b11, bb);
  strassen(n/2, a22, bb, m4);

  add(n/2, a11, a12, aa);
  strassen(n/2, aa, b22, m5);

  sub(n/2, a21, a11, aa); add(n/2, b11, b12, bb);
  strassen(n/2, aa, bb, m6);

  sub(n/2, a12, a22, aa); add(n/2, b21, b22, bb);
  strassen(n/2, aa, bb, m7);

  // combine c matrix
  add(n/2, m1, m4, aa), sub(n/2, aa, m5, bb), add(n/2, bb, m7, c11);
  add(n/2, m3, m5, c12);
  add(n/2, m2, m4, c21);
  add(n/2, m1, m3, aa), sub(n/2, aa, m2, bb); add(n/2, bb, m6, c22);

  for(int y = 0; y < n/2; y++) for(int x = 0; x < n/2; x++) {
    c[y*n+x] = c11[y*n/2+x];
    c[y*n+n/2+x] = c12[y*n/2+x];
    c[(n/2+y)*n+x] = c21[y*n/2+x];
    c[(n/2+y)*n+n/2+x] = c22[y*n/2+x];
  }
}

int main()
{
  long long n, A[N] = {}, B[N] = {}, C[N] = {}, D[N] = {};

  // input
  f = fopen("test1", "r");

  fscanf(f, "%lld%lld", &n, &n);
  for(int r = 0; r < n; r++)
    for(int c = 0; c < n; c++) fscanf(f, "%lld", &A[r*n+c]);

  fscanf(f, "%lld%lld", &n, &n);
  for(int r = 0; r < n; r++)
    for(int c = 0; c < n; c++) fscanf(f, "%lld", &B[r*n+c]);

  fclose(f);

  // traditional method
  f = fopen("output1", "w");

  for(int r = 0; r < n; r++) {
    for(int c = 0; c < n; c++) {
      for(int k = 0; k < n; k++) C[r*n+c] += A[r*n+k] * B[k*n+c];

      fprintf(f, "%lld ", C[r*n+c]);
    }
    fprintf(f, "\n");
  }

  fclose(f);

  // Strassen's algorithm
  f = fopen("output2", "w");

  strassen(n, A, B, D);

  for(int r = 0; r < n; r++) {
    for(int c = 0; c < n; c++) fprintf(f, "%lld ", D[r*n+c]);
    fprintf(f, "\n");
  }

  fclose(f);

  return 0;
}
