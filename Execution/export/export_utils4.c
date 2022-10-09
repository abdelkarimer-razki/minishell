/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:15:13 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 20:47:47 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	oldpwd_len(char **source)
{
	if (getenv("OLDPWD"))
		return (ft_strlen_2(source) + 1);
	else
		return (ft_strlen_2(source) + 1 + 1);
}

char	**ft_strdup_2(char **source)
{
	char	**s;
	int		i;
	int		y;

	y = oldpwd_len(source);
	s = malloc((y) * sizeof(char *));
	if (!s)
		return (NULL);
	i = 0;
	while (source[i])
	{
		s[i] = ft_strdup(source[i]);
		i++;
	}
	if (y == ft_strlen_2(source) + 1 + 1)
	{
		s[i] = ft_strdup("OLDPWD");
		s[i + 1] = 0;
	}
	else
		s[i] = 0;
	sort_strings(s);
	return (s);
}

void	fill_export(int i, int j, t_env *env, t_list *table)
{
	if (table->args[i][j] == '=')
		just_equal(table->args[i], env);
	else if (table->args[i][j] == '+' && table->args[i][j + 1] == '=')
		plus_equal(table->args[i], env);
}

void	arg_error_export(void)
{
	ft_putstr_fd("do3afa2: export: not a valid identifier\n", 2);
	g_data.exit_status = 1;
}

void	fill_args(t_env *env, t_list *table)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	while (table->args[++i])
	{
		set_values(&j, &n);
		if (check_args(table->args[i]) == -1)
		{
			arg_error_export();
			continue ;
		}
		while (table->args[i][++j] && ft_strncmp(table->args[i], "_",
				find_equal(table->args[i])) != 0)
		{
			if (n == 0 && tester_args(table, i, j) == 1)
			{
				fill_export(i, j, env, table);
				n++;
			}
		}
		no_value_fill(table, n, i, env);
	}
	sort_strings(env->export);
}
