#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{   
    char s[100];

    printf("%s\n", getcwd(s, 100));
}