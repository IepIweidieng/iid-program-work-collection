// Ver.1 Rev.1 by Iep Iweidieng on 2018-11-03
//    improve the performance by inlining functions
// Ver.1 by Iep Iweidieng on 2018-11-03
// Compile with
//    g++ -std=c++11 -Wall -Wextra -Wpedantic
//    clang++ -std=c++11 -Wall -Wextra -Wpedantic

#include <functional>
#include <initializer_list>
#include <limits>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>

typedef long double Num;
typedef long long int Int;
typedef unsigned long long int UInt;


template<class T> inline
  void noop(const std::initializer_list<T>&)  {}

struct Term { } TERM;

template<class T>
  struct TypeValue { T value; };

template<class Derived, class Result>
  struct FuncChain {
    operator Result() const
    {
        auto func = std::mem_fn(&Derived::eval);
        return Result{
                    func(static_cast<const Derived*>(this))};
    }
    template<class... Ts>
      const Derived operator()(Ts... vals) const
    {
        typedef const Derived (Derived::*DerivedConstMemFunc)(Ts...) const;
        auto func = std::mem_fn(
                        static_cast<DerivedConstMemFunc>(&Derived::append));
        return func(static_cast<const Derived*>(this),
                    vals...);
    }
    Result operator()(Term=TERM) const
      { return Result{*this}; }
};

class OsOutChain : public FuncChain<OsOutChain, bool> {
  public:
    typedef bool Result;

    OsOutChain(const OsOutChain& _cp) : out (_cp.out)  { }
    OsOutChain(std::ostream& _out) : out (_out)  { }

    Result eval() const  { return Result{out}; }
    template<class... Ts>
      const OsOutChain append(Ts... value) const
    {
        noop({(out << value, true)...});
        return *this;
    }

  private:
    std::ostream& out;
};

template<class Derived, class Value, class Result>
  struct ArithChain : public FuncChain<Derived, Result> {
    Value eval() const
    {
        auto func = std::mem_fn(&DerivedAccessor::eval);
        return func(static_cast<const Derived*>(this));
    }

    template<class... Ts>
      const Derived append(Ts... val) const
    {
        return DerivedAccessor::append_access(
                    static_cast<const Derived*>(this),
                    {static_cast<typename Derived::Value>(val)...});
    }

  private:
    struct DerivedAccessor : Derived {
        static const Derived append_access(
                        const Derived* derived_this,
                        std::initializer_list<typename Derived::Value> vals)
        {
            auto func = std::mem_fn(&DerivedAccessor::append_internal);
            return func(derived_this, vals);
        }
    };
};

template<class Value_T, class Result_T=Value_T>
        class LAccChain: public ArithChain<
                            LAccChain<Value_T, Result_T>, Value_T, Result_T> {
  public:
    typedef std::function<Value_T (Value_T, Value_T)> Func;
    typedef Value_T Value;
    typedef Result_T Result;

    LAccChain(Func _func, Value _res) : func (_func), res (_res)  { }

    operator Value() const  { return this->eval(); }
    Value eval() const  { return res; }

  protected:
    const LAccChain append_internal(std::initializer_list<Value> vals) const
    {
        Value result = res;
        for (const auto& value : vals) {
            result = func(result, value);
        }

        return LAccChain{func, result};
    }

  private:
    const Func func;
    const Value res;
};

template<class Value_T, class Result_T=Value_T>
        class RAccChain : public ArithChain<
                            RAccChain<Value_T, Result_T>, Value_T, Result_T> {
  public:
    typedef std::function<Value_T (Value_T, Value_T)> Func;
    typedef Value_T Value;
    typedef Result_T Result;

    RAccChain(Func _func, Value _init_value)
        : func (_func), init_value (_init_value), val_list ()  { }

    operator Value() const  { return this->eval(); }
    Value eval() const
    {
        Value res = init_value;
        if (val_list.empty()) { return res; }

        auto&& vals_iter = val_list.rbegin();
        res = *vals_iter;
        ++ vals_iter;
        for (; vals_iter != val_list.rend(); ++ vals_iter) {
            res = func(*vals_iter, res);
        }

        return res;
    }

  protected:
    const RAccChain append_internal(std::initializer_list<Value> vals) const
    {
        std::vector<Value> new_vals (val_list);
        new_vals.insert(new_vals.end(), vals.begin(), vals.end());
        return RAccChain{func, init_value, new_vals};
    }

  private:
    RAccChain(Func _func, Value _init_value,
              const std::vector<Value>& _val_list)
        : func (_func), init_value (_init_value), val_list (_val_list)  { }

    const Func func;
    const Value init_value;
    const std::vector<Value> val_list;
};

