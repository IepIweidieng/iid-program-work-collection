/* range_op_cpp_vs_es.cpp
Examples of operating on ranges of objects
   using C++11 / C++20 / ECMAScript 6

C++11 (without user-defined classes) and ECMAScript 6 examples inspired by 張哲豫.
Written by Iweidieng Iep on 2019-06-13.

Compile the C++ code with
   `g++ range_op_cpp_vs_es.cpp -Wall -Wextra -Wpedantic -std=c++11`
Compile the C++ code with the C++20 part with (if supported)
   `g++ range_op_cpp_vs_es.cpp -Wall -Wextra -Wpedantic -std=c++20 -fconcepts`
No warnings.
Result (example; compiled with `-O` option;
   the `exampleCxx11User` was simplified
      to use the equivalent operations as `exampleCxx20Ranges`):
```
exampleCxx11Stl:        {1, 55, 89, 2, 3, 13, } Response time: 0.0216ms
exampleCxx11User:       {1, 55, 89, 2, 3, 13, } Response time: 0.0183ms
exampleCxx20Ranges:     {1, 55, 89, 2, 3, 13, } Response time: 0.0066ms
```

Run the ECMAScript 6 code with
   `cpp -P -x c -D__ecmascript range_op_cpp_vs_es.cpp |
      nodejs --trace-warnings --trace-deprecation`
Result:
```
[ 1, 55, 89, 2, 3, 13 ]
```

Rev.1 by Iweidieng Iep on 2019-06-13:
   `Enable_if_tp<>`: Fix `TrueT` not being passed to `Enable_if_b_tp<>`.
Rev.2 by Iweidieng Iep on 2019-06-13:
   `Stream::Detail`: Replace all `T_tp<std::remove_reference<>>`s by `Remove_ref<>`.
Rev.3 by Iweidieng Iep on 2019-06-13:
   Use list initialization whenever possible.
*/

#ifdef __cplusplus
#include <algorithm>  // `std::transform()`
#include <chrono>
#include <forward_list>
#include <functional>  // `std::function<>`
#include <numeric>  // `std::accumulate()`
#include <initializer_list>
#include <iostream>
#include <iterator>  // `std::begin()`, `std::end()`
#include <tuple>
#include <type_traits>  // `std::enable_if<>`, `std::conditional<>`
#include <utility>  // `std::move()`, `std::forward()`
#include <vector>

#if defined __cpp_lib_ranges
  #include <ranges>
  #define CXX20_CODE(...)  __VA_ARGS__
#else
  #define CXX20_CODE(...)
#endif

#define CXX11_USER_CODE(...) __VA_ARGS__

int calculateFibonacci(int n)
{
    int res[] {0, 1};
    for (int k {2}; k <= n; ++k) {
        res[k%2] = res[0] + res[1];
    }
    return res[n%2];
}

std::vector<int> exampleCxx11Stl()
{
    std::vector<short> user_input {1, 10, 11, 18, 3, 4, 7, 17, 19, 18,};
    std::vector<int> fibonacci;

    std::transform(
        std::begin(user_input),
        std::end(user_input),
        std::back_inserter(fibonacci),
        calculateFibonacci);
    fibonacci.assign(
        std::begin(fibonacci),
        std::remove_if(
            std::begin(fibonacci),
            std::end(fibonacci),
            [](unsigned number)  { return !(number <= 100); }));

    return fibonacci;
}

