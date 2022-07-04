/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/04 10:55:41 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **environ)
{
	t_list	*node;
	char	*line;
	t_env	table;

	(void)ac;
	(void)av;
	table.env = ft_strdup_0(environ);
	g_data.env = ft_strdup_0(environ);
	while (1)
	{
		node = malloc(sizeof(t_list) * 1);
		init_node(node);
		line = readline("do3afa2-1.0$ ");
		if (line == NULL)
			exit(0);
		if (*line == 0)
		{
			free(line);
			free(node);
			continue ;
		}
		if (parc(node, line))
			exec(node, table);
		free_all(&node);
	}
}
