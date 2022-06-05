/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:29:49 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/05 16:15:02 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quoteArg(t_list *node, int i)
{
    int	j;

	j = 1;
	while (node->table[i][j] != node)
	{
		
	}
}

//count how many quote in the command
void	count_quote(char *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (cmd[i] == 32 || cmd[i] == '"')
			j++;
	}
	return (j);
}

void	parcer(t_list *node)
{
	int	i;

	i = 0;
	while (node->table[i])
	{
		if (node->table[i][0] == '"' || node->table[i][0] == 32)
		{
			check_quoteArg(node, i);
		}
	}
}