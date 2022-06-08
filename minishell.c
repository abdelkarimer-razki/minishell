/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/05/20 16:19:13 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (line[i])
	{
		if (line[i] == '|')
			y++;
		i++;
	}
	return (y);
}

void	print(t_list *node)
{
	int	i;

	i = 0;
	while (node)
	{
		while (node->table[i])
			printf("%s&\n", node->table[i++]);
		printf("--------------------\n");
		i = 0;
		node = node->next;
	}
}

void	free_all(t_list **node)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *node;
	i = 0;
	while (tmp)
	{
		ft_free(tmp->table);
		free(tmp->cmd);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
}

int	main(void)
{
	t_list	*node;
	char	*line;

	while (1)
	{
		node = malloc(sizeof(t_list) * 1);
		node->next = NULL;
		line = readline("~$ ");
		if (*line == 0)
		{
			free(line);
			free(node);
			continue ;
		}
		parcing(line, node);
		free(line);
		print(node);
		free_all(&node);
	}
}
