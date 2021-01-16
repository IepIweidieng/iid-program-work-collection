/*
A 32-bit counter implemented with C++ preprocessor, written by Iweidieng Iep on 2019-03-01.
Require C++11.

Rev.1 by Iweidieng Iep on 2019-03-01:
   Change the outputs to numbers instead of strings.
   Make the outputs to be in the same line.
   Wide the counter from 16 bits to 32 bits.
   Use inclusion level counter.
*/

#ifndef INITED
#define INITED

#include <iostream>

using namespace std;

int main()
{
    (cout << nounitbuf).sync_with_stdio(false);
    cin.tie(nullptr);

#define CAT_PRIME(x1, x0)  x1 ## x0
#define CAT(...)  CAT_PRIME(__VA_ARGS__)

#define CAT4_PRIME(x3, x2, x1, x0)  x3 ## x2 ## x1 ## x0
#define CAT4(...)  CAT4_PRIME(__VA_ARGS__)

#define HEX_0000  0
#define HEX_0001  1
#define HEX_0010  2
#define HEX_0011  3
#define HEX_0100  4
#define HEX_0101  5
#define HEX_0110  6
#define HEX_0111  7
#define HEX_1000  8
#define HEX_1001  9
#define HEX_1010  A
#define HEX_1011  B
#define HEX_1100  C
#define HEX_1101  D
#define HEX_1110  E
#define HEX_1111  F

#define HEX4(x3, x2, x1, x0) CAT(HEX_, CAT4(x3, x2, x1, x0))

#define HEX16(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2, x1, x0)  CAT4(HEX4(x15, x14, x13, x12), HEX4(x11, x10, x9, x8), HEX4(x7, x6, x5, x4), HEX4(x3, x2, x1, x0))

#define HEX32(x31, x30, x29, x28, x27, x26, x25, x24, x23, x22, x21, x20, x19, x18, x17, x16, x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2, x1, x0)  CAT(HEX16(x31, x30, x29, x28, x27, x26, x25, x24, x23, x22, x21, x20, x19, x18, x17, x16), HEX16(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2, x1, x0))

#define XHEX4(...)  CAT(0x, HEX4(__VA_ARGS__))
#define XHEX32(...)  CAT(0x, HEX32(__VA_ARGS__))

#define K  K31, K30, K29, K28, K27, K26, K25, K24, K23, K22, K21, K20, K19, K18, K17, K16, K15, K14, K13, K12, K11, K10, K9, K8, K7, K6, K5, K4, K3, K2, K1, K0

#define TOP
#define LEVEL  L3, L2, L1, L0
#define RESET_L
#define RESET_K

#endif  // INITED


#ifdef RESET_L
#undef RESET_L

#undef L0
#undef L1
#undef L2
#undef L3

#define L0  0
#define L1  0
#define L2  0
#define L3  0

#endif  // RESET_L


#ifdef RESET_K
#undef RESET_K

#undef K0
#undef K1
#undef K2
#undef K3
#undef K4
#undef K5
#undef K6
#undef K7
#undef K8
#undef K9
#undef K10
#undef K11
#undef K12
#undef K13
#undef K14
#undef K15
#undef K16
#undef K17
#undef K18
#undef K19
#undef K20
#undef K21
#undef K22
#undef K23
#undef K24
#undef K25
#undef K26
#undef K27
#undef K28
#undef K29
#undef K30
#undef K31

#define K0  0
#define K1  0
#define K2  0
#define K3  0
#define K4  0
#define K5  0
#define K6  0
#define K7  0
#define K8  0
#define K9  0
#define K10  0
#define K11  0
#define K12  0
#define K13  0
#define K14  0
#define K15  0
#define K16  0
#define K17  0
#define K18  0
#define K19  0
#define K20  0
#define K21  0
#define K22  0
#define K23  0
#define K24  0
#define K25  0
#define K26  0
#define K27  0
#define K28  0
#define K29  0
#define K30  0
#define K31  0

#endif  // RESET_K

// Increase `LEVEL` by 1
#if L0 == 0
  #undef L0
  #define L0  1
#else
  #undef L0
  #define L0  0
  #if L1 == 0
    #undef L1
    #define L1  1
  #else
    #undef L1
    #define L1  0
    #if L2 == 0
      #undef L2
      #define L2  1
    #else
      #undef L2
      #define L2  0
      #if L3 == 0
        #undef L3
        #define L3  1
      #else
        #undef L3
        #define L3  0
      #endif
    #endif
  #endif
#endif

#if defined TOP
  #undef TOP
  #define RESET_L
  #include __FILE__
  #include __FILE__
  #include __FILE__
  #include __FILE__
  #define TOP
#elif XHEX4(LEVEL) != 0x8
  #include __FILE__
  #include __FILE__
  #include __FILE__
  #include __FILE__
#else

    cout << '\r' << XHEX32(K);

// Increase `K` by 1
#if K0 == 0
  #undef K0
  #define K0  1
#else
  #undef K0
  #define K0  0
  #if K1 == 0
    #undef K1
    #define K1  1
  #else
    #undef K1
    #define K1  0
    #if K2 == 0
      #undef K2
      #define K2  1
    #else
      #undef K2
      #define K2  0
      #if K3 == 0
        #undef K3
        #define K3  1
      #else
        #undef K3
        #define K3  0
        #if K4 == 0
          #undef K4
          #define K4  1
        #else
          #undef K4
          #define K4  0
          #if K5 == 0
            #undef K5
            #define K5  1
          #else
            #undef K5
            #define K5  0
            #if K6 == 0
              #undef K6
              #define K6  1
            #else
              #undef K6
              #define K6  0
              #if K7 == 0
                #undef K7
                #define K7  1
              #else
                #undef K7
                #define K7  0
                #if K8 == 0
                  #undef K8
                  #define K8  1
                #else
                  #undef K8
                  #define K8  0
                  #if K9 == 0
                    #undef K9
                    #define K9  1
                  #else
                    #undef K9
                    #define K9  0
                    #if K10 == 0
                      #undef K10
                      #define K10  1
                    #else
                      #undef K10
                      #define K10  0
                      #if K11 == 0
                        #undef K11
                        #define K11  1
                      #else
                        #undef K11
                        #define K11  0
                        #if K12 == 0
                          #undef K12
                          #define K12  1
                        #else
                          #undef K12
                          #define K12  0
                          #if K13 == 0
                            #undef K13
                            #define K13  1
                          #else
                            #undef K13
                            #define K13  0
                            #if K14 == 0
                              #undef K14
                              #define K14  1
                            #else
                              #undef K14
                              #define K14  0
                              #if K15 == 0
                                #undef K15
                                #define K15  1
                              #else
                                #undef K15
                                #define K15  0
                                #if K16 == 0
                                  #undef K16
                                  #define K16  1
                                #else
                                  #undef K16
                                  #define K16  0
                                  #if K17 == 0
                                    #undef K17
                                    #define K17  1
                                  #else
                                    #undef K17
                                    #define K17  0
                                    #if K18 == 0
                                      #undef K18
                                      #define K18  1
                                    #else
                                      #undef K18
                                      #define K18  0
                                      #if K19 == 0
                                        #undef K19
                                        #define K19  1
                                      #else
                                        #undef K19
                                        #define K19  0
                                        #if K20 == 0
                                          #undef K20
                                          #define K20  1
                                        #else
                                          #undef K20
                                          #define K20  0
                                          #if K21 == 0
                                            #undef K21
                                            #define K21  1
                                          #else
                                            #undef K21
                                            #define K21  0
                                            #if K22 == 0
                                              #undef K22
                                              #define K22  1
                                            #else
                                              #undef K22
                                              #define K22  0
                                              #if K23 == 0
                                                #undef K23
                                                #define K23  1
                                              #else
                                                #undef K23
                                                #define K23  0
                                                #if K24 == 0
                                                  #undef K24
                                                  #define K24  1
                                                #else
                                                  #undef K24
                                                  #define K24  0
                                                  #if K25 == 0
                                                    #undef K25
                                                    #define K25  1
                                                  #else
                                                    #undef K25
                                                    #define K25  0
                                                    #if K26 == 0
                                                      #undef K26
                                                      #define K26  1
                                                    #else
                                                      #undef K26
                                                      #define K26  0
                                                      #if K27 == 0
                                                        #undef K27
                                                        #define K27  1
                                                      #else
                                                        #undef K27
                                                        #define K27  0
                                                        #if K28 == 0
                                                          #undef K28
                                                          #define K28  1
                                                        #else
                                                          #undef K28
                                                          #define K28  0
                                                          #if K29 == 0
                                                            #undef K29
                                                            #define K29  1
                                                          #else
                                                            #undef K29
                                                            #define K29  0
                                                            #if K30 == 0
                                                              #undef K30
                                                              #define K30  1
                                                            #else
                                                              #undef K30
                                                              #define K30  0
                                                              #if K31 == 0
                                                                #undef K31
                                                                #define K31  1
                                                              #else
                                                                #undef K31
                                                                #define K31  0
                                                              #endif
                                                            #endif
                                                          #endif
                                                        #endif
                                                      #endif
                                                    #endif
                                                  #endif
                                                #endif
                                              #endif
                                            #endif
                                          #endif
                                        #endif
                                      #endif
                                    #endif
                                  #endif
                                #endif
                              #endif
                            #endif
                          #endif
                        #endif
                      #endif
                    #endif
                  #endif
                #endif
              #endif
            #endif
          #endif
        #endif
      #endif
    #endif
  #endif
#endif

#endif  // !defined TOP && XHEX4(LEVEL) == 0x8


// Decrease `LEVEL` by 1
#if L0 == 1
  #undef L0
  #define L0  0
#else
  #undef L0
  #define L0  1
  #if L1 == 1
    #undef L1
    #define L1  0
  #else
    #undef L1
    #define L1  1
    #if L2 == 1
      #undef L2
      #define L2  0
    #else
      #undef L2
      #define L2  1
      #if L3 == 1
        #undef L3
        #define L3  0
      #else
        #undef L3
        #define L3  1
      #endif
    #endif
  #endif
#endif


#ifdef TOP

    cout << '\r' << XHEX32(K) << '\n';

    return 0;
}
#endif  // TOP
