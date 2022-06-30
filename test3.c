#include "minishell.h"

int main()
{
    int  i =0;
    char *d;
    d = malloc(4);
    while(i < 2000000)
    {
        d[i] = 'a';
        i++;
    }
    d[i] = '\0';
   // free(d);
    printf("%s\n", d);
}