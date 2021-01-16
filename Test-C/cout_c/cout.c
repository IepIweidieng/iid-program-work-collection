// cout, but it is an emulation in C
// Written by Iep Iweidieng on 2018-12-19
// Compiles with ISO C99 standard

#define iostream  <stdio.h>

#include iostream
#include <stdarg.h>

typedef struct Ostream Ostream;
const struct Ostream {
    const Ostream *
        (*func)(const char *format, ...);
} *do_cout(const char *format, ...)
{
    extern const Ostream *const cout;
    va_list(args);
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return cout;
}
const Ostream
    *const cout = & (Ostream){do_cout};

#define endln  chara('\n')
#define chara(val)  ("%c", val)
#define inte(val)  ("%d", val)
#define str(val)  ("%s", val)
#define KK  ->func

#define _endl  _char('\n')
#define _char(val)  KK chara(val)
#define _int(val)  KK inte(val)
#define _str(val)  KK str(val)

#define using  extern
#define namespace  Ostream
#define std  const *const cout


// -- The main function ------

#include iostream

using namespace std;

int main(void)
{
    cout
      _str("Hello, world") _endl
      _int(42) _char('0') _endl;
    return 0;
}
