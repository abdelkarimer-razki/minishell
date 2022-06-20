#include "../../minishell.h"

void	cd(t_env *env, t_list *table)
{
	char	s[100];
	char	*oldpwd;
	char	*pwd;
	int		i;

	oldpwd = ft_strdup("OLDPWD=");
	pwd = ft_strdup("PWD=");
	i = check_table(env->env, "OLDPWD");
	if (i != -1)
	{
		free(env->env[i]);
		env->env[i] = ft_strjoin1(oldpwd, ft_strdup(getcwd(s, 100)));
	}
	else
	{
		env->env = ft_realloc(env->env, ft_strlen_2(env->env) + 1);
		env->env[ft_strlen_2(env->env)] = ft_strjoin1(oldpwd,
				ft_strdup(getcwd(s, 100)));
	}
	if (chdir(table->args[1]) == -1)
		printf("cd: no such file or directory: %s\n", table->args[0]);
	i = check_table(env->env, "PWD");
	free(env->env[i]);
	env->env[i] = ft_strjoin1(pwd, ft_strdup(getcwd(s, 100)));
}
