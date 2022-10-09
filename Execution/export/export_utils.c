/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:55:44 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 20:08:52 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*getmyenv(char *str, char **env)
{
	int		i;
	char	*s;

	s = ft_calloc(1, 1);
	if (str[0] == '?')
	{
		free(s);
		s = ft_itoa(g_data.exit_status);
		return (s);
	}
	else if (ft_isalnum(str[0]))
		return (s);
	i = check_table(env, str);
	if (i != -1)
	{
		free(s);
		return (cut_string(env[i], find_equal(env[i]) + 1, ft_strlen(env[i])));
	}
	return (s);
}

void	setmyenv(char *str, char *value, t_env *env)
{
	char	*tmp;
	char	*value1;
	char	*equal;

	if (str != NULL && value != NULL)
	{
		tmp = ft_strdup(str);
		value1 = ft_strdup(value);
		equal = ft_strdup("=");
		just_equal(ft_strjoin1(tmp, ft_strjoin1(equal, value1)), env);
	}
}

int	find_equal(char *table)
{
	int	i;

	i = 0;
	while (table[i] && table[i] != '=' && table[i] != '+')
		i++;
	return (i);
}

int	check_args(char *arg)
{
	int	j;

	j = -1;
	while (arg[++j]
		&& ((arg[j] != '=' && (arg[j] != '+' || arg[j + 1] != '=')) || j == 0))
	{
		if (j == 0 && ft_isalpha1(arg[j]) == 0)
			return (-1);
		else if ((j != 0 && ft_isalpha2(arg[j]) == 0))
			return (-1);
	}
	if (ft_strlen(arg) == 0)
		return (-1);
	return (1);
}

int	check_table(char **table, char *arg)
{
	int		i;
	char	*str;
	char	*str1;

	i = -1;
	while (table[++i])
	{
		str = ft_substr(table[i], 0, find_equal(table[i]));
		str1 = ft_substr(arg, 0, find_equal(arg));
		if (ft_strncmp(str, str1, find_equal(table[i])) == 0
			&& find_equal(table[i]) == find_equal(arg))
			return (free(str), free(str1), i);
		free(str);
		free(str1);
	}
	return (-1);
}
