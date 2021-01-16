/* listlit_test.cpp
This shows the differences
   between C99 compound literal
      and C++11 list initialization casted to lvalue.
Written by Iweidieng Iep on 2020-03-01.

The code conforms to ISO C99.
It compiles with ISO C++11 but causes undefined behaviors.
 */

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
template <class T>
using Identity = T;
#define LISTLIT(Type, ...) Identity<Type> __VA_ARGS__
#define TEMPLVAL(Type, ...) \
    (Identity<Type> &) (const Identity<Type> &) LISTLIT(Type, __VA_ARGS__)
#else
#define LISTLIT(Type, ...) (Type) __VA_ARGS__
#define TEMPLVAL(Type, ...) LISTLIT(Type, __VA_ARGS__)
#endif

typedef struct FuncArg {
    intmax_t (*func)(const void *);
    const void *arg;
} FuncArg;

intmax_t print_int(const void *arg)
{
    return printf("%d", *(const int *) arg);
}

static FuncArg *ans_ptr =
    &TEMPLVAL(FuncArg, {&print_int, &TEMPLVAL(int, {42})});
static FuncArg *ans_arr =
    TEMPLVAL(FuncArg[1], {&print_int, TEMPLVAL(int[1], {42})});

int main(void)
{
    FuncArg *ans_auto_arr =
        TEMPLVAL(FuncArg[1], {&print_int, TEMPLVAL(int[1], {42})});
    fputs("stack arr: ", stdout);
    fflush(stdout);
    ans_auto_arr->func(ans_auto_arr->arg);

    fputs(", static arr: ", stdout);
    fflush(stdout);
    ans_arr->func(ans_arr->arg);

    FuncArg *ans_auto_ptr =
        &TEMPLVAL(FuncArg, {&print_int, &TEMPLVAL(int, {42})});
    fputs(", stack ptr: ", stdout);
    fflush(stdout);
    ans_auto_ptr->func(ans_auto_ptr->arg);

    fputs(", static ptr: ", stdout);
    fflush(stdout);
    ans_ptr->func(ans_ptr->arg);

    putchar('\n');
}