template<class Value_T, class Result_T=Value_T>
        class LDecChain : public ArithChain<
                            LDecChain<Value_T, Result_T>, Value_T, Result_T> {
  public:
    typedef std::function<Value_T (Value_T, Value_T)> Func;
    typedef Value_T Value;
    typedef Result_T Result;

    LDecChain(Func _func, Value _first_value)
        : func (_func), res (_first_value),
          first_value (_first_value), append_count (0)  { }

    operator Value() const  { return this->eval(); }
    Value eval() const  { return res; }

  protected:
    const LDecChain append_internal(std::initializer_list<Value> vals) const
    {
        Value result = res;
        Value new_first_value = first_value;
        auto&& value_iter = vals.begin();
        int delta_append_count = 0;

        if (value_iter != vals.end() && !append_count) {
            result = func(result, *value_iter);
            new_first_value = *value_iter;
            ++value_iter;
            ++ delta_append_count;
        }
        if (value_iter != vals.end() && append_count + delta_append_count == 1) {
            result = func(first_value, *value_iter);
            ++value_iter;
            ++ delta_append_count;
        }
        for (; value_iter != vals.end(); ++ value_iter) {
            result = func(res, *value_iter);
        }

        return LDecChain{
            func, result, new_first_value, append_count + vals.size()};
    }

  private:
    LDecChain(Func _func, Value _res,
              Value _first_value, int _append_count)
        : func (_func), res (_res),
          first_value (_first_value), append_count (_append_count)  { }

    const Func func;
    const Value res;
    const Value first_value;
    const int append_count;
};


template<class Value_T, class Result_T=Value_T>
        class RDecChain : public ArithChain<
                            RDecChain<Value_T, Result_T>, Value_T, Result_T> {
  public:
    typedef std::function<Value_T (Value_T, Value_T)> Func;
    typedef Value_T Value;
    typedef Result_T Result;

    RDecChain(Func _func, Value _init_value)
        : func (_func), init_value (_init_value), val_list ()  { }

    operator Value() const  { return this->eval(); }
    Value eval() const
    {
        Value res = init_value;
        if (val_list.empty()) { return res; }

        auto vals_iter = val_list.rbegin();
        Value first_value = *vals_iter;

        res = func(res, first_value);
        ++ vals_iter;
        if (vals_iter != val_list.rend()) {
            res = func(*vals_iter, first_value);
            ++ vals_iter;
        }
        for (; vals_iter != val_list.rend(); ++ vals_iter) {
            res = func(*vals_iter, res);
        }

        return res;
    }

  protected:
    const RDecChain append_internal(std::initializer_list<Value> vals) const
    {
        std::vector<Value> new_vals (val_list);
        new_vals.insert(new_vals.end(), vals.begin(), vals.end());
        return RDecChain{func, init_value, new_vals};
    }

  private:
    RDecChain(Func _func, Value _init_value,
              const std::vector<Value>& _val_list)
        : func (_func), init_value (_init_value), val_list (_val_list)  { }

    const Func func;
    const Value init_value;
    const std::vector<Value> val_list;
};

struct HyperOprChain;

class HyperOpr {
  public:
    friend HyperOprChain;

    std::function<Num (Num, Num)> operator[](Int grade) const
      { return HyperOprFunctor{grade}; }

  private:
    struct rec_stack_frame { Int grade; Num lhs; Num rhs; int state; Num res; };
    struct HyperOprFunctor {
        Num operator()(Num lhs, Num rhs)
        {
            std::stack<rec_stack_frame> rec_stack;
            rec_stack.push({});
            rec_stack.push({grade, lhs, rhs, 0, Num{}});

            while (rec_stack.size() > 1) {
                rec_stack_frame cur_frame = rec_stack.top();
                switch (cur_frame.state) {
                  case 0:
                    switch (cur_frame.grade) {
                      case 0:
                        rec_return(rec_stack, 1 + cur_frame.rhs);
                        continue;
                      case 1:
                        rec_return(rec_stack, cur_frame.lhs + cur_frame.rhs);
                        continue;
                      case 2:
                        rec_return(rec_stack, cur_frame.lhs * cur_frame.rhs);
                        continue;
                      case 3:
                        rec_return(rec_stack,
                                   std::pow(cur_frame.lhs, cur_frame.rhs));
                        continue;
                      default:
                        if (cur_frame.rhs < 1) {
                            rec_return(rec_stack, 1.0L);
                            continue;
                        } else {
                            rec_call(rec_stack,
                                     {cur_frame.grade,
                                      cur_frame.lhs, cur_frame.rhs - 1,
                                      int{}, Num{}});
                            continue;
                        }
                    }
                  case 1:
                    rec_call_and_return(rec_stack,
                                        {cur_frame.grade - 1,
                                         cur_frame.lhs, cur_frame.res,
                                        int{}, Num{}});
                    continue;
                }
            }
            return rec_stack.top().res;
        }

