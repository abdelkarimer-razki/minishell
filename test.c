#include "minishell.h"



int main()
{
	char *s;
	int *j;
	s = ft_error(3, NULL, NULL, NULL);
	j = ft_error(4, NULL, NULL, 1);
	printf("%s\t%d\n", s, j);
}

