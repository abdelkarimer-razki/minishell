/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:06:25 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/05 16:13:02 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (ft_strtrim(line, " "));
}

int	quoted(char	*line, int i)
{
	int	j;

	j = i + 1;
	while (line[j] != line[i] && line[j])
		j++;
	return (j);
}

int	single_quoted(char	*line, int i)
{
	i++;
	while (line[i] != 32 && line[i])
		i++;
	return (i);
}

int	double_quoted(char	*line, int i)
{
	i++;
	while (line[i] != '"' && line[i])
		i++;
	return (i);
}


// adding a new node and make it the last element of the node list
void	add_node(t_list **node)
{
	t_list	*new;

	new = malloc(sizeof(t_list) * 1);
	if (!new)
		exit (0);
	ft_lstadd_back(node, new);
}

// parcing is a function that split the command line to specific words and put them into a node
void	parcing(char *line, t_list *node)
{
	t_list	*tmp;
	char	**par;
	int		i;

	i = 0;
	tmp = node;
	par = lexer(line, '|');
	tmp->cmd = par[i];
	tmp->table = lexer(par[i], ' ');
	while (par[++i])
	{
		add_node(&node);
		tmp = tmp->next;
		tmp->cmd = par[i];
		tmp->table = lexer(par[i], ' ');
	}
	free(par);
}

// spliting (by space or quotes) the command line to words
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
		if (line[i] == 32)
			i = single_quoted(line, i);
		else if (line[i] == '"')
			i = double_quoted(line, i); 
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