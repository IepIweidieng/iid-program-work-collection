/*
A any-bit counter implemented with C++ templates,
   written by Iweidieng Iep on 2019-03-09.
Require C++11.
*/

/* N-bit Hex_class */
template <bool...> struct Hex {};

/* 4-bit Hex_class */
template <>
  struct Hex<0, 0, 0, 0> {static constexpr unsigned long long int value {0x0};};
template <>
  struct Hex<0, 0, 0, 1> {static constexpr unsigned long int long value {0x1};};
template <>
  struct Hex<0, 0, 1, 0> {static constexpr unsigned int long long value {0x2};};
template <>
  struct Hex<0, 0, 1, 1> {static constexpr long unsigned long int value {0x3};};
template <>
  struct Hex<0, 1, 0, 0> {static constexpr long unsigned int long value {0x4};};
template <>
  struct Hex<0, 1, 0, 1> {static constexpr int unsigned long long value {0x5};};
template <>
  struct Hex<0, 1, 1, 0> {static constexpr long long unsigned int value {0x6};};
template <>
  struct Hex<0, 1, 1, 1> {static constexpr long int unsigned long value {0x7};};
template <>
  struct Hex<1, 0, 0, 0> {static constexpr int long unsigned long value {0x8};};
template <>
  struct Hex<1, 0, 0, 1> {static constexpr long long int unsigned value {0x9};};
template <>
  struct Hex<1, 0, 1, 0> {static constexpr long int long unsigned value {0xA};};
template <>
  struct Hex<1, 0, 1, 1> {static constexpr int long long unsigned value {0xB};};
template <>
  struct Hex<1, 1, 0, 0> {constexpr static unsigned long long int value {0xC};};
template <>
  struct Hex<1, 1, 0, 1> {constexpr static unsigned long int long value {0xD};};
template <>
  struct Hex<1, 1, 1, 0> {constexpr static unsigned int long long value {0xE};};
template <>
  struct Hex<1, 1, 1, 1> {constexpr static long unsigned long int value {0xF};};


/* Logical operations */

/* Variadic logical `true` operation */
template <bool...>
  struct True {
    static constexpr bool value {true};
};

/* Variadic logical `false` operation */
template <bool...>
  struct False {
    static constexpr bool value {false};
};

/* Unary logical `buf` operation */
template <bool b>
  struct Buf {
    static constexpr bool value {true};
};
template <>
  struct Buf<0> {
    static constexpr bool value {false};
};

/* Unary logical `not` operation */
template <bool>
  struct Not {
    static constexpr bool value {false};
};
template <>
  struct Not<0> {
    static constexpr bool value {true};
};

/* Variadic logical `and` operation */
template <bool...>
  struct And {
    static constexpr bool value {true};
};
template <bool b0, bool... bs>
  struct And<b0, bs...> {
    static constexpr bool value {And<bs...>::value};
};
template <bool... bs>
  struct And<0, bs...> {
    static constexpr bool value {false};
};

/* Variadic logical `or` operation */
template <bool...>
  struct Or {
    static constexpr bool value {false};
};
template <bool b0, bool... bs>
  struct Or<b0, bs...> {
    static constexpr bool value {Or<bs...>::value};
};
template <bool... bs>
  struct Or<1, bs...> {
    static constexpr bool value {true};
};

/* Variadic logical `xor`/`not equal` operation */
template <bool...>
  struct Xor {
    static constexpr bool value {false};
};
template <bool... bs>
  struct Xor<0, bs...> {
    static constexpr bool value {Xor<bs...>::value};
};
template <bool... bs>
  struct Xor<1, bs...> {
    static constexpr bool value {Not<Xor<bs...>::value>::value};
};

/* Variadic logical `imply`/`less than or equal` operation */
template <bool...>
  struct Imp {
    static constexpr bool value {true};
};
template <bool... bs>
  struct Imp<1, 0, bs...> {
    static constexpr bool value {false};
};
template <bool b0, bool b1, bool... bs>
  struct Imp<b0, b1, bs...> {
    static constexpr bool value {Imp<b1, bs...>::value};
};


/* Functional operations */

