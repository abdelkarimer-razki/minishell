#include "../../minishell.h"

void	pwd()
{   
	char s[100];

	printf("%s\n", getcwd(s, 100));
}