#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#undef DEBUG_Mode

extern bool DEBUG_OUT;

#ifdef DEBUG_Mode
    #define DEBUG_output(code) code
    #define DEBUG_output_set(code) {code; DEBUG_OUT = true;}
    #define DEBUG_output_if(code) {if (DEBUG_OUT){code;}}
    #define DEBUG_reset DEBUG_OUT = false;
#else
    #define DEBUG_output(code)
    #define DEBUG_output_set(code) ;
    #define DEBUG_output_if(code) ;
    #define DEBUG_reset ;
#endif


#endif // DEBUG_H_INCLUDED