/* N-bit Hex_class reducer */
/* Usage: Reduce<Opr, Hex_class>::value => single value */
template <template <bool...> class Opr, class H> struct Reduce;
// `Opr` is vararg
template <
      template <bool...> class Opr,
      template <bool...> class H, bool... bs>
  struct Reduce<Opr, H<bs...>> {
    static constexpr auto value {
      Opr<bs...>::value};
};
// `Opr` is binary
template <
      template <bool, bool> class Opr,
      template <bool...> class H, bool b0, bool b1>
  struct Reduce<Opr, H<b0, b1>> {
    static constexpr auto value {
      Opr<b0, b1>::value};
};
// `Opr` is binary, but the Hex_class has more than 2 bits
template <
      template <bool, bool> class Opr,
      template <bool...> class H, bool b0, bool b1, bool b2, bool... bs>
  struct Reduce<Opr, H<b0, b1, b2, bs...>> {
    static constexpr auto value {
      Opr<b0, Reduce<Opr, H<b1, b2, bs...>>::value>::value};
};

/* N-bit Hex_class mapper */
/* Usage: Map_T<Opr, Hex<bits...>> => Hex<new_bits...>
          Map_T<Opr, Hex<bits0...>, Hex<bits1...>> => Hex<new_bits...>
*/
template <template <bool...> class Opr, class... Hs> struct Map;
template <template <bool...> class Opr, class... Hs>
  using Map_T = typename Map<Opr, Hs...>::type;

// For 1 Hex_class
template <
      template <bool...> class Opr,
      template <bool...> class H, bool... bs>
  struct Map<Opr, H<bs...>> {
    using type = H<Opr<bs>::value...>;
};
// For 2 Hex_classes
template <
      template <bool...> class Opr,
      template <bool...> class H0, bool... bs0,
      template <bool...> class H1, bool... bs1>
  struct Map<Opr, H0<bs0...>, H1<bs1...>> {
    using type = H0<Opr<bs0, bs1>::value...>;
};
// For 3 or more Hex_classes
template <
      template <bool...> class Opr,
      class H0, class H1, class H2, class... Hs>
  struct Map<Opr, H0, H1, H2, Hs...> {
    using type = Map_T<Opr, Map_T<Opr, Map_T<Opr, H0, H1>, H2>, Hs...>;
};

/* Selector nth class (n>=0) */
template <int n, bool cond, class H0, class... Hs> struct Select_helper;
template <int n, bool cond, class H0, class... Hs>
  using Select_helper_T = typename Select_helper<n, cond, H0, Hs...>::type;
template <int n, class H0, class... Hs>
  struct Select_helper<n, 0, H0, Hs...> {
    using type = H0;
};
template <int n, class H0, class H1, class... Hs>
  struct Select_helper<n, 1, H0, H1, Hs...> {
    using type = Select_helper_T<n-1, (n>1), H1, Hs...>;
};

template <int n, class H0, class... Hs>
  using Select_T = Select_helper_T<n, (n>0), H0, Hs...>;


/* Apply if `cond` is true */
/* Usage: Apply_if_T<Opr, [true|false], Hex_class>
             if true => Opr<Hex_class>::type => new Hex_class
             if false => Hex_class
*/
template <template <class> class Opr, bool cond, class H>
  using Apply_if_T = Select_T<cond, H, typename Opr<H>::type>;

/* Apply n times, but using logarithm depth of recursions
      to work around the limitation of template instantiation depth
*/
/* Usage: Apply_T<Opr, Hex_class, n> => A new Hex_class */
// \sum_{k=1}^{22}(8 ^ k) = 84,327,972,908,386,521,672 ~= 2 ^ 66.2
//    => Enough to exhaust all the possible `long long int` values
constexpr int level_limit {22};
template <template <class> class Opr, int n, int lv, bool cond, class H>
  struct Apply_helper;
template <template <class> class Opr, int n, int lv, bool cond, class H>
  using Apply_helper_T = typename Apply_helper<Opr, n, lv, cond, H>::type;