#if CXX11_USER_CODE(true) + false
namespace Stream {
namespace Detail {

template <typename T>
  using T_tp = typename T::type;
template <bool b, typename TrueT = int>
  using Enable_if_b_tp = T_tp<std::enable_if<b, TrueT>>;
template <typename T, typename TrueT = int>
  using Enable_if_tp = Enable_if_b_tp<T::value, TrueT>;
template <typename T, typename FalseT = int>
  using Disable_if_tp = Enable_if_b_tp<!T::value, FalseT>;
template <typename T, typename TrueT, typename FalseT>
  using Conditional_tp = T_tp<std::conditional<T::value, TrueT, FalseT>>;
template <typename F, typename... ArgTs>
#ifdef __cpp_lib_invoke
  using Invoke_result_tp = T_tp<std::invoke_result<F, ArgTs&&...>>;
#else
  using Invoke_result_tp = T_tp<std::result_of<F&&(ArgTs&&...)>>;
#endif
template <typename T, typename TrueT = int>
  // Propagate the template substitution failure caused by `T`
  using Enable_if_valid_tp = Conditional_tp<std::true_type, TrueT, T>;
template <typename T>
  using Remove_ref = T_tp<std::remove_reference<T>>;

/* Generalized `begin()` and `end()` that work on scalar types
      by treating scalar types as one element arrays */
template <typename T,
      Disable_if_tp<std::is_scalar<Remove_ref<T>>> = 0>
 inline constexpr auto begin(T&& v) -> decltype(std::begin(v))
  { return std::begin(v); }
template <typename T,
      Disable_if_tp<std::is_scalar<Remove_ref<T>>> = 0>
 inline constexpr auto end(T&& v) -> decltype(std::end(v))
  { return std::end(v); }
template <typename T,
      Enable_if_tp<std::is_scalar<Remove_ref<T>>> = 0>
  inline constexpr Remove_ref<T>* begin(T&& v)  { return &v; }
template <typename T,
      Enable_if_tp<std::is_scalar<Remove_ref<T>>> = 0>
  inline constexpr Remove_ref<T>* end(T&& v)  { return &v + 1; }

template <typename T>
  using Get_iter_tp = decltype(begin(std::declval<T&&>()));
template <typename T>
  using Get_const_iter_tp = Get_iter_tp<const Remove_ref<T>>;
template <typename T>
  using Get_elem_tp = Remove_ref<decltype(*std::declval<Get_iter_tp<T>&>())>;
template <typename T>
  using Get_list_tp = std::forward_list<T_tp<std::remove_cv<T>>>;
template <typename T>
  using Get_elem_list_tp = Get_list_tp<Get_elem_tp<T>>;

/* It tries to resolve overloaded member functions for member pointers
      and results in template substitution failure
         if the overload resolution is invalid */
template <typename ClassT, typename RetT, typename... ArgTs>
 inline constexpr auto
  resolve(RetT(Remove_ref<ClassT>::*method)(ArgTs...)) -> decltype(method)
  { return method; }

template <typename T,
      Enable_if_valid_tp<decltype(
          resolve<T, void, Get_elem_tp<T>&&>(&Remove_ref<T>::push_back))> = 0>
 inline constexpr auto list_inserter(T&& li) -> decltype(std::back_inserter(li))
  { return std::back_inserter(li); }
/* Fallback overload */
template <typename... Ts,
      Enable_if_b_tp<sizeof...(Ts) == 1> = 0>
 inline constexpr auto list_inserter(Ts&&... li) -> decltype(std::front_inserter(li...))
  { return std::front_inserter(li...); }

template <typename T,
      Enable_if_valid_tp<decltype(
          resolve<T, void, Get_elem_tp<T>&&>(&Remove_ref<T>::push_back))> = 0>
  inline void finish_insert(T&&)  { }
/* Fallback overload */
template <typename... Ts,
      Enable_if_b_tp<sizeof...(Ts) == 1> = 0>
 inline void finish_insert(Ts&&... li)
  // Expand the parameter pack in the argument list
  { [](...)  { }((li.reverse(), 0)...); }

/* The basic class of `Stream` for temporary objects,
      whose instances store the elements to avoid the dangling reference issue */
template <typename SrcT, typename DestT = Get_elem_list_tp<SrcT>>
 class Stream_base {
  public:
    using Src_t = SrcT;
    using Dest_t = DestT;

    constexpr Stream_base(SrcT&& obj):
          li_ {std::make_move_iterator(begin(obj)),
            std::make_move_iterator(end(obj))}  { }

    DestT eval()  { return li_; }

  private:
    DestT li_;
};

/* The basic class of `Stream` for non-temporary objects,
      whose instances only store the `begin` and `end` iterators */
template <typename SrcT, typename DestT>
 class Stream_base<SrcT&, DestT> {
  public:
    using Src_t = SrcT;
    using Dest_t = DestT;
    using Const_iter_t = Get_const_iter_tp<Src_t>;

    constexpr Stream_base(const SrcT& obj):
          begin_ {begin(obj)}, end_ {end(obj)}  { }

