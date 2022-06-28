/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:44:23 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/28 02:27:34 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_error(int Er, char **table, char *str)
{
	if (Er == 1)
		printf("Error\n");
	else if (Er == 2)
		printf(ANSI_COLOR_RED "command not found\n" ANSI_COLOR_RESET);
	else if (Er == 3)
		printf(ANSI_COLOR_RED "syntax error\n" ANSI_COLOR_RESET);
	else if (Er == 4)
		printf(ANSI_COLOR_RED "do3afa2: quote not closed \n" ANSI_COLOR_RESET);
	else if (Er == 5)
		printf(ANSI_COLOR_RED "syntax error near unexpected token `||'\n" ANSI_COLOR_RESET);
	if (table)
		ft_free(table);
	if (str)
		free(str);
	return (NULL);
}

int ft_error_2(int Er, char **table, char *str)
{
	if (Er == 1)
		printf("Error\n");
	else if (Er == 2)
		printf(ANSI_COLOR_RED "command not found\n" ANSI_COLOR_RESET);
	else if (Er == 3)
		printf(ANSI_COLOR_RED "syntax error\n" ANSI_COLOR_RESET);
	else if (Er == 4)
		printf(ANSI_COLOR_RED "do3afa2: quote not closed \n" ANSI_COLOR_RESET);
	else if (Er == 5)
		printf(ANSI_COLOR_RED "syntax error near unexpected token `||'\n" ANSI_COLOR_RESET);
	if (table)
		ft_free(table);
	if (str)
		free(str);
	return (0);
}

void	check_memory(t_list *node)
{
	if (node->table)
		ft_free(node->table);
	if (node->str)
		free(node->str);
	if (node->cmd)
		free(node->cmd);
	if (node->args)
		ft_free(node->args);
	if (node->red_args)
		ft_free(node->red_args);
}

void	free_all(t_list **node)
{
	t_list	*tmp;

	tmp = *node;
	while (tmp)
	{
		check_memory(tmp);
		*node = tmp;
		tmp = tmp->next;
		free(*node);
	}
}

void	init_node(t_list *node)
{
	node->args = NULL;
	node->cmd = NULL;
	node->next = NULL;
	node->str = NULL;
	node->table = NULL;
	node->red_args = NULL;
}