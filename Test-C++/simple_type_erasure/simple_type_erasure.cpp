#ifdef __GNUC__
    #include <cxxabi.h>
#endif

#if __cplusplus <= 199711L
    #include <cstdlib>
    #define NULLPTR NULL
#else
    #define NULLPTR (nullptr)
#endif


#include <iostream>
#include <typeinfo>


  #define DEBUG
  #define MEMORY_DEBUG

#if defined(DEBUG) && defined(MEMORY_DEBUG)
    #include "nvwa/debug_new.h"
#endif


namespace Simple_Any {
    inline std::string get_typename(
            const std::type_info& type_id)
    {
      #ifdef __GNUC__
        char* realname = abi::__cxa_demangle(
                            type_id.name(), 0, 0, NULLPTR);
        std::string result = realname;
        std::free(realname);
      #else
        std::string result = type_id.name();
      #endif

        return result;
    }


    template<class Type> inline
          Type& at(Type& operand, int)
      { return operand; }
    template<class Type> inline
          Type& at(Type*& operand, int n)
      { return operand[n]; }


    template<class Type_T>
      struct Remove_Const {
        typedef Type_T Type;
    };
    template<class Type_T>
      struct Remove_Const<const Type_T> {
        typedef typename Remove_Const<Type_T>::Type Type;
    };

    template<class Type_T>
      struct Remove_Volatile {
        typedef Type_T Type;
    };
    template<class Type_T>
      struct Remove_Volatile<volatile Type_T> {
        typedef typename Remove_Volatile<Type_T>::Type Type;
    };

    template<class Type_T>
      struct Remove_CV {
        typedef typename Remove_Volatile<
                    typename Remove_Const<Type_T>::Type>::Type
                            Type;
    };

    template<class Type_T>
      struct Remove_Reference {
        typedef Type_T Type;
    };
    template<class Type_T>
      struct Remove_Reference<Type_T&> {
        typedef typename Remove_Reference<Type_T>::Type Type;
    };

    template<class Type_T>
      struct Remove_CVRef {
        typedef typename Remove_CV<
                    typename Remove_Reference<
                        Type_T>::Type>::Type Type;
    };

    template<class Type_T>
      struct Add_Pointer {
        typedef typename Remove_Reference<Type_T>::Type* Type;
    };

    template<class Type_T>
      struct Remove_Pointer_Base {
        typedef typename Remove_Reference<Type_T>::Type Type;
    };
    template<class Type_T>
      struct Remove_Pointer_Base<Type_T*> {
        typedef typename Remove_Reference<Type_T>::Type Type;
    };
    template<class Type_T>
      struct Remove_Pointer {
        typedef typename Remove_Pointer_Base<
            typename Remove_CV<Type_T>::Type>::Type Type;
    };

    template<class Type_T>
      struct Decay {
        typedef typename Remove_CV<Type_T>::Type Type;
    };
    template<class Type_T>
      struct Decay<Type_T&> {
        typedef typename Decay<Type_T>::Type Type;
    };
    template<class Type_T>
      struct Decay<Type_T[]> {
        typedef Type_T* Type;
    };
    template<class Type_T, int N>
      struct Decay<Type_T[N]> {
        typedef Type_T* Type;
    };
    template<class Type_T>
      struct Decay<Type_T()> {
        typedef typename Add_Pointer<Type_T()>::Type Type;
    };
    template<class Type_T>
      struct Decay<Type_T(...)> {
        typedef typename Add_Pointer<Type_T(...)>::Type Type;
    };
    template<class Type_T, class Arg1_T>
      struct Decay<Type_T(Arg1_T)> {
        typedef typename Add_Pointer<
                    Type_T(Arg1_T)>::Type Type;
    };
    template<class Type_T, class Arg1_T>
      struct Decay<Type_T(Arg1_T, ...)> {
        typedef typename Add_Pointer<
                    Type_T(Arg1_T, ...)>::Type Type;
    };
    template<class Type_T, class Arg1_T, class Arg2_T>
      struct Decay<Type_T(Arg1_T, Arg2_T)> {
        typedef typename Add_Pointer<
                    Type_T(Arg1_T, Arg2_T)>::Type Type;
    };
    template<class Type_T, class Arg1_T, class Arg2_T>
      struct Decay<Type_T(Arg1_T, Arg2_T, ...)> {
        typedef typename Add_Pointer<
                    Type_T(Arg1_T, Arg2_T, ...)>::Type Type;
    };
    template<class Type_T, class Arg1_T, class Arg2_T, class Arg3_T>
      struct Decay<Type_T(Arg1_T, Arg2_T, Arg3_T)> {
        typedef typename Add_Pointer<
                    Type_T(Arg1_T, Arg2_T, Arg3_T)>::Type Type;
    };
    template<class Type_T, class Arg1_T, class Arg2_T, class Arg3_T>
      struct Decay<Type_T(Arg1_T, Arg2_T, Arg3_T, ...)> {
        typedef typename Add_Pointer<
                    Type_T(Arg1_T, Arg2_T, Arg3_T, ...)>::Type
                        Type;
    };



