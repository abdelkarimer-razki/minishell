/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:56:06 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 10:29:46 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**tabup(char **tab, char *str)
{
	char	**new;
	int		i;
	int		j;
	int		k;
	char	*str_new;

	j = ft_strlen_2(tab);
	i = -1;
	k = 0;
	new = malloc(sizeof(char *) * (j));
	while (++i < j)
	{
		str_new = cut_string(tab[i], 0, find_equal(tab[i]));
		if (ft_strncmp(str_new, str, ft_strlen(str_new)) != 0)
			new[k++] = tab[i];
		free(str_new);
	}
	new[i - 1] = NULL;
	ft_free(tab);
	return (new);
}

void	unset(t_env *env, t_list *table)
{
	int	i;

	i = 0;
	if (table->args[1] && table->args[1][0] == '-')
	{
		ft_putstr_fd("do3afa2: unset: option not supported\n", 2);
		g_data.exit_status = 2;
		return ;
	}
	while (table->args[++i])
	{
		if (check_args(table->args[1]) == -1)
		{
			ft_putstr_fd("do3afa2: unset :invalid argument\n", 2);
			g_data.exit_status = 2;
			return ;
		}
	}
	i = 0;
	while (table->args[++i])
	{
		if (check_table(env->env, table->args[i]) != -1)
			env->env = tabup(env->env, table->args[i]);
		if (check_table(env->export, table->args[i]) != -1)
			env->export = tabup(env->export, table->args[i]);
	}
	g_data.exit_status = 0;
}