    Dest_t eval()  { return {begin_, end_}; }

  private:
    Const_iter_t begin_;
    Const_iter_t end_;
};

/* The main class of `Stream`,
      implemented with ((SrcT) -> DestT) function composition,
      whose each instance stores a function
         and another instance storing the inner function */
template <typename InnerT, typename SrcT = typename InnerT::Dest_t, typename DestT = SrcT>
 class Stream_impl {
  public:
    using Src_t = SrcT;
    using Dest_t = DestT;
    using Inner_t = InnerT;

    using Elem_dest_t = Get_elem_tp<Dest_t>;
    using Func_t = std::function<Dest_t(Src_t)>;

    constexpr Stream_impl(const Stream_impl& cpy) = default;
    constexpr Stream_impl(Stream_impl&& mov) = default;

    template <typename T>
     constexpr Stream_impl(const T& obj):
          inner_ {std::forward<const T>(obj)},
          func_ {[](SrcT li)  { return li; }}  { }
    template <typename T>
     constexpr Stream_impl(T&& obj):
          inner_ {std::move(obj)},
          func_ {[](SrcT li)  { return li; }}  { }

    constexpr Stream_impl(const Inner_t& inner, const Func_t& func):
          inner_ {inner}, func_ {func}  { }
    constexpr Stream_impl(Inner_t&& inner, Func_t&& func):
          inner_ {std::move(inner)}, func_ {std::move(func)}  { }

    /* Evaluate result;
          convert the result to container type whenever need;
          perform conversion on the elements whenever need */
    template <template <typename...> class ResTp>
     ResTp<Elem_dest_t> value()
      { return value<ResTp<Elem_dest_t>>(); }
    template <typename ResT>
      ResT value()
    {
        Dest_t res {eval()};
        return {begin(res), end(res)};
    }
    Dest_t value()  { return eval(); }

    template <typename ElemRetDesigT = void, typename F,
          typename RetT = Get_list_tp<
                  Conditional_tp<std::is_same<ElemRetDesigT, void>,
                    Invoke_result_tp<F, Elem_dest_t&&>, ElemRetDesigT>>>
     Stream_impl<Stream_impl, DestT, RetT>
      map(F&& func)
    {
        auto func_op = to_assignable(std::forward<F>(func));
        return {*this, {[func_op](Dest_t li)
        {
            RetT res {};
            auto ins {list_inserter(res)};
            std::transform(begin(li), end(li), ins, func_op);
            finish_insert(res);
            return res;
        }}};
    }

    template <typename F>
     Stream_impl<Stream_impl, DestT, Get_list_tp<Elem_dest_t>>
      filter(F&& func)
    {
        auto func_op = to_assignable(std::forward<F>(func));
        return {*this, {[func_op](Dest_t li)
        {
            li.remove_if([&func_op](Elem_dest_t& v)  { return !func_op(v); });
            return li;
        }}};
    }

    template <typename AccT = Elem_dest_t, typename F,
          typename RetT = Invoke_result_tp<F, AccT&&, Elem_dest_t&&>>
     Stream_impl<Stream_impl, DestT, RetT>
      reduce(F&& func)  { return reduce(std::forward<F>(func), RetT{}); }
    template <typename AccT = Elem_dest_t, typename F,
          typename RetT = Invoke_result_tp<F, AccT&&, Elem_dest_t&&>>
     Stream_impl<Stream_impl, DestT, RetT>
      reduce(F&& func, RetT&& init)
    {
        auto func_op = to_assignable(std::forward<F>(func));
        return {*this, {[func_op, init](Dest_t li)
          { return std::accumulate(begin(li), end(li), init, func_op); }}};
    }

    template <typename RetT = Elem_dest_t>
     Stream_impl<Stream_impl, DestT, RetT>
      join()
    {
        return {*this, {[](Dest_t li)
        {
            RetT res {};
            auto ins {list_inserter(res)};
            std::for_each(begin(li), end(li), [&ins](Elem_dest_t& v)
              { std::move(begin(v), end(v), ins); });
            finish_insert(res);
            return res;
        }}};
    }

    Dest_t eval()  { return func_(inner_.eval()); }