        Int grade;
    };

    static void rec_call(
        std::stack<rec_stack_frame>& rec_stack,
        rec_stack_frame arg)
    {
        ++ rec_stack.top().state;
        arg.state = 0;
        rec_stack.push(arg);
    };
    static void rec_return(
        std::stack<rec_stack_frame>& rec_stack,
        Num res)
    {
        rec_stack.pop();
        rec_stack.top().res = res;
    };
    static void rec_call_and_return(  // Tail recursion optimization
        std::stack<rec_stack_frame>& rec_stack,
        rec_stack_frame arg)
    {
        arg.state = 0;
        rec_stack.top() = arg;
    };
};

template<class Type>
  struct CompValue {
    CompValue(): value (Type()), res (2)  { }
    CompValue(const CompValue& _cp): value (_cp.value), res (_cp.res)  { }
    CompValue(const Type& _value, int _res=true)
      : value (_value), res (_res)  { }
    template<class ArithChainType>
      CompValue(
            const ArithChain<ArithChainType, CompValue<Type>, bool>& arith_chain)
            : value (), res ()
        { *this = CompValue(arith_chain.eval()); }

    operator bool() const  { return bool(res); }

    Type value;
    int res;
};

struct HyperExponent {
    operator Num() const  { return value; }
    HyperExponent operator*() const
    {
        return HyperExponent{value, grade + 1};
    }

    template<class Num_T>
      friend HyperExponent operator*(Num_T lhs, HyperExponent rhs)
    {
        return HyperExponent{
            HyperOpr()[1 + rhs.grade](lhs, rhs.value), 1};
    }


    HyperExponent operator+() const
      { return *this; }
    HyperExponent operator-() const
      { return HyperExponent{-value, grade}; }

    Num value;
    Int grade;
};

HyperExponent operator""_f(UInt v)
  { return HyperExponent{Num(v), 1}; }
HyperExponent operator""_f(Num v)
  { return HyperExponent{v, 1}; }

#define COMP_OPR(opr) \
    template<class Type> inline \
      CompValue<Type> operator opr(Type lhs, HyperExponent rhs) \
    { \
        return CompValue<Type>{rhs, lhs opr rhs.value}; \
    } \
    template<class Type> inline \
      CompValue<Type> operator opr(HyperExponent lhs, Type rhs) \
    { \
        return CompValue<Type>{rhs, lhs.value opr rhs}; \
    } \
    template<class Type> inline \
      CompValue<Type> operator opr(HyperExponent lhs, HyperExponent rhs) \
    { \
        return CompValue<Type>{rhs.value, lhs.value opr rhs.value}; \
    } \
    template<class Type> inline \
      CompValue<Type> operator opr(CompValue<Type> lhs, Type rhs) \
    { \
        return CompValue<Type>{rhs, \
                               (lhs.res == 2) \
                                  ? true \
                                  : (lhs.res) && (lhs.value opr rhs)}; \
    } \
    template<class Type> inline \
      CompValue<Type> operator opr(CompValue<Type> lhs, \
                                   CompValue<Type> rhs) \
    { \
        return CompValue<Type>{rhs.value, \
                               (lhs.res == 2) \
                                  ? rhs.res \
                                  : (lhs.res && rhs.res) \
                                      && (lhs.value opr rhs.value)}; \
    } \

COMP_OPR(<) COMP_OPR(<=) COMP_OPR(==) COMP_OPR(!=) COMP_OPR(>=) COMP_OPR(>)

#undef COMP_OPR

struct HyperOprChain : public FuncChain<RAccChain<Num>, void> {
    RAccChain<Num> operator[](Int grade) const
    {
        return RAccChain<Num>{HyperOpr::HyperOprFunctor{grade}, 1};
    }
};


