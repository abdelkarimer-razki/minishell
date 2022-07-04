/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:55:44 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 12:16:27 by bboulhan         ###   ########.fr       */
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
		return(s);
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
