/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parcer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:20:47 by brahim            #+#    #+#             */
/*   Updated: 2022/07/03 11:05:45 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_args_2(char ***tab, int *j, char *arg)
{
	int		i;
	int		y;
	char	**s;
	char	**table;

	table = *tab;
	i = -1;
	y = *j;
	s = split_with_red(arg);
	if (!s)
		return (0);
	while (s[++i])
	{
		table = ft_realloc(table, ++y);
		table[y - 1] = ft_strdup(s[i]);
	}
	*j = y;
	*tab = table;
	ft_free(s);
	return (1);
}

char	**split_args(t_list *node)
{
	char	**table;
	int		i;
	int		j;

	j = 0;
	i = -1;
	table = malloc(sizeof(char *) * 1);
	table[0] = NULL;
	while (node->table[++i])
	{	
		if (check_red(node->table[i]))
		{
			if (!split_args_2(&table, &j, node->table[i]))
				return (ft_error(0, table, NULL));
		}
		else
		{
			table = ft_realloc(table, ++j);
			table[j - 1] = ft_strdup(node->table[i]);
		}
	}
	table[j] = NULL;
	return (table);
}

int	red_parcing_2(t_list *node, char **table, int *i, int *j)
{
	int	k;

	*i = -1;
	*j = 0;
	k = 0;
	while (table[++(*i)])
	{
		if (check_red(table[*i]) > 0)
		{
			node->red_args = ft_realloc(node->red_args, ++(*j));
			node->red_args[*j - 1] = ft_strdup(table[*i]);
			if (table[*i + 1])
			{
				node->red_args = ft_realloc(node->red_args, ++(*j));
				node->red_args[*j - 1] = ft_strdup(table[++(*i)]);
			}
		}
		else
		{
			node->args = ft_realloc(node->args, ++k);
			node->args[k - 1] = put_arg(table[*i]);
		}
	}
	return (1);
}

int	red_parcer(t_list *node)
{
	t_list	*tmp;

	tmp = node;
	while (tmp)
	{
		if (!red_parcing(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	red_parcing(t_list *node)
{
	char	**table;
	int		i;
	int		j;

	i = -1;
	j = 0;
	table = split_args(node);
	if (!table)
		return (0);
	while (table[++i])
	{
		if (check_red(table[i]))
			j++;
	}
	if (ft_strlen_2(table) < 2 && j > 0)
		return (ft_error_2(3, table, NULL));
	node->cmd = ft_strdup(table[0]);
	node->cmd = check_cmd(node->cmd);
	node->args = malloc(sizeof(char *) * 1);
	node->red_args = malloc(sizeof(char *) * 1);
	node->args[0] = NULL;
	node->red_args[0] = NULL;
	red_parcing_2(node, table, &i, &j);
	ft_free(table);
	return (1);
}
