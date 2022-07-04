/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:56:06 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 19:03:35 by bboulhan         ###   ########.fr       */
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
			new[k++] = ft_strdup(tab[i]);
		free(str_new);
	}
	ft_free(tab);
	new[i - 1] = NULL;
	return (new);
}

void unset_exit_Status(void)
{
	if (g_data.exit_status == -212121)
		g_data.exit_status = 1;
	else
		g_data.exit_status = 0;
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
		if (check_args(table->args[i]) == -1)
		{
			ft_putstr_fd("do3afa2: unset :invalid argument\n", 2);
			g_data.exit_status = -212121;
			continue ;
		}
		if (check_table(env->env, table->args[i]) != -1)
			env->env = tabup(env->env, table->args[i]);
		if (check_table(env->export, table->args[i]) != -1)
			env->export = tabup(env->export, table->args[i]);
	}
	unset_exit_Status();
}