template<class Type>
  struct LogicalValue {
    LogicalValue(): value (Type()), res (2)  { }
    LogicalValue(const LogicalValue& _cp): value (_cp.value), res (_cp.res)  { }
    LogicalValue(const Type& _value, int _res=true)
      : value (_value), res (_res)  { }
    template<class ArithChainType>
      LogicalValue(
            const ArithChain<ArithChainType, LogicalValue<Type>, bool>& arith_chain)
            : value (), res ()
        { *this = LogicalValue(arith_chain.eval()); }

    operator Type() const  { return value; }

    Type value;
    int res;
};

#define LOGICAL_OPR(opr)
    template<class Type> inline \
      LogicalValue<Type> operator&&(LogicalValue<Type> lhs, \
                                    LogicalValue<Type> rhs) \
    { \
        return LogicalValue<Type>{(lhs.res) \
                                    ? rhs \
                                    ? false \
                                  (lhs.res == 2) \
                                    ? rhs.res \
                                    : (lhs.res && rhs.res) \
                                      && (lhs.value && rhs.value)}; \
    } \
    template<class Type> inline \
      LogicalValue<Type> operator||(LogicalValue<Type> lhs, \
                                    LogicalValue<Type> rhs) \
    { \
        return LogicalValue<Type>{(lhs.res) \
                                    ? (rhs.value) \
                                    : (lhs.value), \
                                  (lhs.res == 2) \
                                    ? rhs.res \
                                    : (lhs.res && rhs.res) \
                                      && (lhs.value || rhs.value)}; \
    } \
    template<class Type> inline \
      LogicalValue<Type> operator==(LogicalValue<Type> lhs, \
                                    LogicalValue<Type> rhs) \
    { \
        return LogicalValue<Type>{(lhs.res) \
                                    ? (rhs.value) \
                                    ? false \
                                  (lhs.res == 2) \
                                    ? rhs.res \
                                    : (lhs.res && rhs.res) \
                                      && (lhs.value == rhs.value)}; \
    } \
    template<class Type> inline \
      LogicalValue<Type> operator!=(LogicalValue<Type> lhs, \
                                    LogicalValue<Type> rhs) \
    { \
        return LogicalValue<Type>{(lhs.res) \
                                    ? (rhs.value) \
                                    ? false \
                                  (lhs.res == 2) \
                                    ? rhs.res \
                                    : (lhs.res && rhs.res) \
                                      && (lhs.value != rhs.value)}; \
    } \

LOGICAL_OPR(&&) LOGICAL_OPR(||) LOGICAL_OPR(==) LOGICAL_OPR(!=)

#undef LOGICAL_OPR


template<class Type> inline
  auto resolve(Type (&func)()) -> Type (&)()
    { return func; }
template<class Type> inline
  auto resolve(Type (&func)(Type)) -> Type (&)(Type)
    { return func; }
template<class Type> inline
  auto resolve(Type (&func)(Type, Type)) -> Type (&)(Type, Type)
    { return func; }

namespace IO_Chain {
    const auto& print = OsOutChain{std::cout};
}

namespace Arithm_Chain {
    template<class Num_T> inline
      Num_T successor(Num_T, Num_T rhs)  { return rhs + 1; }
    template<class Num_T> inline
      Num_T predecessor(Num_T lhs, Num_T)  { return lhs - 1; }
    template<class Num_T> inline
      Num_T log_yb(Num_T lhs, Num_T rhs)
        { return std::log(lhs) / std::log(rhs); }

    const auto& succ = RAccChain<Num>{successor<Num>, 0};
    const auto& add = LAccChain<Num>{std::plus<Num>(), 0};
    const auto& mul = LAccChain<Num>{std::multiplies<Num>(), 1};
    const auto& expt = RAccChain<Num>{resolve<Num>(std::pow), 1};
    const auto& expn = RDecChain<Num>{resolve<Num>(std::pow), std::exp(Num(1))};
    const auto& expb = RDecChain<Num>{resolve<Num>(std::pow), 2};
    const auto& expg = RDecChain<Num>{resolve<Num>(std::pow), 10};

    const auto& pred = LDecChain<Num>{predecessor<Num>, 0};
    const auto& sub = LDecChain<Num>{std::minus<Num>(), 0};
    const auto& fdiv = LDecChain<Num>{std::divides<Num>(), 1};
    const auto& idiv = LDecChain<Int>{std::divides<Int>(), 1};
    const auto& mod = LDecChain<Num>{resolve<Num>(std::fmod), 1};
    const auto& logt = LDecChain<Num>{log_yb<Num>, 1};
    const auto& logn = LDecChain<Num>{log_yb<Num>, std::exp(Num(1))};
    const auto& logb = LDecChain<Num>{log_yb<Num>, 2};
    const auto& logg = LDecChain<Num>{log_yb<Num>, 10};

