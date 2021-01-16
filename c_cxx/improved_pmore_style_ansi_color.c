/* improved_pmore_style_ansi_color.c
A improved version of PttBBS's macro `ANSI_COLOR()` (ECMA-48 SGR sequence string generator)
   which accepts comma-separated arguments, accepts other macros,
      and produces only a single string.
PttBBS's `ANSI_COLOR()` first appeared in pmore (piaip's more)
   and is now used thoroughly in PttBBS.

This program conforms to ISO C99 and ISO C++11 standards.

This implementation only supports up to 136 (17*8) arguments
   but can be easily modified to support more arguments.
This implementation is optimized for short argument lists.

To see the result of macro expansions: ```sh
time gcc -DDEBUG -E improved_pmore_style_ansi_color.c
```
To execute the tests: ```sh
time gcc -o impmore_ansi_color_test.o improved_pmore_style_ansi_color.c -std=c99 -Wall -Wextra -Wpedantic
./impmore_ansi_color_test.o
```

For optimal reading experience on vim,
   use the vim plugin [Colorizer](https://github.com/chrisbra/Colorizer)
For optimal reading experience on vscode,
   use the vscode extension [Color Highlight](https://github.com/sergiirocks/vscode-ext-color-highlight)

Written by Iweidieng Iep on 2019-09-10
Rev.1 by Iweidieng Iep on 2019-09-12
   - Optimize `PAREN_ALL()` for short argument lists
   - Extract macro `ANSI_COLOR_PAREN()` from `ANSI_COLOR()`
   - Rename `ANSI_COLOR_*` internal macros
   - Add more test cases and helper macros
   - Revise the description of this program
   - Rename this program from 'ANSI_COLOR.c' to 'improved_pmore_style_ansi_color.c'
   - Add `main()` function to make this program executable
*/

#ifndef DEBUG
  #include <assert.h>
  #include <stdio.h>
  #include <string.h>
#endif

/* Basic utility macros */
#define NOOP(...)  __VA_ARGS__
#define JOIN(x, y)  NOOP(x)y
#define STR_PRIME(...)  #__VA_ARGS__
#define STR(x)  STR_PRIME(x)
#define CAT_PRIME(x, ...)  x##__VA_ARGS__
#define CAT(x, y)  CAT_PRIME(x, y)
#define CAT_PRIME2(x, ...)  x##__VA_ARGS__
#define CAT2(x, y)  CAT_PRIME2(x, y)
#define DEFER(f, args)  f args

/* Argument manipulation utility macros */
// Argument extractors
#define SELECT_0_PRIME(_0, ...)  _0
#define SELECT_1_PRIME(_0, _1, ...)  _1
// #define SELECT_2_PRIME(_0, _1, _2, ...)  _2
// ...
#define SELECT_4_PRIME(_0, _1, _2, _3, _4, ...)  _4
#define SELECT_8_PRIME(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...)  _8
#define SELECT_0(...)  SELECT_0_PRIME(__VA_ARGS__,)
#define SELECT_REST_PRIME(_0, ...)  __VA_ARGS__
#define SELECT_REST(...)  SELECT_REST_PRIME(__VA_ARGS__)
#define SELECT_1(...)  SELECT_0(SELECT_REST(__VA_ARGS__))
// #define SELECT_2(...)  SELECT_1(SELECT_REST(__VA_ARGS__))
// ...

// Argument counters
// Expands to `1` for 0 or 1 argument or to `N` for more arguments
#define NARGS_1(...)  \
    SELECT_1(SELECT_1_PRIME(__VA_ARGS__, NOOP(, 1),), N)
// Expands to `1`-`4` for 0-4 arguments or to `N` for more arguments
#define NARGS_4(...)  \
    SELECT_1(SELECT_4_PRIME(__VA_ARGS__, \
      NOOP(, 4), NOOP(, 3), NOOP(, 2), NOOP(, 1),), N)
