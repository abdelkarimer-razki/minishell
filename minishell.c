/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/04 17:20:53 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_2(t_env *table, char **environ)
{
	g_data.exit_status = 0;
	table->env = ft_strdup_0(environ);
	table->export = ft_strdup_2(table->env);
	g_data.env = ft_strdup_0(environ);
}

int	main(int ac, char **av, char **environ)
{
	t_list	*node;
	char	*line;
	t_env	table;

	(void) av;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	rl_catch_signals = 0;
	main_2(&table, environ);
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
		if (parc(node, line, ac))
			exec(node, &table, av);
		free_all(&node);
	}
}
