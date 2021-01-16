#include <stdio.h>
#include <string.h>

int main(void)
{
#define ORIG "Ｔｈｉｓ　ｉｓ　ａ　ｔｅｓｔ．"
    const int o[2][2] = {{0, 15}, {15, 0}};
    printf("original: %s\n", ORIG);
    for (int k = 0; k < (&o)[1] - o; ++k)
    {
        char mov[2 * sizeof(ORIG)] = ORIG;
        char cpy[2 * sizeof(ORIG)] = ORIG;
        memmove(mov + o[k][0], mov + o[k][1], sizeof(ORIG));
        memcpy(cpy + o[k][0], cpy + o[k][1], sizeof(ORIG));
        printf("memmove: %s\n", mov);
        printf("memcpy: %s\n", cpy);
    }
#undef ORIG

    return 0;
}
