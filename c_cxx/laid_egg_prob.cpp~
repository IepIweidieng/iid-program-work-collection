/* laid_egg_prob.cpp
Calculate the probability and the expected value of the number
   of egg laying for a Minecraft chicken under normal conditions
   using a numeral method.

`pmf(t)`: The probability that the `gen`-th egg is laid at the `t`-th tick
`expect_mf(t)`: The expected value of the number of eggs laid at the `t`-th tick
`prob_cmf(t)`: The probability that the `gen`-th egg has been laid after the `t`-th tick passes
`expect_cmf(t)`: The expected value of the number of laid eggs after the `t`-th tick passes

Written by Iweidieng Iep on 2019-10-16.
Rev.1 by Iweidieng Iep on 2019-10-16.
   - `calc()`: Refine output; now it prints more `Graph` functions
   - `calc()`: Make the comment consistent with this file header
*/

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest in the software to the public domain. We make this dedication for the benefit of the public at large and to the detriment of our heirs and successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all present and future rights to this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
*/

/*
To compile: ```
g++ -o laid_egg_prob laid_egg_prob.cpp -Wall -Wextra -pedantic-errors --std=c++17 -O3 -flto
```

To run: ```
./laid_egg_prob [n]
```
where `n` represents the n-th generation (`0` for the beginning)
*/

#include <functional>
#include <map>
#include <utility>

#include <cstdlib>
#include <cstdio>

template <class T>
 constexpr const T kEpsilon = {};
template <>
 constexpr const float kEpsilon<float> = 1e-7;
template <>
 constexpr const double kEpsilon<double> = 1e-16;
template <>
 constexpr const long double kEpsilon<long double> = 1e-19;

template <class T, class Tr = T>
 extern inline T fuzz_cmp(const T& lhs, const Tr& rhs = {})
{
    const T diff = lhs - rhs;
    return (kEpsilon<T> && diff > -kEpsilon<T> && diff < kEpsilon<T>)
          ? T{} : diff;
}
template <class T, class Tr = T>
 struct Fuzz_less {
    bool operator()(const T& lhs, const Tr& rhs) const
      { return fuzz_cmp(lhs, rhs) < 0; }
};