    struct Any {
        struct Any_Value_Base {
            Any_Value_Base(
                const std::type_info& _type_id,
                int _array_size=-1)
                  : type_id (_type_id),
                    array_size (_array_size)  { }
            virtual ~Any_Value_Base()  { }

            virtual Any_Value_Base* clone() = 0;
            virtual std::ostream& show(
                std::ostream& out) const = 0;

            virtual Any_Value_Base& operator[](int);

            const std::type_info& type_id;
            const int array_size;
        };

        template<class Type>
          struct Any_Value : public Any_Value_Base {
            Any_Value(const Type& _value)
                : Any_Value_Base(typeid(_value)),
                  value (_value)
            {
              #ifdef DEBUG
                std::cerr << "Allocated "
                  << get_typename(type_id) << '\t'
                  << '\'' << *this << '\''
                  << " (" << this << ")\n";
              #endif
            }
            ~Any_Value()
            {
              #ifdef DEBUG
                std::cerr << "Deallocated "
                  << get_typename(type_id) << '\t'
                  << '\'' << *this << "' (" << this << ")\n";
              #endif
            }

            friend
              std::ostream& operator<<(
                  std::ostream& out,
                  const Any_Value& item)
            {
                item.show(out);
                return out;
            }

            virtual std::ostream& show(
                  std::ostream& out) const
            {
                out << this->value;
                return out;
            }

            virtual Any_Value<
                  typename Remove_Pointer<Type>::Type>&
                    operator[](int n)
              { return at(value, n); }

            Any_Value* clone()
              { return new Any_Value(value); }

            Type& cast()  { return value; }

            Type value;

          protected:
            Any_Value(const Type& _value, int _array_size)
                : Any_Value_Base(typeid(_value), _array_size),
                  value (_value)  { }
        };

        template<class Type>
          struct Any_Array : public Any_Value<Type*> {
            Any_Array(Type *const & _value, int _array_size)
                : Any_Value<Type*>(
                    _value, _array_size)
            {
              #ifdef DEBUG
                std::cerr << "Allocated "
                  << get_typename(Any_Value_Base::type_id) << '\t'
                  << '\'' << *this << '\''
                  << " (" << this << ")\n";
              #endif
            }

            friend std::ostream& operator<<(
                  std::ostream& out,
                  const Any_Array& array)
            {
                array.show(out);
                return out;
            }

            std::ostream& show(
                  std::ostream& out) const
            {
                const int size = Any_Value_Base::array_size;
                static const bool is_c_str = (
                    typeid(
                        typename Remove_Const<Type>::Type)
                      == typeid(char));
                static const char array_display[7] = {
                    (is_c_str) ? '\0' : '{', '\0',
                    (is_c_str) ? '\0' : ',',
                    (is_c_str) ? '\0' : ' ', '\0',
                    (is_c_str) ? '\0' : '}', '\0'};

                if (typeid(Type) == typeid(char)) {
                    out << this->value;
                }
                else if (size >= 0) {
                    out << &array_display[0];
                    for (int k = 0; k < size; ++k) {
                        out << this->value[k];
                        if (k != size-1) { out << &array_display[2]; }
                    }
                    out << &array_display[5];
                }
                else {
                    out << this->value;
                }

                return out;
            }
        };


