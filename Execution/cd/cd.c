#include<stdio.h>
#include <unistd.h>

int main(int arc, char **argv)
{   
    if (arc == 2)
        chdir(argv[1]);
    return 0;
}