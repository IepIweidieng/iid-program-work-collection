/* malloc_test.c
Automagically generate casting of `*alloc()` result using macro
   for GNU C++ and ISO C++11
Note: Parsing `malloc(sizeof(<typename>))` and the alike
   requires GNU extensions (supported by GCC and Clang).

Written by Iweidieng Iep on 2019-08-25
Rev.1 by Iweidieng Iep on 2019-08-25:
   Fix inclusion error;
      `std::decay<>` is defined in <type_traits> header, not <utility>
Rev.2 by Iweidieng Iep on 2019-08-25:
   `simplied` -> `simplified`: Fix a typo in a comment
   Make function macro `CPP_NOT_EMPTY_PROBE` variadic
   `main()`: Add comments for expressions requiring GNU extensions in C++
*/

#include <stdlib.h>

#if __cplusplus
  #if !defined __GNUC__ && __cplusplus >= 201103L
    #include <type_traits>
    #define __typeof__(x)  std::decay<decltype(x)>::type
    // Note: decltype(<typename>) is invalid, unlike gcc __typeof__
  #endif

  #define CPP_NOOP(...)  __VA_ARGS__
  #define CPP_SELECT_2(_1, _2, ...)  _2
  #define CPP_CAT(x, y)  x##y
  #define CPP_DEFER(f, args)  f args  // Disabled inside `ALLOC_CAST_GEN`
  #define CPP_DEFER2(f, args)  f args  // Disabled inside `ALLOC_PARSE_INNER_ARG`
  #define CPP_DEFER3(f, args)  f args  // Disabled inside `CPP_EMPTY_OR_OP`
  #define CPP_EMPTY_OR_OP(arg, op)  \
      CPP_DEFER3(CPP_SELECT_2, ( \
          CPP_DEFER3(CPP_CAT, (CHECK_, CPP_NOT_EMPTY_PROBE CPP_NOOP(arg) (CPP, PROBE))), op,) \
      ) (arg)  // Note: This is a simplified implement;
               //       `arg` should not start with a open parenthesis,
               //          and should not end with a function-like macro.
  #define CPP_PROBE(x)  , x,
  #define CHECK_CPP_NOT_EMPTY_PROBE(_1, _2)  _1##_##_2(CPP_NOOP)
  #define CPP_NOT_EMPTY_PROBE(...)

  #define malloc(x)  ALLOC_CAST_GEN(x) (malloc)(x)
  // Note: Do not use the type of `ptr`, since it can be `NULL` (`(int)0` in C++)
  #define realloc(ptr, x)  ALLOC_CAST_GEN(x) (realloc)(ptr, x)
  #define calloc(n, x)  ALLOC_CAST_GEN(x) (calloc)(n, x)

  #define ALLOC_CAST_GEN(x)  CPP_DEFER(ALLOC_PARSE_INNER_ARG, (ALLOC_INNER_##x,,))
  #define ALLOC_INNER(x)  , ALLOC_PTR_CAST(x),
  #define ALLOC_PARSE_INNER_ARG(res_arg, inner_arg, ...)  \
      CPP_DEFER2(ALLOC_PARSE_RESARG, (CPP_NOOP(RESARG_##res_arg,,))) inner_arg
  #define RESARG_ALLOC_INNER  ,
  #define ALLOC_PARSE_RESARG(_ign, res_arg, ...)  \
      CPP_EMPTY_OR_OP(res_arg, ALLOC_PTR_CAST)
  #define ALLOC_PTR_CAST(x)  (__typeof__(x) *)

  #define ALLOC_INNER_sizeof  ALLOC_INNER
  #define RESARG_ALLOC_INNER_sizeof  RESARG_ALLOC_INNER
  // To support other `sizeof`-like size operators and (macro) functions,
  //    define both `ALLOC_INNER_*` and `RESARG_ALLOC_INNER_*` as above
#endif

int main(void)
{
    int *a = (int *) malloc(4 * 1);  // Still need an explicit cast
    int *b = malloc(sizeof(*b));
    int *k = malloc(sizeof(*k) * 1);
    // char *m = malloc(sizeof *m * 1);  // `int*` taken; type error
    char *n = malloc(sizeof *n);
    int *q = malloc(sizeof(int) * 1);  // Need GNU extensions

    a = (int *) realloc(a, 4 * 1);
    b = realloc(b, sizeof(*b));
    k = realloc(k, sizeof(*k) * 1);
    n = realloc(n, sizeof *n);
    q = realloc(q, sizeof(int) * 1);  // Need GNU extensions

    free(a), free(b), free(k), /* free(m), */ free(n), free(k), free(q);

    a = (int *) calloc(1, 4 * 1);
    b = calloc(1, sizeof(*b));
    k = calloc(1, sizeof(*k) * 1);
    n = calloc(1, sizeof *n);
    q = calloc(1, sizeof(int) * 1);  // Need GNU extensions

    free(a), free(b), free(k), /* free(m), */ free(n), free(k), free(q);
    return 0;
}
