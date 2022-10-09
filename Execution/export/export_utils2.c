/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:09:43 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 20:22:13 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	just_equal(char *arg, t_env *env)
{
	int	i;
	int	j;

	i = check_table(env->env, arg);
	j = check_table(env->export, arg);
	if (i != -1)
	{
		free(env->env[i]);
		env->env[i] = ft_strdup(arg);
	}
	else
	{
		env->env = ft_realloc(env->env, ft_strlen_2(env->env) + 1);
		env->env[ft_strlen_2(env->env) - 1] = ft_strdup(arg);
	}
	if (j != -1)
	{
		free(env->export[j]);
		env->export[j] = ft_strdup(arg);
	}
	else
	{
		env->export = ft_realloc(env->export, ft_strlen_2(env->export) + 1);
		env->export[ft_strlen_2(env->export) - 1] = ft_strdup(arg);
	}
}

char	*remove_plus(char *source)
{
	char	*s;
	int		i;
	int		j;

	s = malloc((ft_strlen(source)) * sizeof(char));
	if (!s)
		return (NULL);
	i = -1;
	j = -1;
	while (source[++i])
	{
		if (source[i] == '+')
			continue ;
		j++;
		s[j] = source[i];
	}
	s[j + 1] = 0;
	return (s);
}

void	plus_equal(char *arg, t_env *env)
{
	int		i;
	int		j;

	i = check_table(env->env, arg);
	j = check_table(env->export, arg);
	if (i != -1)
		env->env[i] = ft_strjoin1(env->env[i], ft_substr(arg, find_equal(arg)
					+ 2, ft_strlen(arg) - 1));
	else
	{
		env->env = ft_realloc(env->env, ft_strlen_2(env->env) + 1);
		env->env[ft_strlen_2(env->env) - 1] = remove_plus(arg);
	}
	if (j != -1)
		env->export[j] = ft_strjoin1(env->export[j],
				ft_substr(arg,
					find_equal(arg) + 2, ft_strlen(arg) - 1));
	else
	{
		env->export = ft_realloc(env->export, ft_strlen_2(env->export) + 1);
		env->export[ft_strlen_2(env->export) - 1] = remove_plus(arg);
	}
}

void	no_value(char *arg, t_env *env)
{
	int		i;

	i = check_table(env->export, arg);
	if (i == -1)
	{
		env->export = ft_realloc(env->export, ft_strlen_2(env->export) + 1);
		env->export[ft_strlen_2(env->export) - 1] = ft_strdup(arg);
	}
}