// Expands to `1`-`4` for 0-4 arguments, to `4N` for 5-7 arguments,
//    to `8` for 8 arguments, or to `N` for more arguments
#define NARGS_4N_8(...)  \
    SELECT_1(SELECT_8_PRIME(__VA_ARGS__, \
      NOOP(, 8), NOOP(, 4N), NOOP(, 4N), NOOP(, 4N), \
      NOOP(, 4), NOOP(, 3), NOOP(, 2), NOOP(, 1),), N)

/* Macro expansion utility macros */
#define ID_DEFER(...)  __VA_ARGS__ NOOP()
#define EVAL(...)  __VA_ARGS__  // Expands 1 time
#define EVAL_7(...)  EVAL(EVAL(EVAL(EVAL(EVAL(EVAL(__VA_ARGS__))))))  // Expands 6+1 times
#define EVAL_8(...)  EVAL_7(__VA_ARGS__)  // Expands 7+1 times
// Deeper `EVAL_*`s can be implemented in this way

/* `PAREN_ALL()`: Enclose each argument with a pair of parentheses
This implementation supports up to (8+7+1) * 8 = 128 arguments;
   replace `EVAL_*`s with deeper `EVAL_*`s to support more arguments.
This implementation is optimized for short argument lists.
Usage Example: PAREN_ALL(x, y, z) => (x)(y)(z)
*/
#define PAREN_ALL(...)  EVAL_8(EVAL_7(PAREN_ALL_IN(__VA_ARGS__)))
#define PAREN_ALL_IN(...)  CAT(PAREN_ALL_IN_, NARGS_4N_8(__VA_ARGS__))(__VA_ARGS__)
#define PAREN_ALL_IN4(...)  CAT(PAREN_ALL_IN_, NARGS_4(__VA_ARGS__))(__VA_ARGS__)
#define PAREN_ALL_IN_1(_0)  (_0)
#define PAREN_ALL_IN_2(_0, _1)  (_0)(_1)
#define PAREN_ALL_IN_3(_0, _1, _2)  (_0)(_1)(_2)
#define PAREN_ALL_IN_4(_0, _1, _2, _3)  (_0)(_1)(_2)(_3)
#define PAREN_ALL_IN_4N(_0, _1, _2, _3, ...)  \
    PAREN_ALL_IN_4(_0, _1, _2, _3)PAREN_ALL_IN4(__VA_ARGS__)
#define PAREN_ALL_IN_8(_0, _1, _2, _3, _4, _5, _6, _7)  \
    PAREN_ALL_IN_4(_0, _1, _2, _3)PAREN_ALL_IN_4(_4, _5, _6, _7)
#define PAREN_ALL_IN_N(_0, _1, _2, _3, _4, _5, _6, _7, ...)  \
    PAREN_ALL_IN_8(_0, _1, _2, _3, _4, _5, _6, _7)ID_DEFER(PAREN_ALL_IN_ID)()(__VA_ARGS__)
#define PAREN_ALL_IN_ID()  PAREN_ALL_IN

#define ANSI_CSI  \x1b[

/* `ANSI_COLOR()`: ECMA-48 Select Graphic Rendition (SGR) sequence string generator
Usage Example: ANSI_COLOR(x, y, z) => "\x1b[x;y;zm"
*/
#define ANSI_COLOR_ITEM1(x)  JOIN(;x, ANSI_COLOR_ITEM2)
#define ANSI_COLOR_ITEM2(x)  JOIN(;x, ANSI_COLOR_ITEM1)
#define ANSI_COLOR_ITEM1_TAIL
#define ANSI_COLOR_ITEM2_TAIL
#define ANSI_COLOR_HEAD_ITEM(x)  JOIN(x, ANSI_COLOR_ITEM1)
// Usage Example: ANSI_COLOR_PAREN((x)(y)(z)) => "\x1b[x;y;zm"
#define ANSI_COLOR_PAREN(parens)  \
    STR(JOIN(ANSI_CSI, DEFER(CAT, (ANSI_COLOR_HEAD_ITEM parens, _TAIL))m))
