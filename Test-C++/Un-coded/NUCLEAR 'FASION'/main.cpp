#define FASION_MODE OFF

/*2016-10-1. Primary version by Iep Iweidieng.

 *2016-10-1. Reversion 1 by Iep Iweidieng.
  ．Made class Type_a more completed.
  ．Made details more detailed.
  ．Made things more readable.
  ．"How we to get the array size of zero-size arrays" added.*/

/*Still an issue:
  Can't spawn child process of child processes
    without the debugger.*/

#include <iostream>
#include <string>
#include <algorithm>
#include <unistd.h>

#define OFF 0
#define CPP 1
#define CPLPL 2
#define CPLPL_NEW 3

#if FASION_MODE == CPP
  char nuclear[]={
    #define FG FF, FF, FF, FF, FF, FF, FF, FF, FE, FE
    #define FF FE, FE, FE, FE, FE, FE, FE, FE, FE, FE
    #define FE FD, FD, FD, FD, FD, FD, FD, FD, FD, FD
    #define FD FC, FC, FC, FC, FC, FC, FC, FC, FC, FC
    #define FC FB, FB, FB, FB, FB, FB, FB, FB, FB, FB
    #define FB FA, FA, FA, FA, FA, FA, FA, FA, FA, FA
    #define FA F_, F_, F_, F_, F_, F_, F_, F_, F_, F_
    #define F_ -1
    FG
    #undef F_
    #undef FA
    #undef FB
    #undef FC
    #undef FD
    #undef FE
    #undef FF
    #undef FG
  };

#elif FASION_MODE == CPLPL
  size_t const nuclear_sz={1836547290};
  char nuclear[nuclear_sz];

