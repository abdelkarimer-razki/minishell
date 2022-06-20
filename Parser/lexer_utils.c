/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:08:33 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/20 14:27:44 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cut_string(char *str, int i0, int i1)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(i1 - i0 + 1);
	if (!line)
		return (NULL);
	while (str[i0 + i] && i + i0 < i1)
	{
		line[i] = str[i0 + i];
		i++;
	}
	line[i] = 0;
	if (line[0] == 0)
		return (line);
	return (ft_strtrim(line, " "));
}

int	quoted(char	*line, int i)
{
	int	j;

	j = i;
	while (line[++j])
	{
		if (line[j] == line[i])
			return (j);
	}
	return (0);
}

void	add_node(t_list **node)
{
	t_list	*new;

	new = malloc(sizeof(t_list) * 1);
	if (!new)
		exit (0);
	ft_lstadd_back(node, new);
}

int	lexer2(t_list *node, t_list *tmp, char **par)
{
	int	i;

	i = 0;
	while (par[++i])
	{
		add_node(&node);
		tmp = tmp->next;
		tmp->str = par[i];
		tmp->table = lexer_space(par[i]);
		if (!(tmp->table) || (tmp->table[0] == 0))
		{
			ft_free(par);
			ft_error(3, tmp->table, NULL);
			return (0);
		}
	}
	return (1);
}
