/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parcer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:20:47 by brahim            #+#    #+#             */
/*   Updated: 2022/06/24 12:11:15 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	**table;
    int 	i;
	int		j;

	j = 0;
    i = -1;
	table = malloc(sizeof(char *) * 1);
    table[0] = NULL;
	while (str[++i])
	{
		if (!is_red(str[i]))
		{
			table = ft_realloc(table, ++j);
			table[j - 1] = ft_calloc(1, 1);
			while (!is_red(str[i]))
				table[j - 1] = add_char(table[j - 1], str[i++]);
		}
		else
		{
			table = ft_realloc(table , ++j);
			table[j - 1] = ft_calloc(1, 1);
			while (is_red(str[i]))
				table[j - 1] = add_char(table[j - 1], str[i++]);
		}
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

	j = 0;
	i = -1;
	k = -1;
	s = NULL;
	table = malloc(sizeof(char *) * 1);
	table[0] = NULL;
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
			if (s)
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
	int		k;

	i = -1;
	j = 0;
	k = 0;
	node->red = malloc(sizeof(t_red ) * 1);
	if (!node->red)
		return (0);
	tmp = node->red;
	table = split_args(node);
	while (table[++i])
	{
		if (check_typeOf_red(table[i]) > 0)
			j++;
		//printf("%s\n", table[i]);
	}
	tmp->args = malloc(sizeof(char *) * (i - (j * 2) + 1));
	if (!tmp->args)
		return (0);
	tmp->red_args = malloc(sizeof(char *) * (j * 2 + 1));
	if (!tmp->red_args)
		return (0);
	//printf("%d\t%d\n", i, j);
	i = -1;
	j = 0;
	while (table[++i])
	{
		if (check_typeOf_red(table[i]) > 0)
		{
			tmp->red_args[j++] = ft_strdup(table[i++]);
			tmp->red_args[j++] = ft_strdup(table[i]);
		}
		else
			tmp->args[k++] = ft_strdup(table[i]);
	}
	tmp->args[k] = NULL;
	tmp->red_args[j] = NULL;
	node->red = tmp;
    return (0);	
}