#define ANSI_COLOR(...)  ANSI_COLOR_PAREN(PAREN_ALL(__VA_ARGS__))

#ifdef DEBUG
  #define ASSERT_STR_EQUAL(x, y)  #x => x / y
#else
  #define ASSERT_STR_EQUAL(x, y)  assert(!strcmp((x), (y)))
#endif

int main(void)
{
    /* Test - Usages of the Original `ANSI_COLOR()` */
    ASSERT_STR_EQUAL(ANSI_COLOR(),        "\x1b[m");  // C99
    ASSERT_STR_EQUAL(ANSI_COLOR(0),       "\x1b[0m");
    ASSERT_STR_EQUAL(ANSI_COLOR(;),       "\x1b[;m");
    ASSERT_STR_EQUAL(ANSI_COLOR(;33),     "\x1b[;33m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;33;44), "\x1b[1;33;44m");
    ASSERT_STR_EQUAL(ANSI_COLOR( 38;2;44;181;233 ), "\x1b[38;2;44;181;233m");

    /* Test - Comma-Separated Arguments */
    ASSERT_STR_EQUAL(ANSI_COLOR(,),         "\x1b[;m");
    ASSERT_STR_EQUAL(ANSI_COLOR(, 33),      "\x1b[;33m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1, 33),     "\x1b[1;33m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1, 33, 44), "\x1b[1;33;44m");
    ASSERT_STR_EQUAL(ANSI_COLOR( 38 , 2 , 44 , 181 , 233 ), "\x1b[38;2;44;181;233m");

    /* Test - Macro Arguments */
#define COLOR(type, x)  CAT(CAT_PRIME(COLORTYPE_, type), CAT2(COLOR_, x))
#define COLORTYPE_FG  3
#define COLORTYPE_fg  3
#define COLORTYPE_FG_BRIGHT  1;3
#define COLORTYPE_fg_bright  1;3
#define COLORTYPE_BG  4
#define COLORTYPE_bg  4
#define COLORTYPE_BG_BRIGHT  10  // Non-standard (xterm, aixterm)
#define COLORTYPE_bg_bright  10

#define COLOR_ISO(type, x)  CAT(CAT_PRIME(COLORTYPE_, type), CAT2(COLOR_ISO_, x))
/* `ISO_SELECT_COLOR()`:
    ISO 8613-6 Standard `Select Character Foreground/Background Colour` argument sequence generator
Usage Example: ISO_SELECT_COLOR(x, y, z) => x:y:z
*/
#define ISO_SELECT_COLOR_ITEM1(x)  JOIN(:x, ISO_SELECT_COLOR_ITEM2)
#define ISO_SELECT_COLOR_ITEM2(x)  JOIN(:x, ISO_SELECT_COLOR_ITEM1)
#define ISO_SELECT_COLOR_ITEM1_TAIL
#define ISO_SELECT_COLOR_ITEM2_TAIL
#define ISO_SELECT_COLOR_HEAD_ITEM(x)  JOIN(x, ISO_SELECT_COLOR_ITEM1)
// Usage Example: ISO_SELECT_COLOR_PAREN((x)(y)(z)) => x:y:z
#define ISO_SELECT_COLOR_PAREN(parens)  \
    DEFER(CAT, (ISO_SELECT_COLOR_HEAD_ITEM parens, _TAIL))
#define ISO_SELECT_COLOR(...)  ISO_SELECT_COLOR_PAREN(PAREN_ALL(__VA_ARGS__))

// ANSI Standard Color (3-Bit Indexed Color)
#define COLOR_0  0
#define COLOR_1  1
#define COLOR_2  2
#define COLOR_3  3
#define COLOR_4  4
#define COLOR_5  5
#define COLOR_6  6
#define COLOR_7  7
#define COLOR_9  9
#define COLOR_MAGENTA  5
#define COLOR_magenta  5
#define COLOR_CYAN  6
#define COLOR_cyan  6
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(fg, COLOR_CYAN)),  "\x1b[36m");
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(fg_bright, cyan)), "\x1b[1;36m");
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(bg, COLOR_5)),     "\x1b[45m");
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(bg_bright, 5)),    "\x1b[105m");