// If `cond` is false
template <template <class> class Opr, int n, int lv, class H>
  struct Apply_helper<Opr, n, lv, 0, H> {
    using type = H;
    static constexpr int idx {n};
};
// If `cond` is true
template <template <class> class Opr, int n, int lv, class H>
  struct Apply_helper<Opr, n, lv, 1, H> {
    // Apply up to \sum_{k=1}^{22}(8 ^ `level_limit`) times
    static constexpr bool cond0 {lv < level_limit && n > 0};
    using Res0 = Apply_helper<Opr,
        n - cond0, lv + 1, cond0,
        Apply_if_T<Opr, cond0, H>>;
    static constexpr bool cond1 {lv < level_limit && Res0::idx > 0};
    using Res1 = Apply_helper<Opr,
        Res0::idx - cond1, lv + 1, cond1,
        Apply_if_T<Opr, cond1, typename Res0::type>>;
    static constexpr bool cond2 {lv < level_limit && Res1::idx > 0};
    using Res2 = Apply_helper<Opr,
        Res1::idx - cond2, lv + 1, cond2,
        Apply_if_T<Opr, cond2, typename Res1::type>>;
    static constexpr bool cond3 {lv < level_limit && Res2::idx > 0};
    using Res3 = Apply_helper<Opr,
        Res2::idx - cond3, lv + 1, cond3,
        Apply_if_T<Opr, cond3, typename Res2::type>>;
    static constexpr bool cond4 {lv < level_limit && Res3::idx > 0};
    using Res4 = Apply_helper<Opr,
        Res3::idx - cond4, lv + 1, cond4,
        Apply_if_T<Opr, cond4, typename Res3::type>>;
    static constexpr bool cond5 {lv < level_limit && Res4::idx > 0};
    using Res5 = Apply_helper<Opr,
        Res4::idx - cond5, lv + 1, cond5,
        Apply_if_T<Opr, cond5, typename Res4::type>>;
    static constexpr bool cond6 {lv < level_limit && Res5::idx > 0};
    using Res6 = Apply_helper<Opr,
        Res5::idx - cond6, lv + 1, cond6,
        Apply_if_T<Opr, cond6, typename Res5::type>>;
    static constexpr bool cond7 {lv < level_limit && Res6::idx > 0};
    using Res7 = Apply_helper<Opr,
        Res6::idx - cond7, lv + 1, cond7,
        Apply_if_T<Opr, cond7, typename Res6::type>>;
    // Apply again if not enough
    static constexpr bool cond8 {lv == 0 && Res7::idx > 0};
    using Res8 = Apply_helper<Opr,
        Res7::idx - cond8, lv, cond8,
        Apply_if_T<Opr, cond8, typename Res7::type>>;

    using type = typename Res8::type;
    static constexpr int idx {Res8::idx};
};

template <template <class> class Opr, int n, class H>
  using Apply = Apply_helper<Opr, n, 0, (n>0), H>;
template <template <class> class Opr, int n, class H>
  using Apply_T = typename Apply<Opr, n, H>::type;


/* Hex_class basic bitwise manipulations */

/* Hex_class width */
/* Usage: Size<Hex_class>::value => Count of bits */
template <class H> struct Size;
template <template <bool...> class H, bool... bs>
  struct Size<H<bs...>> {
    static constexpr unsigned int value {sizeof...(bs)};
};

/* Decompose a Hex_class into car and cdr */
template <class H> struct Decons;
template <template <bool...> class H, bool b0, bool... bs>
  struct Decons<H<b0, bs...>> {
    static constexpr bool car {b0};
    using Cdr = H<bs...>;
};

/* Get the most significant bit of the Hex_class */
template <class H>
  struct Car {
    static constexpr bool value {Decons<H>::car};
};

/* Get the Hex_class without the original most significant bit */
template <class H>
  struct Cdr {
    using type = typename Decons<H>::Cdr;
};
template <class H>
  using Cdr_T = typename Cdr<H>::type;


/* Concatenation of any number of any-bit Hex_classes */
/* Usage: Cat_T<Hex<bits0...>, Hex<bits1...>, ...>
             => Hex<bits0..., bits1..., ...>
*/
template <class... Hs> struct Cat;
// `*_T`: Hex_class type
template <class... Hs>
  using Cat_T = typename Cat<Hs...>::type;

// 1 Hex_class
template <class H>
  struct Cat<H> {
    using type = H;
};
// 2 Hex_classes
template <
    template <bool...> class H0, bool... bs0,
    template <bool...> class H1, bool... bs1>
  struct Cat<H0<bs0...>, H1<bs1...>> {
    using type = H0<bs0..., bs1...>;
};
// 3 or more Hex_classes
template <class H0, class H1, class H2, class... Hs>
  struct Cat<H0, H1, H2, Hs...> {
    using type = Cat_T<Cat_T<Cat_T<H0, H1>, H2>, Hs...>;
};


