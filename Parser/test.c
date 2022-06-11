#include "../minishell.h"
int main()
{
    int i = 2;
    char *c = "ibra";
    if (c[i++] == 'r')
        printf("hey\t%c\n", c[i]);
}