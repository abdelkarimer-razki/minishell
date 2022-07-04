/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:54:42 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 10:24:47 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	show_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = getmyenv("OLDPWD", env->env);
	printf("%s\n", oldpwd);
	free(oldpwd);
}

void	error_oldpwd(void)
{
	ft_putstr_fd("do3afa2: cd: OLDPWD not set\n", 2);
	g_data.exit_status = 1;
}

void	error_pwd(void)
{
	ft_putstr_fd("do3afa2: cd: HOME not set\n", 2);
	g_data.exit_status = 1;
}

void	cd(t_env *env, t_list *table)
{
	char	s[100];

	if (check_table(env->export, "OLDPWD") != -1)
		setmyenv("OLDPWD", getcwd(s, 100), env);
	if (!table->args[1] || !ft_strncmp(table->args[1], "~", 1))
	{
		if (chdir(getmyenv("HOME", env->env)) == -1)
			error_pwd();
	}
	else if (!ft_strncmp(table->args[1], "-", 1))
	{
		if (chdir(getmyenv("OLDPWD", env->env)) == -1)
			error_oldpwd();
		else
			show_oldpwd(env);
	}
	else if (access(table->args[1], R_OK) == -1 || chdir(table->args[1]) == -1)
	{
		perror("do3afa2: cd: ");
		g_data.exit_status = 1;
	}
	else
		g_data.exit_status = 0;
	if (getcwd(s, 100) != NULL)
		setmyenv("PWD", getcwd(s, 100), env);
}
