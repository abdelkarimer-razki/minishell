/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:06:25 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/04 21:51:56 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(char *line, t_list *node)
{
	t_list	*tmp;
	char	**par;

	tmp = node;
	par = lexer_pipe(line);
	if (!par || par[0] == 0)
		return (ft_error_2(0, NULL, NULL));
	tmp->str = ft_strdup(par[0]);
	tmp->table = lexer_space(par[0]);
	if (!(tmp->table))
		return (ft_error_2(0, par, NULL));
	if (tmp->table[0] == 0)
		return (ft_error_2(3, par, NULL));
	if (!lexer2(node, tmp, par))
		return (0);
	ft_free(par);
	return (1);
}

void	lexer_pipe_2(char *line, char ***t, int *i, int *n)
{
	int		j;
	char	**table;

	j = 0;
	table = *t;
	while (table[j])
		j++;
	if (line[*i] == '|' && line[*i + 1] == 0)
		table = ft_error(3, table, NULL);
	else if ((line[*i] == '|' && line[*i + 1] != '|') || line[*i + 1] == '\0')
	{
		table = ft_realloc(table, ++j);
		if (line[*i] == '|')
			table[j - 1] = cut_string(line, *n, *i);
		else if (line[*i + 1] == '\0')
			table[j - 1] = cut_string(line, *n, *i + 1);
		*n = *i + 1;
		table[j] = NULL;
	}
	*t = table;
}

char	**lexer_pipe(char *line)
{
	int		i;
	int		n;
	char	**table;

	i = 0;
	n = 0;
	table = malloc(sizeof(char *) * 1);
	table[0] = NULL;
	while (line[i] == ' ')
	{
		if (line[++i] == '|')
			return (ft_error(3, table, NULL));
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] == 39 || line[i] == '"')
		{	
			i = quoted(line, i);
			if (i == 0)
				return (ft_error(4, table, NULL));
		}
		lexer_pipe_2(line, &table, &i, &n);
	}
	return (table);
}

void	lexer_space_2(char *line, char ***t, int *i, int *n)
{
	int		j;
	char	**table;

	j = 0;
	table = *t;
	while (table[j])
		j++;
	if ((line[*i] == ' ' && line[*i - 1] != ' ') || line[*i + 1] == '\0')
	{
		j++;
		table = ft_realloc(table, j);
		if (line[*i] == ' ')
			table[j - 1] = cut_string(line, *n, *i);
		else if (line[*i + 1] == '\0')
			table[j - 1] = cut_string(line, *n, *i + 1);
		*n = *i + 1;
		table[j] = NULL;
	}
	*t = table;
}

char	**lexer_space(char *line)
{
	int		i;
	int		n;
	char	**table;

	i = -1;
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
		lexer_space_2(line, &table, &i, &n);
	}
	if (line[i] == 0 && table[0] == 0)
		return (ft_error(0, table, NULL));
	return (table);
}
