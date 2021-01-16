#include <stdio.h>

int main(void)
{
    int a[] = {1, 2, 3,};

    int k = 0;
    for (k = 0; k < sizeof a / sizeof *a; ++k) {
        printf("%d\n", a[k]);
    }

    return 0;
}
