/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:02:15 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/28 03:03:43 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(t_list *node)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while (node->table[++i])
	{
		while (node->table[i][++j])
		{
			if (node->table[i][j] == 39 || node->table[i][j] == '"')
				j = quoted(node->table[i], j);
			if (node->table[i][j] == '|')
				return (0);
		}
		j = -1;
	}
	return (1);
}

int	check_dif_red(char *str)
{
	int		i;
	char	c;
	
	i = 0;
	c = str[i];
	while (str[++i])
	{
		if (str[i] != c)
			return (0);
	}
	return (1);
}

int red_errors(t_list *node)
{
	int i;

	i = -1;
	if (!node->red_args)
		return (1);
	while (node->red_args[++i])
	{
		if (check_red(node->red_args[i]) && node->red_args[i + 1] && check_red(node->red_args[i + 1]))
			return (0);
		else if (check_red(node->red_args[i]) && !node->red_args[i + 1])
			return (0);
		else if (!check_dif_red(node->red_args[i]))
			return (0);
	}
	return (1);
}

int	error_checker(t_list *node)
{
	int	i;
	t_list	*tmp;

	i = -1;
	tmp = node;
	while (tmp)
	{
		if (!check_pipe(tmp))
			return (ft_error_2(5, NULL, NULL));
        if (!red_errors(tmp))
			return (ft_error_2(3, NULL, NULL));
        tmp = tmp->next;
	}
	return (1);
}