/* Concate n bits into a Hex_class from the left */
template <class H, bool... lbs> struct L_bcat;
template <template <bool...> class H, bool... bs, bool... lbs>
  struct L_bcat<H<bs...>, lbs...> {
    using type = H<lbs..., bs...>;
};
template <class H, bool... lbs>
  using L_bcat_T = typename L_bcat<H, lbs...>::type;

/* Concate n bits into a Hex_class from the right */
template <class H, bool... rbs> struct R_bcat;
template <template <bool...> class H, bool... bs, bool... rbs>
  struct R_bcat<H<bs...>, rbs...> {
    using type = H<bs..., rbs...>;
};
template <class H, bool... rbs>
  using R_bcat_T = typename R_bcat<H, rbs...>::type;


/* Fill n-bit with `b` */
/* Usage: Fill_T<Hex<...>, [true|false]>
             if true => Hex<true, true, ...>
             if false => Hex<false, false, ...>
*/
template <class H, bool b> struct Fill;
template <class H>
  struct Fill<H, 0> {
    using type = Map_T<False, H>;
};
template <class H>
  struct Fill<H, 1> {
    using type = Map_T<True, H>;
};
template <class H, bool b>
  using Fill_T = typename Fill<H, b>::type;


/* N-bit left shifts */
template <template <bool...> class Opr>
  struct L_base {
    template <class H>
      using L_base_prime = R_bcat<Cdr_T<H>, Opr<Car<H>::value>::value>;
    template <class H, int n>
      using L_base_T = Apply_T<L_base_prime, n, H>;
};
template <template <bool...> class Opr, class H, int n>
  using L_base_T = typename L_base<Opr>::template L_base_T<H, n>;

/* N-bit left circular shift */
template <class H, int n>
  using L_rotate_T = L_base_T<Buf, H, n>;

/* N-bit left logical/arithmetic shift */
template <class H, int n>
  using L_shift_T = L_base_T<False, H, n>;
template <class H, int n>
  using L_lshift_T = L_shift_T<H, n>;
template <class H, int n>
  using L_ashift_T = L_shift_T<H, n>;

/* N-bit left shift, but pads 1s */
template <class H, int n>
  using L_revshift_T = L_base_T<True, H, n>;

/* N-bit right circular shift */
template <class H, int n>
  using R_rotate_T = L_rotate_T<H, Size<H>::value - n>;

/* N-bit right logical shift */
template <class H, int n>
  using R_shift_T = R_rotate_T<L_shift_T<R_rotate_T<H, n>, n>, n>;
template <class H, int n>
  using R_lshift_T = R_shift_T<H, n>;

/* N-bit right shift, but pads 1s */
template <class H, int n>
  using R_revshift_T = R_rotate_T<L_revshift_T<R_rotate_T<H, n>, n>, n>;

/* N-bit right arithmetic shift */
template <class H, bool b0, int n> struct R_ashift_helper;
// The most significant bit of the Hex_class is 0
template <class H, int n>
  struct R_ashift_helper<H, 0, n> {
    using type = R_shift_T<H, n>;
};
// The most significant bit of the Hex_class is 1
template <class H, int n>
  struct R_ashift_helper<H, 1, n> {
    using type = R_revshift_T<H, n>;
};
template <class H, int n>
  using R_ashift_T = typename R_ashift_helper<H, Car<H>::value, n>::type;


/* Hex_class width manipulations */

/* An empty Hex_class */
template <template <bool...> class H>
  using Empty = H<>;

/* Remove n bits from the msb of a Hex_class */
template <class H, int n>
  using L_pop = Apply<Cdr, n, H>;
template <class H, int n>
  using L_pop_T = typename L_pop<H, n>::type;

/* Remove n bits from the lsb of a Hex_class */
template <class H, int n>
  using R_pop = L_pop<R_rotate_T<H, n>, n>;
template <class H, int n>
  using R_pop_T = typename R_pop<H, n>::type;


