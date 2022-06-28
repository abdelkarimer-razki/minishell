#include "../../minishell.h"

void	cd(t_env *env, t_list *table)
{
	char	s[100];

	setmyenv("OLDPWD", getcwd(s, 100), env);
	if (!table->args[1] || !ft_strncmp(table->args[1], "~", ft_strlen(table->args[1])))
	{
		if (chdir(getmyenv("HOME", env->env)) == -1)
			printf("do3afa2: cd: HOME not set\n");
	}
	else if (!ft_strncmp(table->args[1], "-", ft_strlen(table->args[1])))
	{
		if (chdir(getmyenv("OLDPWD", env->env)) == -1)
			printf("do3afa2: cd: OLDPWD not set\n");
		else
			printf("%s\n", getmyenv("OLDPWD", env->env));
	}
	else if (chdir(table->args[1]) == -1)
		printf(ANSI_COLOR_RED "cd: no such file or directory: %s\n" ANSI_COLOR_RESET, table->args[0]);
	setmyenv("PWD", getcwd(s, 100), env);
}
