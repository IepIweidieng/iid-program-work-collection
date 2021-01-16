#include <stdio.h>
#include <stdlib.h>

static inline int finder(unsigned int seed) {
    srand(seed);
    if (rand() % 7 != 5) { return 0; }
    if (rand() % 7 != 6) { return 0; }
    if (rand() % 7 != 2) { return 0; }
    if (rand() % 7 != 0) { return 0; }
    if (rand() % 7 != 4) { return 0; }
    if (rand() % 7 != 3) { return 0; }
    if (rand() % 7 != 1) { return 0; }
    if (rand() % 7 != 2) { return 0; }
    if (rand() % 7 != 0) { return 0; }
    return 1;
}

int main(void)
{
    unsigned int k;
    for (k = 0; k != (unsigned int) ~0; ++k) {
        if (!(k % 10000)) { printf("\r%u", k); }
        if (finder(k)) { printf("\r%u: Matched.\n", k); }
    }
    printf("\r%u", ~0);
    if (finder((unsigned int) ~0)) { printf("\r%u: Matched.\n", ~0); }
    return 0;
}