/* Add n `b`s to a Hex_class */
template <template <class, bool...> class Opr>
  struct Push_base {
    template <class H, bool b>
      using Push_prime = Opr<H, b>;
    // Add `0`s
    template <class H>
      using Push_0_prime = Push_prime<H, 0>;
    template <class H, int n>
      using Push_0_T = Apply_T<Push_0_prime, n, H>;
    // Add `1`s
    template <class H>
      using Push_1_prime = Push_prime<H, 1>;
    template <class H, int n>
      using Push_1_T = Apply_T<Push_1_prime, n, H>;
    // Add `b`s
    template <class H, int n, bool b> struct Push;
    template <class H, int n>
      struct Push<H, n, 0> {
        using type = Push_0_T<H, n>;
    };
    template <class H, int n>
      struct Push<H, n, 1> {
        using type = Push_1_T<H, n>;
    };
};
template <template <class, bool...> class Opr, class H, int n, bool b>
  using Push_base_opr = typename Push_base<Opr>::template Push<H, n, b>;

/* Add n `b`s from the msb of a Hex_class */
template <class H, int n, bool b>
  using L_push = Push_base_opr<L_bcat, H, n, b>;
template <class H, int n, bool b>
  using L_push_T = typename L_push<H, n, b>::type;

/* Add n `b`s from the lsb of a Hex_class */
template <class H, int n, bool b>
  using R_push = Push_base_opr<R_bcat, H, n, b>;
template <class H, int n, bool b>
  using R_push_T = typename R_push<H, n, b>::type;


/* Make a new Hex_class with n `b`s */
template <template <bool...> class H, int n, bool b>
  using Make_T = L_push_T<Empty<H>, n, b>;


/* Fit a Hex_class to n-bit */
template <
      template <class, int, bool> class Push_opr,
      template <class, int> class Pop_opr,
      template <bool...> class Bit_opr>
  struct Fit_base {
    template <class H, bool is_less, int n> struct Fit_helper;
    // `H` is narrower than n bits => Pad `H` with 0s
    template <class H, int n>
      struct Fit_helper<H, 0, n> {
        using type = typename Push_opr<H, n - Size<H>::value, Bit_opr<Car<H>::value>::value>::type;
    };
    // `H` is wider than n bits => Truncate `H`
    template <class H, int n>
      struct Fit_helper<H, 1, n> {
        using type = typename Pop_opr<H, Size<H>::value - n>::type;
    };
    template <class H, int n>
      using Fit_T = typename Fit_helper<H, (n < Size<H>::value), n>::type;
};
template <
      template <class, int, bool> class Push_opr,
      template <class, int> class Pop_opr,
      template <bool...> class Bit_opr,
      class H, int n>
  using Fit_base_T = typename Fit_base<Push_opr, Pop_opr, Bit_opr>::template Fit_T<H, n>;

/* Adjust the left bits of a Hex_class to fit in n-bit */
template <template <bool...> class Bit_opr, class H, int n>
  using L_fit_base_T = Fit_base_T<L_push, L_pop, Bit_opr, H, n>;

/* Adjust the left bits of a Hex_class to fit in n-bit, padding `0`s when needed */
template <class H, int n>
  using L_fit_T = L_fit_base_T<False, H, n>;
template <class H, int n>
  using L_lfit_T = L_fit_T<H, n>;

/* Adjust the left bits of a Hex_class to fit in n-bit, preserving the sign bit */
template <class H, int n>
  using L_afit_T = L_fit_base_T<Buf, H, n>;

/* Adjust the left bits of a Hex_class to fit in n-bit, padding `1`s when needed */
template <class H, int n>
  using L_revfit_T = L_fit_base_T<True, H, n>;


/* Adjust the right bits of a Hex_class to fit in n-bit */
template <template <bool...> class Bit_opr, class H, int n>
  using R_fit_base_T = Fit_base_T<R_push, R_pop, Bit_opr, H, n>;

/* Adjust the right bits of a Hex_class to fit in n-bit, padding `0`s when needed */
template <class H, int n>
  using R_fit_T = R_fit_base_T<False, H, n>;
template <class H, int n>
  using R_lfit_T = R_fit_T<H, n>;
template <class H, int n>
  using R_afit_T = R_fit_T<H, n>;

/* Adjust the right bits of a Hex_class to fit in n-bit, padding `1`s when needed */
template <class H, int n>
  using R_revfit_T = R_fit_base_T<True, H, n>;


/* Decompose a Hex_class into MSB and LSB */
template <class H>
  using Msb_T = R_fit_T<H, Size<H>::value / 2>;
