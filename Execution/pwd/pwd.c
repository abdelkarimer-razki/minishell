#include "../../minishell.h"

void	pwd(t_env *table)
{
	char	s[1000];

	if (getcwd(s, 1000) == NULL)
		printf("%s\n", getmyenv("PWD", table->env));
	else
		printf("%s\n", getcwd(s, 100));
}
