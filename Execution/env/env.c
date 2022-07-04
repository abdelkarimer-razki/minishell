/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:54:57 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 10:27:52 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	no_option(void)
{
	ft_putstr_fd("do3afa2: env: option not supported\n", 2);
	g_data.exit_status = 1;
}

void	many_args(void)
{
	ft_putstr_fd("do3afa2: env: too many argumants\n", 2);
	g_data.exit_status = 127;
}

void	env(t_env *env, t_list *table)
{
	int	i;

	if (table->args[1] && table->args[1][0] == '-')
	{
		no_option();
		return ;
	}
	if (ft_strlen_2(table->args) != 1)
	{
		many_args();
		return ;
	}
	if (!(*env->env))
	{
		env->env = ft_realloc(env->env, 4);
		env->env[0] = ft_strjoin1(ft_strdup("PWD="),
				ft_strdup(getcwd(NULL, 100)));
		env->env[1] = ft_strdup("SHLVL=1");
		env->env[2] = ft_strdup("_=./minishell");
		env->env[3] = NULL;
	}
	i = -1;
	while (env->env[++i])
		printf("%s\n", env->env[i]);
	g_data.exit_status = 0;
}