        Any(): value (NULLPTR)
        {
          #ifdef DEBUG
            std::cerr << this << ": Allocated empty Any " << '\t'
              << " (" << &value << ")\n";
          #endif
        }
        Any(const Any& _copy)
            : value (((_copy.value)
                      ?
                      #ifdef DEBUG
                        std::cerr << this << ": ",
                      #endif
                        _copy.value->clone()
                      : NULLPTR))  { }
        template<class Type>
            Any(const Type& _value)
              : value ((
                      #ifdef DEBUG
                        std::cerr << this << ": ",
                      #endif
                      new Any_Value<
                          typename Decay<Type>::Type>(
                              _value)))  { }
        template<class Type, int N>
            Any(Type (&_value)[N])
              : value ((
                      #ifdef DEBUG
                        std::cerr << this << ": ",
                      #endif
                      new Any_Array<Type>(
                            &_value[0], N)))  { }
        template<class Type, int N>
            Any(const Type (&_value)[N])
              : value ((
                      #ifdef DEBUG
                        std::cerr << this << ": ",
                      #endif
                      new Any_Array<const Type>(
                            &_value[0], N)))  { }

        Any& operator=(const Any& _copy)
        {
          #ifdef DEBUG
            if (value) { std::cerr << this << ": "; }
          #endif
            delete value;

            if (_copy.value) {
              #ifdef DEBUG
                std::cerr << this << ": ";
              #endif
                value = _copy.value->clone();
            }

            return *this;
        }

        ~Any()
        {
          #ifdef DEBUG
            if (value) { std::cerr << this << ": "; }
          #endif

            delete value;
            value = NULLPTR;
        }

        friend std::ostream& operator<<(
            std::ostream& out,
            const Any& operand)
        {
            if (operand.value) {
                operand.value->show(out);
            }
            else { out << "(Empty)"; }
            return out;
        }

        Any_Value_Base& operator[](int n)
        {
            if (value) {
                return (*value)[n];
            }
            throw "";
        }

        Any_Value_Base* value;
    };


    template<class Dest_Type> inline
      Dest_Type& cast(const Any& src)
    {
        typedef typename Decay<Dest_Type>::Type
                    Decayed_Dest_Type;
        typedef typename Any::Any_Value<Decayed_Dest_Type>
                    Any_Value_Type;
        const std::type_info& src_type_id = (
            (src.value)
              ? src.value->type_id
              : typeid(void));

        Any_Value_Type *const casted_value_ptr = (
            dynamic_cast<Any_Value_Type*>(
                    src.value));
        if (casted_value_ptr) {
            return casted_value_ptr->cast();
        }

        std::cerr
          << "Cast '"
            << get_typename(src_type_id)
          << "' to '"
            << get_typename(typeid(Dest_Type))
          << "' is invalid.\n";
        throw std::bad_cast();
    }

    template<class Dest_Type> inline
      Dest_Type* cast(const Any* src_ptr)
    {
        typedef typename Decay<Dest_Type>::Type
                    Decayed_Dest_Type;
        typedef typename Any::Any_Value<Decayed_Dest_Type>
                    Any_Value_Type;

        Any_Value_Type *const casted_value_ptr = (
            dynamic_cast<Any_Value_Type*>(
                    src_ptr->value));
        if (casted_value_ptr) {
            return & casted_value_ptr->cast();
        }

        return NULLPTR;
    }
}


using namespace std;
using namespace Simple_Any;

int main()
{
    Any ans[] = {4, '2'};
    Any info[] = {"The answer is ", '\n',
                  ans, '\n'};

    ans[0] = "Disappeared.";
    ans[0] = 3.141592653589;
    ans[0] = "4";

    cout
      << info[0]
      << info[1]
      << cast<Any*>(info[2]) [0]
      << cast<Any*>(info[2]) [1]
      << info[3];

    return 0;
}
// Compile with
//   g++ -std=c++98 -Wall-Wextra -Wpedantic
//   clang++ -std=c++98 -Wall-Wextra -Wpedantic
//   No warnings.