#elif FASION_MODE == CPLPL_NEW
  template<typename Type> class Type_a{
    private:size_t        size    ;
    private:Type   *const ptr2arr ;
    private:bool          poss_arr;

    #define CHECK_IF_A_INVALID \
      do { \
        if (!ptr2arr) \
          this->size =0, this->poss_arr =false; \
      } while(0)

    #define GET_POSSESSION \
      do {((Type_a&)rfr).poss_arr =false;} while (0)

    #define TYPE_A__CTOR(PARM, A_SIZE, P_2_A, ACT) \
      public:Type_a(PARM) \
         :size (A_SIZE), ptr2arr (P_2_A), poss_arr (true){ \
        ACT; \
      }

    #define TYPE_A_CONST(PARM, A_SIZE) \
      TYPE_A__CTOR(PARM, A_SIZE, \
                   new (std::nothrow) Type[sz], \
                   CHECK_IF_##A_INVALID)

    TYPE_A_CONST(size_t       &sz, sz)
    TYPE_A_CONST(size_t const &sz, sz)

    #undef TYPE_A_CONST

    #define TYPE_A_COPY(PARM, A_SIZE) \
      TYPE_A__CTOR(PARM, A_SIZE, \
                   rfr.ptr2arr, \
                   GET_##POSSESSION)

    TYPE_A_COPY(Type_a       &rfr, rfr.size)
    TYPE_A_COPY(Type_a const &rfr, rfr.size)

    #undef TYPE_A_COPY

    #undef TYPE_A__CTOR
    #undef GET_POSSESSION
    #undef CHECK_IF_INVALID

    public:~Type_a(){
      if (this->ptr2arr&& this->poss_arr)
        delete[] ptr2arr;
    }

    public:Type_a& operator=(Type_a const &rhs){
      if (this->ptr2arr&& this->poss_arr){
        this->size =rhs.size, delete[] (this->ptr2arr);

        if (new (std::nothrow, this->ptr2arr) Type[rhs.size]){
          std::copy(&rhs.ptr2arr[0],
                    &rhs.ptr2arr[this->size],
                    &this->ptr2arr[0]);
        } else {this->size =0;}

        return *this;
      }

      return rhs;
    }

    public:Type& operator[](intmax_t const &id){
      return ptr2arr[id];
    }

    public:bool is_valid()const{return bool(this->ptr2arr);}
    public:size_t get_size()const{return this->size;}
  };

  template<typename Type> Type_a<Type> neualloclear(){
    size_t max_nl ={0},
           max_fs ={0};

    for (size_t i ={(size_t(-1)/2)+1}; ; i /=2){
      if (!i){
        Type_a<Type> temp (max_nl);
        if (temp.is_valid()) return temp;
        return Type_a<Type>(max_fs);
      }

      if (Type_a<Type>(max_nl+i).is_valid())
        max_fs =max_nl, max_nl +=i;
    }
  }

  Type_a<char> nuclear (neualloclear<char>());

#else
  char nuclear[0]={};

#endif  //FASION_MODE

//sz can't be 0 or a compiling error will occur:
/* error: no matching function for call to 'get_size(char [0])'
   note: candidate is:
   note: template<class T, unsigned int sz> size_t get_size(T (&)[sz])
   note:   template argument deduction/substitution failed:            */
template<typename T, size_t sz>
 inline size_t get_size(T(&)[sz]){return sz;}

 //The solution to the problem above.
 /*Notice that the array nuclear should not
    be declared and defined as "char nuclear[]={};"
    or a compiling error will occur:                */
/*
   error: zero-size array 'nuclear'
   error: no matching function for call to 'get_size(char [0])'
   note: candidates are:
   note: template<class T, unsigned int sz> size_t get_size(T (&)[sz])
   note:   template argument deduction/substitution failed:

   note: template<class T> size_t get_size(T (&)[0])
   note:   template argument deduction/substitution failed:
   note:   template argument '-1' does not match '#'integer_cst' not supported by dump_decl#<declaration error>'
*/
/*The solution to this:
    Declare and define nuclear as "char nuclear[0]={};"
    as the example above.*/
template<typename T>
 inline size_t get_size(T(&)[0]){return 0;}


#if FASION_MODE == CPLPL_NEW
  //Specialization for Type_a.
  template<typename T>
   inline size_t get_size(Type_a<T>(&rhs)){
    return rhs.get_size();
  }

#endif // FASION_MODE

namespace para_str {
  using std::string;

//++str
  string& operator++(string&);

//str++
  inline string operator++(string&lhs, int){
    string temp(lhs);
    return ++lhs, temp;
  }
}

namespace{
  using namespace para_str;
  using std::cin;
  using std::cout;
  using std::endl;
}

int main(int argc, char *(argv[])){
  std::ios_base::sync_with_stdio(false),
    cin.tie(NULL),
    cout.unsetf(std::ios::unitbuf);
  string parm (argc>1? argv[argc-1]: "");

  cout<< parm<< " Nuclear: address=="<<
    reinterpret_cast<void*>(&nuclear[0])<<
    ", size=="<< get_size(nuclear)<< '\n';

#  ifndef _CRTIMP
#   ifdef __USE_CRTIMP
#    define _CRTIMP  __attribute__ ((dllimport))
#   else
#    define _CRTIMP
#   endif
#  endif
  _CRTIMP intptr_t (&exe)(int, const char*, const char*, ...)
    =_spawnl;

  if (++parm=="00"){
    cout<< "Ended normally. "
      "Enter enter or return to return."<< endl,
      cin.get();

    return 0;
  }

  cout<< "Exe: address=="<<
    reinterpret_cast<void*>(exe)<< endl;

#  ifndef _P_WAIT
#   define	_P_WAIT		0
#  endif
  if (exe(_P_WAIT, argv[0], argv[0], parm.c_str(), NULL)){
    cout<< "Ended early. "
      "Enter enter or return to return."<< endl,
      cin.get();
  }

  return 0;
}

//++str
std::string& para_str::operator++(string&rhs){
  if (rhs.empty()) rhs ="/";
  size_t temp ={size_t(rhs[0]-'/')};

  rhs[0] ='0'+(temp%('{'-'0'));
  for (size_t i ={1};
         i<=rhs.length()&& temp/('{'-'0');
         temp =rhs[i++]-'/'){
    if (i==rhs.length()) rhs.append("/");
    rhs[i] +=temp/('{'-'0');
  }

  return rhs;
}

#undef CPLPL_NEW
#undef CPLPL
#undef CPP
#undef FASION_MODE