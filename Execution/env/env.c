#include "../../minishell.h"

void	env(t_env *env)
{
	int	i;

	i = -1;
	while (env->env[++i])
		printf("%s\n", env->env[i]);
}
