/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parcer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:20:47 by brahim            #+#    #+#             */
/*   Updated: 2022/06/25 22:57:28 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_args_2(char ***tab, int *j, char *arg)
{
	int		i;
	int		y;
	char	**s;
	char	**table;

	table = *tab;
	i = -1;
	y = *j;
	s = split_with_red(arg);
	while (s[++i])
	{
		table = ft_realloc(table, ++y);
		table[y - 1] = ft_strdup(s[i]);
	}
	*j = y;
	*tab = table;
	ft_free(s);
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
			split_args_2(&table, &j, node->table[i]);
		else
		{
			table = ft_realloc(table, ++j);
			table[j - 1] = ft_strdup(node->table[i]);
		}
		}
	table[j] = NULL;
	return (table);
}

int	red_parcer_2(t_list *node, char **table)
{
	int		i;
	int	j;

	i = -1;
	j = 0;
	node->cmd = ft_strdup(table[0]);
	node->cmd = check_cmd(node->cmd);
	while (table[++i])
	{
		if (check_red(table[i]) > 0)
			j++;
	}
	node->args = malloc(sizeof(char *) * (i - (j * 2) + 1));
	if (!node->args)
		return (0);
	node->red_args = malloc(sizeof(char *) * (j * 2 + 1));
	if (!node->red_args)
		return (0);
	return (1);
}


int	red_parcer(t_list *node)
{
	char	**table;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	table = split_args(node);
	red_parcer_2(node, table);
	while (table[++i])
	{
		if (check_red(table[i]) > 0)
		{
			node->red_args[j++] = ft_strdup(table[i++]);
			node->red_args[j++] = ft_strdup(table[i]);
		}
		else
			node->args[k++] = put_arg(table[i]);
	}
	node->args[k] = NULL;
	node->red_args[j] = NULL;
	//printf("in red parcer\n");
	ft_free(table);
    return (1);	
}

int	red(t_list *node)
{
	t_list	*tmp;

	tmp = node;
	while (tmp)
	{
		if (!red_parcer(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}














// int	check_typeOf_red(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
// 			return (2);
// 		else if (str[i] == '>')
// 			return (1);
// 		else if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
// 			return (4);
// 		else if (str[i] == '<')
// 			return (3);		
// 	}
// 	return (0);
// }

// int	check_dif_red(char *str)
// {
// 	int	i;
// 	char	c;
	
// 	i = 0;
// 	c = str[i];
// 	while (str[++i])
// 	{
// 		if (str[i] != c)
// 			return (1);
// 	}
// 	return (0);
// }