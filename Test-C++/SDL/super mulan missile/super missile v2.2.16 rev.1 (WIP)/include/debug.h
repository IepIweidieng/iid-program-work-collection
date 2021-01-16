#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define MLDEBUG 1

#if MLDEBUG==1
#define DEBUG(str) str
#define DEBUG_OUTPUT(str) DEBUG(std::cout<<str)
#define just_for_debug(str) std::cout<<str
#else
#define DEBUG(str) ;
#endif

#endif // DEBUG_H_INCLUDED
