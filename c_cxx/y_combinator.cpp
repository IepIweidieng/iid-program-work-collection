/* y_combinator.cpp
The Y combinator, implemented in ISO C++11.
Written by Iweidieng Iep on 2020-04-15.
Rev.1 by Iweidieng Iep on 2020-04-16.
- Now the function template `Y` accepts ordinary functions.
- Fix problems if the `self` argument uses `const T &`.
- Add more examples.
Rev.2 by Iweidieng Iep on 2020-04-16.
- Make the code conforms to ISO C++11.
- Eliminate function template `C`.
- Move class template `struct D` into function template `Y`.
*/

#include <functional>
#include <iostream>
#include <utility>

template <class T> struct FuncType {
};
template <class T> struct FuncType<std::function<T>> {
    using type = std::function<T>;
};
template <class T>
using RemoveCvrType =
    typename std::remove_cv<typename std::remove_reference<T>::type>::type;
template <class RetT, class... ArgTs> struct FuncType<RetT (*)(ArgTs...)> {
    using type = std::function<RetT(RemoveCvrType<ArgTs>...)>;
};
template <class RetT, class T, class... ArgTs>
struct FuncType<RetT (T::*)(ArgTs...) const> {
    using type = std::function<RetT(RemoveCvrType<ArgTs>...)>;
};
template <class T>
auto toFuncType(T obj) -> typename FuncType<decltype(&T::operator())>::type
{
    return obj;
}
template <class T> auto toFuncType(T obj) -> typename FuncType<T>::type
{
    return obj;
}
template <class T> using GetFuncType = decltype(toFuncType(std::declval<T>()));

template <class RetT, class... ArgTs,
          class FuncT = std::function<RetT(ArgTs...)>>
FuncT Y(const std::function<FuncT(std::function<RetT(ArgTs...)>)> &self_f)
{
    const struct D {
        const std::function<FuncT(FuncT)> self_f;
        FuncT operator()(const struct D &x) const
        {
            return self_f([=](ArgTs... args) -> RetT { return x(x)(args...); });
        }
    } x{self_f}; // Can be written as a lambda function in C++14
    return x(x);
}
template <class T> auto Y(const T &y) -> decltype(Y(GetFuncType<T>{y}))
{
    return Y(GetFuncType<T>{y});
}

int answer() { return 42; }

auto fact(const std::function<int(int)> &self) -> std::function<int(int)>
{
    return [=](int x) { return (x) ? x * self(x - 1) : 1; };
}

int main()
{
    std::cout
        << "answer(): " << Y([](std::function<int()> self) -> decltype(self) {
               return answer;
           })()
        << "\n8!: " << Y(fact)(8) << "\nfib(8): "
        << Y([](std::function<int(int)> self) -> decltype(self) {
               return [=](int x) {
                   return (x >> 1) ? self(x - 1) + self(x - 2) : x;
               };
           })(8)
        << "\nlcd(15, 72): "
        << Y([](std::function<int(int, int)> self) -> decltype(self) {
               return [=](int x, int y) {
                   return (x && y) ? self(x % y, y % x) : x + y;
               };
           })(15, 72)
        << "\nfor range(1, 42, 2): ",
        Y([=](std::function<int(int, int, int)> self) -> decltype(self) {
            return [=](int i, int n, int s) {
                return (i < n) ? std::cout << i << ' ', self(i + s, n, s) : 0;
            };
        })(1, 42, 2);
    std::cout << '\n';
}
