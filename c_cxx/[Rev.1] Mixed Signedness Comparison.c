/* Mixed Signedness Comparison
Intuitively comparison between signed and unsigned values.

Written by Iweidieng Iep on 2019-05-24.
Rev.1 by Iweidieng Iep on 2019-05-24:
   Refine punctuation of program description
   Fix using `[u|]int16_t` in `>` test cases where `[u|]int8_t` were intended
*/

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define TEST(val, expect)  assert((val) == (expect))

/* Compare the signs first and then the values */
#define MIXSIGNCMP(lhs, opr, rhs)  \
  (int) ((((lhs) >= 0) != ((rhs) >= 0)) \
    ? ((lhs) >= 0) opr ((rhs) >= 0) \
    : (lhs) opr (rhs))

int main(void)
{
    TEST((uint64_t)-1 < 0, false);
    TEST(-1 < (uint64_t)0, false);
    TEST(MIXSIGNCMP((uint64_t)-1, <, 0), false);
    TEST(MIXSIGNCMP(-1, <, (uint64_t)0), true);

    TEST((uint64_t)-1 <= -1, true);
    TEST(-1 <= (uint64_t)-1, true);
    TEST(MIXSIGNCMP((uint64_t)-1, <=, -1), false);
    TEST(MIXSIGNCMP(-1, <=, (uint64_t)-1), true);

    TEST((uint64_t)-1 == (int16_t)-1, true);
    TEST((int64_t)-1 == (uint16_t)-1, false);
    TEST(MIXSIGNCMP((uint64_t)-1, ==, (int16_t)-1), false);
    TEST(MIXSIGNCMP((int64_t)-1, ==, (uint16_t)-1), false);

    TEST((uint16_t)-1 >= -1, true);
    TEST(-1 >= (uint16_t)-1, false);
    TEST(MIXSIGNCMP((uint16_t)-1, >=, -1), true);
    TEST(MIXSIGNCMP(-1, >=, (uint16_t)-1), false);

    TEST((uint8_t)0 > (int8_t)-1, true);
    TEST((int8_t)0 > (uint8_t)-1, false);
    TEST(MIXSIGNCMP((uint8_t)0, >, (int8_t)-1), true);
    TEST(MIXSIGNCMP((int8_t)0, >, (uint8_t)-1), false);

    printf("Test passed.\n");

    return 0;
}