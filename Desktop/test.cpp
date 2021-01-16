#include <iostream>
#include <tuple>

#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    if (argc <= 2)
        return 0;
    auto [buf1, buf2] = std::make_tuple(strdup(argv[1]), strdup(argv[2]));
    std::cout << buf1 << ' ' << buf2 << '\n';
    free(buf2);
    free(buf1);
}
