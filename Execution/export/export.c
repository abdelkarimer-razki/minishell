/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:55:47 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 20:15:31 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	if (s3[0] == '\0' || s4[0] == '\0')
		return (-1);
	if (s3 != NULL || s4 != NULL)
	{
		while ((s3[i] != '\0' || s4[i] != '\0')
			&& i != n)
		{
			if (s3[i] != s4[i])
				return (s3[i] - s4[i]);
			i++;
		}
	}
	return (0);
}

int	ft_strlen_2(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2);
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, ft_strlen(s1));
	ft_memcpy(s + ft_strlen(s1), s2, ft_strlen(s2));
	s[i] = 0;
	free(s2);
	free(s1);
	return (s);
}

void	sort_strings(char **string)
{
	int		i;
	int		j;
	char	*c;

	i = -1;
	while (string[++i])
	{
		j = i + 1;
		while (string[j])
		{
			if (ft_strncmp(string[i], string[j], 20) > 0)
			{
				c = string[i];
				string[i] = string[j];
				string[j] = c;
			}
			j++;
		}
	}
}

void	export(t_env *env, t_list *table)
{
	if (table->args[1] && table->args[1][0] == '-')
	{
		ft_putstr_fd("do3afa2: export: option not supported\n", 2);
		g_data.exit_status = 2;
		return ;
	}
	if (ft_strlen_2(table->args) == 1)
		show_export(env->export);
	else
		fill_args(env, table);
}
