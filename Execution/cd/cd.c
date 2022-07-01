#include "../../minishell.h"

void	cd(t_env *env, t_list *table)
{
	char	s[100];

	setmyenv("OLDPWD", getcwd(s, 100), env);
	if (!table->args[1] || !ft_strncmp(table->args[1], "~", 1))
	{
		if (chdir(getmyenv("HOME", env->env)) == -1)
			printf("do3afa2: cd: HOME not set\n");
	}
	else if (!ft_strncmp(table->args[1], "-", 1))
	{
		if (chdir(getmyenv("OLDPWD", env->env)) == -1)
			printf("do3afa2: cd: OLDPWD not set\n");
		else
			printf("%s\n", getmyenv("OLDPWD", env->env));
	}
	else if (access(table->args[1], R_OK) == -1 || chdir(table->args[1]) == -1)
		perror("do3afa2: cd: ");
	if (getcwd(s, 100) != NULL)
		setmyenv("PWD", getcwd(s, 100), env);
}