template <class H>
  using Lsb_T = L_fit_T<H, (Size<H>::value+1) / 2>;


/* Make two Hex_classes equally wide */
/* Usage: Promote_[L|R]<Hex_class_lhs, Hex_class_rhs>
             => promoted Hex_class_[lhs|rhs]
*/
template <class H0, class H1, bool is_less>
  struct Promote_helper;
template <class H0, class H1, bool is_less>
  using Promote_helper_L = typename Promote_helper<H0, H1, is_less>::Lhs;
template <class H0, class H1, bool is_less>
  using Promote_helper_R = typename Promote_helper<H0, H1, is_less>::Rhs;
// `H0` is narrower than `H1` => Widen `H0`
template <class H0, class H1>
  struct Promote_helper<H0, H1, 1> {
    using Lhs = L_fit_T<H0, Size<H1>::value>;
    using Rhs = H1;
};
// `H0` is wider than `H1` => Widen `H1`
template <class H0, class H1>
  struct Promote_helper<H0, H1, 0> {
    using Lhs = H0;
    using Rhs = L_fit_T<H1, Size<H0>::value>;
};

template <class H0, class H1>
  using Promote = Promote_helper<
      H0, H1,
      (Size<H0>::value < Size<H1>::value)>;
template <class H0, class H1>
  using Promote_L = typename Promote<H0, H1>::Lhs;
template <class H0, class H1>
  using Promote_R = typename Promote<H0, H1>::Rhs;

/* `Map` with promotion */
template <template <bool...> class Opr, class H0, class H1>
  using Promote_map_T = Map_T<Opr, Promote_L<H0, H1>, Promote_R<H0, H1>>;


/* Bitwise operations */

/* Unary n-bit bitwise `complement` operation */
template <class H>
  using Compl_T = Map_T<Not, H>;

/* Binary n-bit bitwise `and` operation */
template <class H0, class H1>
  using Band_T = Promote_map_T<And, H0, H1>;

/* Binary n-bit bitwise `or` operation */
template <class H0, class H1>
  using Bor_T = Promote_map_T<Or, H0, H1>;

/* Binary n-bit bitwise `xor` operation */
template <class H0, class H1>
  using Bxor_T = Promote_map_T<Xor, H0, H1>;

/* Binary n-bit bitwise `imply` operation */
template <class H0, class H1>
  using Bimp_T = Promote_map_T<Imp, H0, H1>;


/* N-bit Hex_class comparator */
/* Usage: [Neq|Equ]<Hex_class0, Hex_class1>::value */
template <class H0, class H1>
  struct Neq_prime {
    static constexpr bool value {true};
};
template <class H>
  struct Neq_prime<H, H> {
    static constexpr bool value {false};
};
template <class H0, class H1>
  using Neq = Neq_prime<Promote_L<H0, H1>, Promote_R<H0, H1>>;
template <class H0, class H1>
  using Equ = Not<Neq<H0, H1>::value>;

template <class H0, class H1>
  using Leq = Reduce<And, Bimp_T<H0, H1>>;
template <class H0, class H1>
  using Geq = Leq<H1, H0>;
template <class H0, class H1>
  using Gtr = Not<Leq<H0, H1>::value>;
template <class H0, class H1>
  using Lss = Gtr<H1, H0>;


/* N-bit Hex_class successor */
template <class H, bool carry> struct Suc_helper;
template <class H, bool carry>
  using Suc_helper_T = typename Suc_helper<H, carry>::type;

template <class H>
  struct Suc {
    using type = Suc_helper_T<H, Reduce<And, Lsb_T<H>>::value>;
};
template <class H>
  using Suc_T = typename Suc<H>::type;

template <class H>
  struct Suc_helper<H, 0> {
    using type = Cat_T<Msb_T<H>, Suc_T<Lsb_T<H>>>;
};
template <class H>
  struct Suc_helper<H, 1> {
    using type = R_fit_T<Suc_T<Msb_T<H>>, Size<H>::value>;
};

/* 1-bit Hex_class successor */
template <>
  struct Suc<Hex<0>> {using type = Hex<1>;};
template <>
  struct Suc<Hex<1>> {using type = Hex<0>;};

