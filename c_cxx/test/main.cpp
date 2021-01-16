#include<cstdio>
#include<cstdlib>

long long const N = 5000, R = 19*N*N/3;
long long array[4*N*N+R], *ptr = array;

FILE *f;

long long max(long long lhs, long long rhs) {
  if (rhs >= lhs) { return rhs; }
  else { return lhs; }
}

long long *add(long long n, long long a[], long long b[], long long *c) {
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n; ++x)
      c[y*n+x] = a[y*n+x] + b[y*n+x];

  return c;
}

long long *sub(long long n, long long a[], long long b[], long long *c) {
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n; ++x)
      c[y*n+x] = a[y*n+x] - b[y*n+x];

  return c;
}

long long *mul(long long n, long long a[], long long b[], long long *c) {
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n; ++x) {
      c[y*n+x] = 0;
      for (int z = 0; z < n; ++z)
        c[y*n+x] += a[y*n+z] * b[z*n+x];
    }

  return c;
}

long long *strassen(long long n, long long a[], long long b[], long long *c) {
  if(n == 1) { c[0*n+0] = a[0*n+0] * b[0*n+0]; return c; }

  static long long *&d = ptr;
  long long dn=0, s=n*n/4;

  long long *a11 = d+(dn++)*s, *a12 = d+(dn++)*s, *a21 = d+(dn++)*s, *a22 = d+(dn++)*s;
  long long *b11 = d+(dn++)*s, *b12 = d+(dn++)*s, *b21 = d+(dn++)*s, *b22 = d+(dn++)*s;
  long long *c11 = d+(dn++)*s, *c12 = d+(dn++)*s, *c21 = d+(dn++)*s, *c22 = d+(dn++)*s;
  long long *m1 = d+(dn++)*s, *m2 = d+(dn++)*s, *m3 = d+(dn++)*s, *m4 = d+(dn++)*s, *m5 = d+(dn++)*s, *m6 = d+(dn++)*s, *m7 = d+(dn++)*s;
  long long *aa = d+(dn++)*s, *bb = d+(dn++)*s;

  d += dn*s;

  // partition a and b
  for (int y = 0; y < n/2; ++y) for (int x = 0; x < n/2; ++x) {
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
  strassen(n/2, add(n/2, a11, a22, aa), add(n/2, b11, b22, bb), m1);
  strassen(n/2, add(n/2, a21, a22, aa), b11, m2);
  strassen(n/2, a11, sub(n/2, b12, b22, bb), m3);
  strassen(n/2, a22, sub(n/2, b21, b11, bb), m4);
  strassen(n/2, add(n/2, a11, a12, aa), b22, m5);
  strassen(n/2, sub(n/2, a21, a11, aa), add(n/2, b11, b12, bb), m6);
  strassen(n/2, sub(n/2, a12, a22, aa), add(n/2, b21, b22, bb), m7);

  // combine c matrix
  add(n/2, sub(n/2, add(n/2, m1, m4, aa), m5, bb), m7, c11);
  add(n/2, m3, m5, c12);
  add(n/2, m2, m4, c21);
  add(n/2, sub(n/2, add(n/2, m1, m3, aa), m2, bb), m6, c22);

  for (int y = 0; y < n/2; ++y) for (int x = 0; x < n/2; ++x) {
    c[y*n+x] = c11[y*n/2+x];
    c[y*n+n/2+x] = c12[y*n/2+x];
    c[(n/2+y)*n+x] = c21[y*n/2+x];
    c[(n/2+y)*n+n/2+x] = c22[y*n/2+x];
  }

  d -= dn*s;

  return c;
}

int main()
{
  long long mA, nA, mB, nB, n, s;
  long long *A = ptr, *B = (long long*)NULL, *C = (long long*)NULL, *D = (long long*)NULL;

  // input
  f = fopen("test1", "r");

  fscanf(f, "%lld%lld", &mA, &nA);
  if (mA < 0 || nA < 0) { struct ArrayNegativeSize{} e; throw e; }
  B = (ptr += mA*nA);

  for (int r = 0; r < mA; ++r)
    for (int c = 0; c < nA; ++c) fscanf(f, "%lld", &A[r*nA+c]);

  fscanf(f, "%lld%lld", &mB, &nB);
  if (mA < 0 || nA < 0) { struct ArrayNegativeSize{} e; throw e; }
  C = (ptr += mB*nB);

  for (int r = 0; r < mB; ++r)
    for (int c = 0; c < nB; ++c) fscanf(f, "%lld", &B[r*nB+c]);

  fclose(f);

  if (nA != mB) { struct ArrayNotMultipliable{} e; throw e; }

  // traditional method
  f = fopen("output1", "w");

  for (int r = 0; r < mA; ++r)
    for (int c = 0; c < nB; ++c) {
      C[r*nB+c] = 0;
      for (int k = 0; k < nA; ++k)
          C[r*nB+c] += A[r*nA+k] * B[k*nB+c];
    }

  for (int r = 0; r < mA; ++r) {
    for (int c = 0; c < nB; ++c) fprintf(f, "%lld ", C[r*nB+c]);
    fprintf(f, "\n");
  }

  fclose(f);

  for (n = max(max(max(mA, nA), mB), nB), ((n & (n-1)) != 0) && (n<<=1); (n & (n-1)) != 0; n &= n-1);
  s = n*n;

  ptr = array + 3*s;
  D = ptr;
  
  ptr -= s;
  for (int r = mA-1; r >= 0; --r) {
    for (int c = nB-1; c >= 0; --c) {
      if (r < mA && c < nB) { ptr[r*n+c] = C[r*nB+c]; }
      else if (r == c) { ptr[r*n+c] = 1; }
      else { ptr[r*n+c] = 0; }
    }
  }
  C = ptr;
  
  ptr -= s;
  for (int r = mB-1; r >= 0; --r) {
    for (int c = nB-1; c >= 0; --c) {
      if (r < mB && c < nB) { ptr[r*n+c] = B[r*nB+c]; }
      else if (r == c) { ptr[r*n+c] = 1; }
      else { ptr[r*n+c] = 0; }
    }
  }
  B = ptr;
 
  ptr -= s;
  for (int r = mA-1; r >= 0; --r) {
    for (int c = nA-1; c >= 0; --c) {
      if (r < mA && c < nA) { ptr[r*n+c] = A[r*nA+c]; }
      else if (r == c) { ptr[r*n+c] = 1; }
      else { ptr[r*n+c] = 0; }
    }
  }
  A = ptr;

  f = fopen("output2", "w");

  ptr += 4*s;
  strassen(n, A, B, D);

  for (int r = 0; r < mA; ++r) {
    for (int c = 0; c < nB; ++c) fprintf(f, "%lld ", D[r*n+c]);
    fprintf(f, "\n");
  }

  fclose(f);

  return 0;
}
