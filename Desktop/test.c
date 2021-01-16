#include <unistd.h>

int main(void)
{
    execl("/usr/bin/env", "env", "make", "-h", NULL);
    return 255;
}
