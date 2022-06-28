#include "../../minishell.h"

void	env(t_env *env)
{
	int	i;

	if (!(*env->env))
	{
		env->env = ft_realloc(env->env, 4);
		env->env[0] = ft_strjoin1(ft_strdup("PWD="), ft_strdup(getcwd(NULL, 100)));
		env->env[1] = ft_strdup("SHLVL=1");
		env->env[2] = ft_strdup("_=./minishell");
		env->env[3] = NULL;
	}
	i = -1;
	while (env->env[++i])
		printf("%s\n", env->env[i]);
}
