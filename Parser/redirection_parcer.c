/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parcer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:20:47 by brahim            #+#    #+#             */
/*   Updated: 2022/06/24 09:47:23 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
/*
int	check_typeOf_red(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
			return (2);
		else if (str[i] == '>')
			return (1);
		else if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
			return (4);
		else if (str[i] == '<')
			return (3);		
	}
	return (0);
}

int	check_dif_red(char *str)
{
	int	i;
	char	c;
	
	i = 0;
	c = str[i];
	while (str[++i])
	{
		if (str[i] != c)
			return (1);
	}
	return (0);
}

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


char    **split_with_red(char *str)
{
	char	*table;
    int 	i;
	int		j;

	j = 0;
    i = 0;
	table = malloc(sizeof(char ) * 1);
    table[0] = NULL;
	while (str[++i])
	{
		table = ft_realloc(table, ++j);
		while (!is_red(str[i]))
			table[j - 1] = add_char(table[0], str[i++]);
		table = ft_realloc(table , ++j);
		while (is_red(str[i]))
			table[j - 1] = add_char(table[j - 1], str[i++]);
		i--;
	}
	table[j] = NULL;
	return (table);
}

char	**split_args(t_list *node)
{
	char	**table;
	char	**s;
	int		i;
	int		j;
	int		k;

	j = 1;
	i = -1;
	k = -1;
	s = NULL;
	table = malloc(sizeof(char *) * 2);
	table[0] = ft_strdup(tmp->cmd);
	table[1] = NULL;
	while (node->table[++i])
	{
		if (check_red(node->table[i]))
		{
			s = split_with_red(node->table[i]);
			while (s[++k])
			{
				table = ft_realloc(table, ++j);
				table[j - 1] = ft_strdup(s[k]);
			}
			k = -1;
			free(s);
		}
		else
		{
			table = ft_realloc(table, ++j);
			table[j - 1] = put_arg(node->table[i]);
		}
	}
	table[j] = NULL;
	return (table);
}


int	red_parcer(t_list *node)
{
	t_red	*tmp;
	char	**table;
	int		i;
	int		j;
	int		y;

	i = -1;
	j = 1;
	y = 0;
	node->red = malloc(sizeof(t_red ) * 1);
	if (!node->red)
		return (0);
	tmp = node->red;
	tmp->args = malloc(sizeof(char *) * 1);
	tmp->args[0] = NULL;
	tmp->red_args = malloc(sizeof(char *) * 1)
	tmp->red_args[0] = NULL;
	table = split_args(node);
	while (table[++i])
	{
		if (check_typeOf_red(table[i]) > 0)
		{
			node->red_args = ft_realloc(node->red_args, ++j);
			node->red_args[j - 1] = ft_
		}
	}
    
	
	
}

*/