// "256 Color" (Indexed Color)
#define COLOR_ISO_term256(...)  ISO_SELECT_COLOR(8, 5, __VA_ARGS__)  // ISO 8613-6 standard, less supported
#define COLOR_TERM256_PRIME(n)  8, 5, n
#define COLOR_term256(...)  COLOR_TERM256_PRIME(__VA_ARGS__)  // Non-standard (xterm), widely supported
#define term256(n)  term256(n)
#define COLOR_256_CYAN  term256(81)
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(fg, COLOR_256_CYAN)), "\x1b[38;5;81m");
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(fg, term256(164))),   "\x1b[38;5;164m");
    ASSERT_STR_EQUAL(
        ANSI_COLOR(COLOR(fg, COLOR_256_CYAN), COLOR(bg, term256(164))),
        "\x1b[38;5;81;48;5;164m");
    ASSERT_STR_EQUAL(
        ANSI_COLOR(COLOR_ISO(fg, COLOR_256_CYAN), COLOR_ISO(bg, term256(164))),
        "\x1b[38:5:81;48:5:164m");

// "True Color" (RGB Direct Color)
#define COLOR_ISO_rgb(...)  ISO_SELECT_COLOR(8, 2, 0, __VA_ARGS__)  // ISO 8613-6 standard, less supported
#define COLOR_RGB_PRIME(r, g, b)  8, 2, r, g, b
#define COLOR_rgb(...)  COLOR_RGB_PRIME(__VA_ARGS__)  // Non-standard (xterm), widely supported
#define rgb(r, g, b)  rgb(r, g, b)
#define COLOR_RGB_CYAN  rgb(44, 181, 233)
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(fg, COLOR_RGB_CYAN)),   "\x1b[38;2;44;181;233m");
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(fg, rgb(180, 0, 158))), "\x1b[38;2;180;0;158m");
    ASSERT_STR_EQUAL(
        ANSI_COLOR(COLOR(fg, COLOR_RGB_CYAN), COLOR(bg, rgb(180, 0, 158))),
        "\x1b[38;2;44;181;233;48;2;180;0;158m");
    ASSERT_STR_EQUAL(
        ANSI_COLOR(COLOR_ISO(fg, COLOR_RGB_CYAN), COLOR_ISO(bg, rgb(180, 0, 158))),
        "\x1b[38:2:0:44:181:233;48:2:0:180:0:158m");

    ASSERT_STR_EQUAL(
        ANSI_COLOR(COLOR(fg, COLOR_RGB_CYAN), COLOR(bg, COLOR_256_CYAN)),
        "\x1b[38;2;44;181;233;48;5;81m");
    ASSERT_STR_EQUAL(
        ANSI_COLOR(COLOR_ISO(fg, COLOR_RGB_CYAN), COLOR_ISO(bg, COLOR_256_CYAN)),
        "\x1b[38:2:0:44:181:233;48:5:81m");

    /* Test - Mixed Usages */
    ASSERT_STR_EQUAL(ANSI_COLOR( 38;2 , 44;181;233 ),         "\x1b[38;2;44;181;233m");
    ASSERT_STR_EQUAL(ANSI_COLOR(;COLOR(fg, COLOR_RGB_CYAN)),  "\x1b[;38;2;44;181;233m");
    ASSERT_STR_EQUAL(ANSI_COLOR(2;COLOR(bg, COLOR_256_CYAN)), "\x1b[2;48;5;81m");
    ASSERT_STR_EQUAL(ANSI_COLOR(COLOR(fg, cyan);COLOR(bg, magenta)), "\x1b[36;45m");

    /* Test - Some Actual Usages of the Original `ANSI_COLOR()`, Taken from PttBBS */
    // In the C / C++ code
    ASSERT_STR_EQUAL(ANSI_COLOR(0),         "\x1b[0m");
    ASSERT_STR_EQUAL(ANSI_COLOR(0;1),       "\x1b[0;1m");
    ASSERT_STR_EQUAL(ANSI_COLOR(0;1;30),    "\x1b[0;1;30m");
    ASSERT_STR_EQUAL(ANSI_COLOR(0;1;30;47), "\x1b[0;1;30;47m");
    ASSERT_STR_EQUAL(ANSI_COLOR(0;1;3%d),   "\x1b[0;1;3%dm");
    ASSERT_STR_EQUAL(ANSI_COLOR(0;30;47),   "\x1b[0;30;47m");
    ASSERT_STR_EQUAL(ANSI_COLOR(0;47),      "\x1b[0;47m");
    ASSERT_STR_EQUAL(ANSI_COLOR(0;7),       "\x1b[0;7m");
    ASSERT_STR_EQUAL(ANSI_COLOR(0;7;36),    "\x1b[0;7;36m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1),         "\x1b[1m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;30),      "\x1b[1;30m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;37;46),   "\x1b[1;37;46m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;3%c),     "\x1b[1;3%cm");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;3%d),     "\x1b[1;3%dm");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;40;31),   "\x1b[1;40;31m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;40;3%d),  "\x1b[1;40;3%dm");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;46),      "\x1b[1;46m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1;%d;44),   "\x1b[1;%d;44m");
    ASSERT_STR_EQUAL(ANSI_COLOR(22;37),     "\x1b[22;37m");
    ASSERT_STR_EQUAL(ANSI_COLOR(31),        "\x1b[31m");
    ASSERT_STR_EQUAL(ANSI_COLOR(;31;47),    "\x1b[;31;47m");
    ASSERT_STR_EQUAL(ANSI_COLOR(33;45),     "\x1b[33;45m");
    ASSERT_STR_EQUAL(ANSI_COLOR(;36),       "\x1b[;36m");
    ASSERT_STR_EQUAL(ANSI_COLOR(37;43),     "\x1b[37;43m");
    ASSERT_STR_EQUAL(ANSI_COLOR(3%c),       "\x1b[3%cm");
    ASSERT_STR_EQUAL(ANSI_COLOR(40),        "\x1b[40m");
    ASSERT_STR_EQUAL(ANSI_COLOR(41;5),      "\x1b[41;5m");
    ASSERT_STR_EQUAL(ANSI_COLOR(43;0;1;35), "\x1b[43;0;1;35m");
    ASSERT_STR_EQUAL(ANSI_COLOR(47;34),     "\x1b[47;34m");
    ASSERT_STR_EQUAL(ANSI_COLOR(5;35),      "\x1b[5;35m");
    ASSERT_STR_EQUAL(ANSI_COLOR(7),         "\x1b[7m");
    ASSERT_STR_EQUAL(ANSI_COLOR(%d),        "\x1b[%dm");
    ASSERT_STR_EQUAL(ANSI_COLOR(%s1;%d),    "\x1b[%s1;%dm");

    // In the Python code
    ASSERT_STR_EQUAL(ANSI_COLOR(),     "\x1b[m");
    ASSERT_STR_EQUAL(ANSI_COLOR(0,32), "\x1b[0;32m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1,31), "\x1b[1;31m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1,32), "\x1b[1;32m");
    ASSERT_STR_EQUAL(ANSI_COLOR(1,37), "\x1b[1;37m");
    ASSERT_STR_EQUAL(ANSI_COLOR(33),   "\x1b[33m");

    fputs(ANSI_COLOR(1, COLOR(fg, cyan))
          "All tests were passed successfully!" ANSI_COLOR() "\n",
        stderr);
}