    const auto& hy = HyperOprChain{};
}

namespace Logical_Chain {
    const auto& land = LAccChain<bool>{std::logical_and<bool>(), true};
    const auto& lior = LAccChain<bool>{std::logical_or<bool>(), false};
    const auto& leqv = LAccChain<bool>{std::equal_to<bool>(), true};
    const auto& lxor = LAccChain<bool>{std::not_equal_to<bool>(), false};
    const auto& lnot = LDecChain<bool>{std::not_equal_to<bool>(), true};
}

namespace Bitwise_Chain {
    template<class UInt_T> inline
      UInt_T bit_eqv(UInt_T lhs, UInt_T rhs)
        { return ~std::bit_xor<UInt_T>()(lhs, rhs); }

    const auto& band = LAccChain<UInt>{std::bit_and<UInt>(), ~UInt{0}};
    const auto& bior = LAccChain<UInt>{std::bit_or<UInt>(), 0};
    const auto& beqv = LAccChain<UInt>{bit_eqv<UInt>, ~UInt{0}};
    const auto& bxor = LAccChain<UInt>{std::bit_xor<UInt>(), 0};
    const auto& bnot = LDecChain<UInt>{std::bit_xor<UInt>(), ~UInt{0}};
}

namespace Comp_Chain {
    const auto& lss = LAccChain<CompValue<Num>, bool>{
                        resolve<CompValue<Num>>(operator<), CompValue<Num>()};
    const auto& leq = LAccChain<CompValue<Num>, bool>{
                        resolve<CompValue<Num>>(operator<=), CompValue<Num>()};
    const auto& equ = LAccChain<CompValue<Num>, bool>{
                        resolve<CompValue<Num>>(operator==), CompValue<Num>()};
    const auto& neq = LAccChain<CompValue<Num>, bool>{
                        resolve<CompValue<Num>>(operator!=), CompValue<Num>()};
    const auto& geq = LAccChain<CompValue<Num>, bool>{
                        resolve<CompValue<Num>>(operator>=), CompValue<Num>()};
    const auto& gtr = LAccChain<CompValue<Num>, bool>{
                        resolve<CompValue<Num>>(operator>), CompValue<Num>()};

    const auto& min = LAccChain<Num>{
                        resolve<const Num&>(std::min), std::numeric_limits<Num>::max()};
    const auto& max = LAccChain<Num>{
                        resolve<const Num&>(std::max), std::numeric_limits<Num>::min()};
}


using namespace std;
using namespace IO_Chain;
using namespace Arithm_Chain;
using namespace Logical_Chain;
using namespace Bitwise_Chain;
using namespace Comp_Chain;

int main()
{
    return (print (left) (boolalpha)
        (setw(8))(1     + 3_f) ('\t')    (setw(8))(hy[0] (2) (3)) ('\t')    (setw(8))(succ (2) (3)) ('\n')
        (setw(8))(2     + 3_f) ('\t')    (setw(8))(hy[1] (2) (3)) ('\t')    (setw(8))(add  (2) (3)) ('\n')
        (setw(8))(2     * 3_f) ('\t')    (setw(8))(hy[2] (2) (3)) ('\t')    (setw(8))(mul  (2) (3)) ('\n')
        (setw(8))(2    ** 3_f) ('\t')    (setw(8))(hy[3] (2) (3)) ('\t')    (setw(8))(expt (2) (3)) ('\n')
        (setw(8))(2   *** 3_f) ('\t')    (setw(8))(hy[4] (2) (3)) ('\n')
        (setw(8))(2  **** 3_f) ('\t')    (setw(8))(hy[5] (2) (3)) ('\n')
        (setw(8))(2 ***** 3_f) ('\t')    (setw(8))(hy[6] (2) (3)) ('\n')
        ("3 > 2 > 1 = ") (3_f > 2 > 1) ('\t')   ("(gtr 3 2 1) = ") (gtr (3) (2) (1)) ('\n')
        ("82828 < 2 > 1 < 9 = ") (82828_f < 2 > 1 < 9) ('\t')
             ("(lss (gtr (lss 82828 2) 1) 9) = ") (lss (gtr (lss (82828) (2)) (1)) (9)) ('\n'));
}