/* 4-bit Hex_class successor */
template <bool b3, bool b2, bool b1>
  struct Suc<Hex<b3, b2, b1, 0>> {using type = Hex<b3, b2, b1, 1>;};
template <bool b3, bool b2>
  struct Suc<Hex<b3, b2, 0, 1>> {using type = Hex<b3, b2, 1, 0>;};
template <bool b3>
  struct Suc<Hex<b3, 0, 1, 1>> {using type = Hex<b3, 1, 0, 0>;};
template <>
  struct Suc<Hex<0, 1, 1, 1>> {using type = Hex<1, 0, 0, 0>;};
template <>
  struct Suc<Hex<1, 1, 1, 1>> {using type = Hex<0, 0, 0, 0>;};


/* N-bit Hex_class predecessor */
template <class H>
  struct Pred {
    using type = Compl_T<Suc_T<Compl_T<H>>>;
};
template <class H>
  using Pred_T = typename Pred<H>::type;


/* Get non-reference type */
template <class H>
  struct Remove_ref {using type = H;};
template <class H>
  struct Remove_ref<H&> {using type = H;};
template <class H>
  struct Remove_ref<H&&> {using type = H;};
template <class H>
  using Remove_ref_T = typename Remove_ref<H>::type;


/* Cast bool value [true|false] to struct [True<>|False<>] */
template <bool> struct Bool;
template <>
  struct Bool<0> {using type = False<>;};
template <>
  struct Bool<1> {using type = True<>;};
template <bool b>
  using Bool_T = typename Bool<b>::type;


/* Functions, with lowercased names */

/* Apply if `Cond` is true */
/* Usage: apply_if<Hex_class, [True|False]>(function)
      function: Accepts an instance of Hex_class
                  Returns an instance of new Hex_class
*/
template <class H, class F>
  constexpr inline auto apply_if_helper(F&& f, True<>&&)  { return f(H{}); }
template <class H, class F>
  constexpr inline auto apply_if_helper(F&&, False<>&&)  { return H{}; }

template <class H, bool b, class F>
  constexpr inline auto apply_if(F&& f)  { return apply_if_helper<H>(f, Bool_T<b>{}); }

/* Apply n times, but using logarithm depth of recursions
      to work around the limitation of stack level */
template <class H, class Hn>
  struct Apply_state_wrapper {
    using type = H;
    using Idx = Hn;
};

// If `cond` is false
template <class H, class Hn, int lv, class F>
    constexpr inline auto apply_helper(F&&, False<>&&)
  { return Apply_state_wrapper<H, Hn>{}; }
