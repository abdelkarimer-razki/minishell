/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:29:49 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/11 14:20:55 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	parcer(t_list *node)
{
	t_list	*tmp;

	tmp = node;
	while (tmp)
	{
		cmd_and_args(tmp);
		tmp = tmp->next;
	}
	return (0);
}

// int	check_cmd(char *cmd)
// {
// 	int	i;

// 	i = 0;

// }

int	cmd_and_args(t_list *node)
{
	int	i;
	int	j;
	
	j = 0;
	i = 0;
	node->cmd = ft_strdup(node->table[0]);
	while (node->table[i])
		i++;
	node->args = malloc(sizeof(char *) * i);
	if (!node->args)
		ft_error(1);
	i = 0;
	while (node->table[++i])
	{
		node->args[j] = put_arg(node->table[i]);
		if (node->args[j++] == NULL)
			ft_error(1);
	}
	node->args[j] = NULL;
	return (0);
}
