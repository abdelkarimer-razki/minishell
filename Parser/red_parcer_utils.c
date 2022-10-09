/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parcer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:45:59 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/03 05:01:16 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_red(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_red(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == '"')
			i = quoted(str, i);
		if (is_red(str[i]))
			return (1);
	}
	return (0);
}

char	*red_with_quote(char *str, int *i)
{
	char	*s;
	int		k;

	k = 0;
	s = ft_calloc(1, 1);
	if (str[*i] == 39 || str[*i] == '"')
	{	
		k = *i;
		*i = quoted(str, *i);
		while (str[k] && k <= *i)
			s = add_char(s, str[k++]);
		(*i)++;
	}
	else
	{
		while (str[*i] && !is_red(str[*i]) && (str[*i] != '"' && str[*i] != 39))
			s = add_char(s, str[(*i)++]);
	}
	return (s);
}

char	**split_with_red(char *str)
{
	char	**table;
	int		i;
	int		j;

	j = 0;
	i = 0;
	table = malloc(sizeof(char *) * 1);
	table[0] = NULL;
	while (str[i])
	{
		table = ft_realloc(table, ++j);
		if (str[i] && !is_red(str[i]))
			table[j - 1] = red_with_quote(str, &i);
		else
		{
			table[j - 1] = ft_calloc(1, 1);
			while (str[i] && is_red(str[i]))
				table[j - 1] = add_char(table[j - 1], str[i++]);
			if (ft_strlen(table[j - 1]) > 2)
				return (ft_error(3, table, NULL));
		}
	}
	table[j] = NULL;
	return (table);
}