// If `cond` is true
template <class H, class Hn, int lv, class F>
  constexpr inline auto apply_helper(F&& f, True<>&&)
{
    // Apply up to \sum_{k=1}^{22}(8 ^ `level_limit`) times
    constexpr bool cond0 {lv < level_limit && Gtr<Hn, Hex<0>>::value};
    auto&& app0 {apply_if<H, cond0>(f)};
    auto&& res0 {apply_helper<
        Remove_ref_T<decltype(app0)>,
        Apply_if_T<Pred, cond0, Hn>, lv + 1>(
          f, Bool_T<cond0>{})};
    using Res0 = Remove_ref_T<decltype(res0)>;

    constexpr bool cond1 {lv < level_limit && Gtr<typename Res0::Idx, Hex<0>>::value};
    auto&& app1 {apply_if<typename Res0::type, cond1>(f)};
    auto&& res1 {apply_helper<
        Remove_ref_T<decltype(app1)>,
        Apply_if_T<Pred, cond1, typename Res0::Idx>, lv + 1>(
          f, Bool_T<cond1>{})};
    using Res1 = Remove_ref_T<decltype(res1)>;

    constexpr bool cond2 {lv < level_limit && Gtr<typename Res1::Idx, Hex<0>>::value};
    auto&& app2 {apply_if<typename Res1::type, cond2>(f)};
    auto&& res2 {apply_helper<
        Remove_ref_T<decltype(app2)>,
        Apply_if_T<Pred, cond2, typename Res1::Idx>, lv + 1>(
          f, Bool_T<cond2>{})};
    using Res2 = Remove_ref_T<decltype(res2)>;

    constexpr bool cond3 {lv < level_limit && Gtr<typename Res2::Idx, Hex<0>>::value};
    auto&& app3 {apply_if<typename Res2::type, cond3>(f)};
    auto&& res3 {apply_helper<
        Remove_ref_T<decltype(app3)>,
        Apply_if_T<Pred, cond3, typename Res2::Idx>, lv + 1>(
          f, Bool_T<cond3>{})};
    using Res3 = Remove_ref_T<decltype(res3)>;

    constexpr bool cond4 {lv < level_limit && Gtr<typename Res3::Idx, Hex<0>>::value};
    auto&& app4 {apply_if<typename Res3::type, cond4>(f)};
    auto&& res4 {apply_helper<
        Remove_ref_T<decltype(app4)>,
        Apply_if_T<Pred, cond4, typename Res3::Idx>, lv + 1>(
          f, Bool_T<cond4>{})};
    using Res4 = Remove_ref_T<decltype(res4)>;

    constexpr bool cond5 {lv < level_limit && Gtr<typename Res4::Idx, Hex<0>>::value};
    auto&& app5 {apply_if<typename Res4::type, cond5>(f)};
    auto&& res5 {apply_helper<
        Remove_ref_T<decltype(app5)>,
        Apply_if_T<Pred, cond5, typename Res4::Idx>, lv + 1>(
          f, Bool_T<cond5>{})};
    using Res5 = Remove_ref_T<decltype(res5)>;

    constexpr bool cond6 {lv < level_limit && Gtr<typename Res5::Idx, Hex<0>>::value};
    auto&& app6 {apply_if<typename Res5::type, cond6>(f)};
    auto&& res6 {apply_helper<
        Remove_ref_T<decltype(app6)>,
        Apply_if_T<Pred, cond6, typename Res5::Idx>, lv + 1>(
          f, Bool_T<cond6>{})};
    using Res6 = Remove_ref_T<decltype(res6)>;

    constexpr bool cond7 {lv < level_limit && Gtr<typename Res6::Idx, Hex<0>>::value};
    auto&& app7 {apply_if<typename Res6::type, cond7>(f)};
    auto&& res7 {apply_helper<
        Remove_ref_T<decltype(app7)>,
        Apply_if_T<Pred, cond7, typename Res6::Idx>, lv + 1>(
          f, Bool_T<cond7>{})};
    using Res7 = Remove_ref_T<decltype(res7)>;

    constexpr bool cond8 {lv == 0 && Gtr<typename Res7::Idx, Hex<0>>::value};
    // Apply again if not enough
    auto&& app8 {apply_if<typename Res7::type, cond8>(f)};
    auto&& res8 {apply_helper<
        Remove_ref_T<decltype(app8)>,
        Apply_if_T<Pred, cond8, typename Res7::Idx>, lv>(
          f, Bool_T<cond8>{})};
    using Res8 = Remove_ref_T<decltype(res8)>;

    return Res8{};
}

template <class H, class Hn, class F>
  constexpr inline auto apply(F&& f)
{
    auto&& res {apply_helper<H, Hn, 0>(f, True<>{})};
    return typename Remove_ref_T<decltype(res)>::type{};
}


/* Cast a Hex_class to number */
template <class> struct Value;
template <template <bool...> class H>
  struct Value<H<>> {
    static constexpr auto value {0ULL};
};
template <template <bool...> class H, bool b0, bool... bs>
  struct Value<H<b0, bs...>> {
    static constexpr auto value {b0 << sizeof...(bs) | Value<H<bs...>>::value};
};
template <template <bool...> class H, bool b3, bool b2, bool b1, bool b0, bool... bs>
  struct Value<H<b3, b2, b1, b0, bs...>> {
    static constexpr auto value {H<b3, b2, b1, b0>::value << sizeof...(bs) | Value<H<bs...>>::value};
};


#include <iostream>

using namespace std;

int main()
{
    (cout << nounitbuf).sync_with_stdio(false);
    cin.tie(nullptr);

    using Hex_k = Apply_T<Pred, 5, Bor_T<Make_T<Hex, 16, 0>, Hex<1, 0, 0>>>;
    using Hex_n = Suc_T<Suc_T<L_shift_T<L_fit_T<Hex<1>, 12>, 11>>>;

    apply<Hex_k, Hex_n>([](auto&& hex)
    {
        using H = Remove_ref_T<decltype(hex)>;
        cout << Value<H>::value << '\n';
        return Suc_T<H>{};
    });

    return 0;
}
