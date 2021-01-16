#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned long long int max_uint = -1;
    long long int max_int = (unsigned long long int)(~0)>>1;
    long long int min_int = ((unsigned long long int)(~0)>>1) + 1;
    printf("max_uint %llu\nmax_int %lld\nmin_int %lld\n", max_uint, max_int, min_int);
    return 0;
}
