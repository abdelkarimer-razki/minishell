/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:55:51 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 10:25:11 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(t_env *table, t_list *node)
{
	char	s[1000];

	if (node->args[1] && node->args[1][0] == '-')
	{
		ft_putstr_fd("do3afa2: pwd: option not supported\n", 2);
		g_data.exit_status = 1;
		return ;
	}
	if (getcwd(s, 1000) == NULL)
		printf("%s\n", getmyenv("PWD", table->env));
	else
		printf("%s\n", getcwd(s, 100));
	g_data.exit_status = 0;
}
