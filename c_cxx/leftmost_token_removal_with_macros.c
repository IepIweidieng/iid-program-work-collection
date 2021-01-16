/*
Leftmost token removal using macros,
   written by Iweidieng Iep on 2019-04-04,
   needing ISO C90 / ISO C++98 or newer standards.
*/
/* Example:
```
REMOVE_PARENED((X) (Y))  // (Y)
REMOVE_PARENED((X))  // (X)

REMOVE_TOKEN(X Y)  // X Y
#define REMOVE_TOKEN_X  REMOVE_T
REMOVE_TOKEN(X Y)  // Y
```
*/

#include <stdio.h>

/* Select the first argument */
#define SELECT_0_PRIME(x0, x1)  x0
#define SELECT_0(x0, x1)  SELECT_0_PRIME(x0, x1)

/* Select the second argument */
#define SELECT_1_PRIME(x0, x1)  x1
#define SELECT_1(x0, x1)  SELECT_1_PRIME(x0, x1)

/* Change a `SELECT_1()` to `SELECT_0()` */
/* Usage:
SELECT_1(REMOVE_T x0, x1)
   => SELECT_1(_, SELECT_0)(x0, x1)
   => SELECT_0(x0, x1)
   => x0
*/
#define REMOVE_T  _, SELECT_0)(

/*
Remove leftmost token if the token is specified to remove.
Do nothing if the token is not specified to remove.

To specify a token to remove, define `REMOVE_TOKEN_[the token]`.

(Assume `#define REMOVE_TOKEN_struct  REMOVE_T`)
REMOVE_TOKEN(struct X)
   => SELECT_1(REMOVE_TOKEN_struct X, struct X)
   => SELECT_1(_, SELECT_0)(X, struct X)
   => SELECT_0(X, struct X)
   => X

REMOVE_TOKEN(X)
   => SELECT_1(REMOVE_TOKEN_X, X)
   => X
*/

#define REMOVE_TOKEN_PRIME(x)  SELECT_1(REMOVE_TOKEN_##x, x)
#define REMOVE_TOKEN(x)  REMOVE_TOKEN_PRIME(x)

/*
Remove leftmost token from two or more parenthesised tokens if the token is parenthesised.
Do nothing if the argument has only 1 parenthesised token, or the token is not parenthesised.

REMOVE_PARENED((X) (X))
   => SELECT_1(REMOVE_PARENED_IGN(X) (X), (X) (X))
   => SELECT_1(REMOVE_PARENED_(X), (X) (X))
   => SELECT_1(_, SELECT_0)((X), (X) (X))
   => SELECT_0((X), (X) (X))
   => X

REMOVE_PARENED((X))
   => SELECT_1(REMOVE_PARENED_IGN(X), (X))
   => SELECT_1(REMOVE_PARENED_, (X))
   => X
*/

#define REMOVE_PARENED(x)  SELECT_1(REMOVE_PARENED_IGN x, x)
#define REMOVE_PARENED_IGN(x)  REMOVE_PARENED_
#define REMOVE_PARENED_(x)  REMOVE_T(x)

#define STR_PRIME(x)  #x
#define STR(x)  STR_PRIME(x)

int main(void)
{
#define TEST(type, x)  "REMOVE_" #type "(" STR(x) ") => " STR(REMOVE_##type(REMOVE_##type(x))) "\n"

    fputs(" -= Token removal test =-\n", stdout);
#define TEST_TOKEN(x)  TEST(TOKEN, x)
    fputs("* Remove `struct`: \n", stdout);
#define REMOVE_TOKEN_struct  REMOVE_T
    fputs(
        TEST_TOKEN(X)  // X
        TEST_TOKEN(union X)  // union X
        TEST_TOKEN(struct X)  // X
        TEST_TOKEN(union struct X)  // union struct X
        TEST_TOKEN(struct union X)  // union X
        TEST_TOKEN(struct struct X)  // X
        "\n",
      stdout);

    fputs("* Do not remove `struct`: \n", stdout);
#undef REMOVE_TOKEN_struct
    fputs(
        TEST_TOKEN(X)  // X
        TEST_TOKEN(union X)  // union X
        TEST_TOKEN(struct X)  // struct X
        TEST_TOKEN(union struct X)  // union struct X
        TEST_TOKEN(struct union X)  // struct union X
        TEST_TOKEN(struct struct X)  // struct struct X
        "\n",
      stdout);
#undef TEST_TOKEN

    fputs(" -= Parenthesised token removal test =-\n", stdout);
#define TEST_PARENED(x)  TEST(PARENED, x)
    fputs(
        TEST_PARENED((0))  // (0)
        TEST_PARENED((int) (3))  // (3)
        TEST_PARENED((int) (unsigned int) (42))  // (42)
        "\n",
      stdout);
#undef TEST_PAREN

#undef TEST

    return 0;
}