  private:
    /* Workaround for g++-7.4.0: 'error: variable ‘func’ has function type'
          whenever `func` is captured by lambda by value
    */
    template <typename T,
          Enable_if_tp<std::is_function<Remove_ref<T>>> = 0>
     static constexpr T_tp<std::decay<T>> to_assignable(T&& v)
      { return &v; }
    template <typename T,
          Disable_if_tp<std::is_function<Remove_ref<T>>> = 0>
     static constexpr T&& to_assignable(T&& v)
      { return std::forward<T>(v); }

    Inner_t inner_;
    Func_t func_;
};

}  // namespace Detail

template <typename T>
  using Stream = Detail::Stream_impl<Detail::Stream_base<T&&>>;

template <typename T>
 inline constexpr Stream<T&&> make_stream(T&& obj)
  { return {std::forward<T>(obj)}; }
template <typename T>
 inline constexpr auto make_stream(const std::initializer_list<T>& obj)
    -> Stream<decltype(obj)&>
  { return {obj}; }
template <typename T>
 inline constexpr auto make_stream(std::initializer_list<T>&& obj)
    -> Stream<decltype(obj)&&>
  { return {std::move(obj)}; }

}  // namespace Stream

using Stream::make_stream;

std::vector<int> exampleCxx11User()
{
    std::vector<short> user_input {1, 10, 11, 18, 3, 4, 7, 17, 19, 18,};

    auto fibonacci_filtered = make_stream(42)  // SrcT: int -> DestT: List<int>
            .map([&user_input](...)  { return user_input; })  // -> List<vector<short>>
            .join()  // -> List<short>
            .map(calculateFibonacci)  // -> List<int>
            .filter([](unsigned number)  { return number <= 100; })  // -> List<int>
            .reduce<std::vector<short>>([](std::vector<short> lhs, short&& rhs)
            {
                lhs.emplace_back(std::move(rhs));
                return lhs;
            })  // -> vector<short>
            .map([](int v) -> int  { return v; })  // -> List<int>
            .value<std::vector>();  // ResT: vector<int>

/* Use the equivalent operations as `exampleCxx20Ranges`:
    auto fibonacci_filtered = make_stream(user_input)  // vector<short> -> List<short>
            .map(calculateFibonacci)  // -> List<int>
            .filter([](int number)  { return number <= 100; })  // -> List<int>
            .value<std::vector>();  // ResT: vector<int>
*/

    return fibonacci_filtered;
}
#endif  // #if CXX11_USER_CODE(true) + false

#if CXX20_CODE(true) + false
auto exampleCxx20Ranges()
{
    using namespace std::ranges;

    std::vector user_input {1, 10, 11, 18, 3, 4, 7, 17, 19, 18,};

    auto fibonacci_filtered = user_input
            | view::transform(calculateFibonacci)
            | view::filter([](auto number)  { return number <= 100; })
            | to<std::vector>();

    return fibonacci_filtered;
}
#endif

#define FUNC_PAIR(func)  std::make_tuple(func, #func)
int main()
{
    for (auto&& k: {
              FUNC_PAIR(exampleCxx11Stl),
              FUNC_PAIR(exampleCxx11User),
              CXX20_CODE(FUNC_PAIR(exampleCxx20Ranges),)
            }) {
        auto start {std::chrono::steady_clock::now()};
        auto res {std::get<0>(k)()};
        auto end {std::chrono::steady_clock::now()};
        std::chrono::duration<double> response_time {end-start};

        std::cout << std::get<1>(k) << ":\t{";
        for (auto v: res) { std::cout << v << ", "; }
        std::cout << "}\t"
          "Response time: " << 1000 * response_time.count() << "ms\n";
    }
    (42L).~ssize_t();
}
#endif  // #ifdef __cplusplus

#if defined __ecmascript || defined __javascript  // ECMAScript 6 (2015)
function calculateFibonacci(n)
{
    let res = [0, 1];
    for (let k = 2; k <= n; ++k) {
        res[k%2] = res[0] + res[1];
    }
    return res[n%2];
}

function example()
{
    let user_input = [1, 10, 11, 18, 3, 4, 7, 17, 19, 18,];

    let fibonacci_filtered = user_input
            .map(calculateFibonacci)
            .filter((number) => number <= 100);

    return fibonacci_filtered;
}

console.log(example())
#endif  // #if defined __ecmascript || defined __javascript
