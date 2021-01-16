#ifndef NINT_H_INCLUDED
#define NINT_H_INCLUDED

#include <iostream>

namespace iaz
{
struct nint
{   typedef intmax_t iint;
    typedef long double eint;

    iint num, gen;

    nint(iint const &num=0,
         iint const &gen=0):
        num(num? num: 1),
        gen(num? gen: gen-1)
    {}

    nint operator=(iint const& rhs)
    {return *this=nint(rhs);}

#define OPRTF(OPRT, NOPRT)\
    bool operator OPRT (nint const &rhs)const\
    {   return this->gen==rhs.gen?\
                this->num OPRT rhs.num:\
                (   this->gen>rhs.gen?\
                        this->num OPRT 0:\
                        rhs.num NOPRT 0\
                );\
    }\
\
    bool operator OPRT (iint const &rhs)const\
    {   nint nrhs(rhs);\
        return *this OPRT nrhs;\
    }\
\
    friend inline bool operator OPRT\
    (iint const &lhs, nint const& rhs)\
    {   nint nlhs(lhs);\
        return nlhs OPRT rhs;\
    }\

    OPRTF(>, <)

    OPRTF(>=, <)

    OPRTF(==, ==)

    OPRTF(<=, >)

    OPRTF(<, >)

#undef OPRTF

    friend inline std::ostream& operator<<
    (std::ostream &lhs, nint const &rhs)
    {   if (rhs.gen>0)
            return lhs<< (rhs.num<0? "-Inf": "Inf");
        if (rhs.gen<0)
            return lhs<< (rhs.num<0? "-0": "0");
        return lhs<< rhs.num;
    }
  };
}

#endif // NINT_H_INCLUDED