template <class T, class Tv>
 struct Interval_set
      : public std::map<T, std::pair<T, Tv>, Fuzz_less<T>> {
    template <template <class...> class Tp>
     using Item_tp = Tp<T, std::pair<T, Tv>>;
    using Map_t = Item_tp<std::map>;
    using Pair_t = Item_tp<std::pair>;
    using Iter_ret_t = std::pair<typename Map_t::iterator, bool>;

    static constexpr const auto bg = [](auto&& it) -> auto&&  { return it->first; };
    static constexpr const auto ed = [](auto&& it) -> auto&&  { return it->second.first; };
    static constexpr const auto vl = [](auto&& it) -> auto&&  { return it->second.second; };

    // Returns `{iter_interval_contains_at, is_created}`
    Iter_ret_t insert_create(const T& at, const Tv& val, bool is_tail = false)
    {
        T key = {};
        bool res = true;
        if (!this->empty()) {
            const auto upper = this->upper_bound(at);
            auto less_eq = upper;
            if (upper != this->cbegin()) {
                --less_eq;
                if (at >= bg(less_eq) && at <= ed(less_eq)) {
                    return {less_eq, false};
                }
                if (at == bg(less_eq) - 1
                  && (is_tail && !fuzz_cmp(val, vl(less_eq)))) {
                    auto less = less_eq;
                    if (less_eq != this->cbegin()
                      && ((void)--less,
                          at == ed(less) + 1)) {
                        ed(less) = ed(less_eq);
                        key = bg(less);
                        res = false;
                    }
                    else {
                        const auto tmp = this->emplace(at, std::move(less_eq->second));
                        key = bg(tmp.first);
                        res = tmp.second;
                    }
                    this->erase(at+1);
                    return {this->find(key), res};
                }
                if (at == ed(less_eq) + 1
                  && !fuzz_cmp(val, vl(less_eq))) {
                    ed(less_eq) = at;
                    key = bg(less_eq);
                    res = false;
                }
            }
            if (upper != this->cend()) {
                if (at == bg(upper) - 1
                  && (is_tail && !fuzz_cmp(val, vl(upper)))) {
                    if (!res) {
                        ed(less_eq) = ed(upper);
                        key = bg(less_eq);
                        res = false;
                    }
                    else {
                        const auto tmp = this->emplace(at, std::move(upper->second));
                        key = bg(tmp.first);
                        res = tmp.second;
                    }
                    this->erase(at+1);
                    return {this->find(key), res};
                }
            }
            if (!res) { return {this->find(key), true}; }
        }
        return this->insert({at, {at, val}});
    }

    // Returns `interval_added`
    Pair_t add_split(const T& key, const T& at, const Tv& val = {})
    {
        const auto& it = this->find(key);
        auto sec = it->second;
        if (at > bg(it)) { ed(it) = at-1; }
        else { this->erase(it); }
        sec.second += val;
        return *this->emplace(at, sec).first;
    }
    
    // Returns `{iter_interval_added, is_added}`
    Iter_ret_t add(const T& lhs, const T& rhs, const Tv& val)
    {
        if (lhs >= rhs) { return {this->end(), false}; }

        auto [itr, resr] = insert_create(rhs, val, true);
        Pair_t intr = *itr;
        auto [itl, resl] = insert_create(lhs, val);
        Pair_t intl = *itl;
        if (!resr) { intr = add_split(bg(&intr), rhs, val); }
        if (!resl) { intl = add_split(bg(&intl), lhs, val); }
        auto it = this->find(bg(&intl));
        auto end = this->find(bg(&intr));
        if (it != end) {
            do {
                if (bg(it) != bg(&intl)) { vl(it) += val; }
                auto it_n = it;
                ++it_n;
                if (bg(it_n)-1 >= ed(it)+1) {
                    if (!fuzz_cmp(vl(it), val)) {
                        ed(it) = bg(it_n)-1;
                    }
                    else {
                        it = this->insert({ed(it)+1, {bg(it_n)-1, val}}).first;
                        end = this->find(bg(&intr));
                    }
                }
            } while (++it != end);
            if (!fuzz_cmp(vl(it) -= val)) { this->erase(it); }
        }
        return {this->find(bg(&intl)), true};
    }
    Iter_ret_t add(const Pair_t& intv)
      { return add(bg(&intv), ed(&intv)+1, vl(&intv)); }

    // Returns `{iter_interval_set, is_set}`
    Iter_ret_t set(const T& lhs, const T& rhs, const Tv& val)
    {
        if (lhs >= rhs) { return {this->end(), false}; }

        auto [itr, resr] = insert_create(rhs, val, true);
        Pair_t intr = *itr;
        auto [itl, resl] = insert_create(lhs, val);
        Pair_t intl = *itl;
        if (!resr) { intr = add_split(bg(&intr), rhs); }
        if (!resl) { intl = add_split(bg(&intl), lhs); }
        auto it = this->find(bg(&intl));
        auto end = this->find(bg(&intr));
        ed(it) = bg(end) - 1;
        if (it++ != end) {
            this->erase(it, end);
            it = this->find(bg(&intr));
            if (!fuzz_cmp(vl(it) = vl(&intr))) { this->erase(it); }
        }
        return {this->find(bg(&intl)), true};
    }
    Iter_ret_t set(const Pair_t& intv)
      { return set(bg(&intv), ed(&intv)+1, vl(&intv)); }

    void show(FILE* pf = stdout) const
    {
        for (const auto& m: *this) {
            if (bg(&m) == ed(&m)) {
                fprintf(pf, "%zu: %.12f\n", bg(&m), vl(&m));
            }
            else {
                fprintf(pf, "[%zu, %zu]: %.12f\n", bg(&m), ed(&m), vl(&m));
            }
        }
        fputc('\n', pf);
    }

    const Tv& operator()(const T& at) const
    {
        if (!this->empty()) {
            const auto upper = this->upper_bound(at);
            auto less_eq = upper;
            if (upper != this->cbegin()) {
                --less_eq;
                if (at >= bg(less_eq) && at <= ed(less_eq)) {
                    return vl(less_eq);
                }
            }
        }
        return {};
    }
    Tv& operator()(const T& at)
      { return const_cast<Tv&>(std::as_const(*this)(at)); }

    Interval_set getIntegral() const
    {
        Tv cumu = 0.0;
        Interval_set inf;
        for (const auto& [bg, sec]: *this) {
            const ssize_t len_intv = sec.first + 1 - bg;
            for (ssize_t k = 0; k < len_intv; ++k) {
                inf.set(bg + k, bg + k + 1, cumu + (k+1) * sec.second);
            }
            cumu += len_intv * sec.second;
        }
        return inf;
    }
    Interval_set getIntegral(const T& lower) const
    {
        Interval_set inf = getIntegral();
        inf.begin();
        inf.add(bg(inf.cbegin()), ed(inf.crbegin())+1, -inf(lower));
        return inf;
    }
    T getIntegral(const T& lower, const T& upper) const
    {
        Interval_set inf = getIntegral();
        return inf(upper) - inf(lower);
    }
};

using Graph = Interval_set<ssize_t, double>;

constexpr const ssize_t kBTick = 6000;
constexpr const ssize_t kETick = 12000;
constexpr const double kProb = 1.0/(kETick-kBTick);

void declshow(
  const char* title, const std::function<void(void)>& show_func, FILE* fp = stdout)
{
    fputs(title, fp);
    fputs('\n', fp);
    fgetc(stdin);
    show_func();
    fgetc(stdin);
}

void calc(const ssize_t gen)
{
    // `pmf(t)`: The probability that the `gen`-th egg is laid at the `t`-th tick
    Graph pmf = {{{kBTick, {kETick-1, kProb}}}};
    // `expect_mf(t)`: The expected value of the number of eggs laid at the `t`-th tick
    Graph expect_mf = pmf;

    for (ssize_t g = 1; g <= gen; ++g) {
        // `next_pmf(t)`: The probability that the `g`-th egg is laid at the tick
        Graph next_pmf = {};
        for (ssize_t k = kBTick, n = kETick; k < n; ++k) {
            for (const auto& [bg, sec]: pmf) {
                next_pmf.add(bg + k, sec.first+1 + k, kProb * sec.second);
            }
        }
        pmf = std::move(next_pmf);
        for (const auto& m: pmf) { expect_mf.add(m); }
    }

    declshow("pmf", [&]() { pmf.show(); });
    declshow("expect_mf", [&]() { expect_mf.show(); });

    // `prob_cmf(t)`: The probability that the `gen`-th egg has been laid after the `t`-th tick passes
    Graph prob_cmf = pmf.getIntegral();
    declshow("prob_cmf", [&]() { prob_cmf.show(); });

    // `expect_cmf(t)`: The expected value of the number of laid eggs after the `t`-th tick passes
    Graph expect_cmf = expect_mf.getIntegral();
    declshow("expect_cmf", [&]() { expect_cmf.show(); });
}

int main(int argn, char *argv[])
  { calc((argn > 1) ? atol(argv[1]) : 0); }
