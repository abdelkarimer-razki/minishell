/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:06:25 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/19 19:47:07 by bboulhan         ###   ########.fr       */
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


int	parcing(char *line, t_list *node)
{
	t_list	*tmp;
	char	**par;
	int		i;

	i = 0;
	tmp = node;
	par = lexer(line, '|');
	if (!par)
		return 0;
	tmp->str = par[i];
	tmp->table = lexer_space(par[i], ' ');
	if (!(tmp->table) || !(tmp->table[0]))
	{
		ft_free(par);
		return ((int)ft_error(5, tmp->table, NULL));
	}
	while (par[++i])
	{
		add_node(&node);
		tmp = tmp->next;
		tmp->str = par[i];
		tmp->table = lexer_space(par[i], ' ');
		if (!(tmp->table) || (tmp->table[0] == 0))
		{
			ft_free(par);
			return ((int)ft_error(5, tmp->table, NULL));
		}
	}
	free(par);
	return (1);
}

char	**lexer(char *line, char c)
{
	int		i;
	int		j;
	int		n;
	char	**table;

	i = -1;
	j = 0;
	n = 0;
	table = malloc(sizeof(char *) * 1);
	if (!table)
		return (NULL);
	table[0] = NULL;
	while (line[++i])
	{
		if (line[i] == c || line[i + 1] == '\0')
		{
			j++;
			table = ft_realloc(table, j);
			if (line[i] == c)
				table[j - 1] = cut_string(line, n, i);
			else if (line[i + 1] == '\0')
				table[j - 1] = cut_string(line, n, i + 1);
			n = i + 1;
		}
		table[j] = NULL;
	}
	return (table);
}

char	**lexer_space(char *line, char c)
{
	int		i;
	int		j;
	int		n;
	char	**table;

	i = -1;
	j = 0;
	n = 0;
	table = malloc(sizeof(char *) * 1);
	if (!table)
		return (NULL);
	table[0] = 0;
	while (line[++i])
	{
		if (line[i] == 39 || line[i] == '"')
		{	
			i = quoted(line, i);
			if (i == 0)
				return (ft_error(4, table, NULL));
		}
		if ((line[i] == c && line[i - 1] != c) || line[i + 1] == '\0')
		{
			j++;
			table = ft_realloc(table, j);
			if (line[i] == c)
				table[j - 1] = cut_string(line, n, i);
			else if (line[i + 1] == '\0')
				table[j - 1] = cut_string(line, n, i + 1);
			n = i + 1;
			table[j] = NULL;
		}
	}
	return (table);
}























int	put_zero(void *arg, int x, int y)
{
	char	**table;
	char	*str;

	table = NULL;
	str = NULL;
	if (x == 1)
	{
		table = malloc(sizeof(char *) * 1);
		table[0] = ft_calloc(1, 1);
		arg = table;
	}
	else
	{
		str = ft_calloc(1, 1);
		arg = str;
	}
	return (y);
}