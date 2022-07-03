/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/03 16:02:40 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(t_list *node)
{
	int	i;

	i = -1;
	while (node)
	{
		while (node->table[++i])
		{
			if (check_red(node->table[i]))
				return (1);
		}
		i = -1;
		node = node->next;
	}
	return (0);
}

void	handler(int signum)
{
	if (signum == SIGINT && g_data.sig_i == 1)
	{
		 printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_data.sig_i = 0;
	}
	else if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_data.sig_i = 0;
	}
	else if (signum == SIGQUIT && g_data.sig_q == 1)
	{	
		printf("Quit: 3\n");
		g_data.sig_q = 0;
	}
	else if (signum == SIGQUIT)
	{
		//printf("Quit: 3\n");
		g_data.sig_q = 0;
	}
}



int	main(void)
{
	t_list	*node;
	t_env	table;
	char	*line;
	int		i;

	i = -1;
	table.env = ft_strdup_0(environ);
	table.export = ft_strdup_2(table.env);
	g_data.env = ft_strdup_0(environ);
	g_data.export = ft_strdup_2(g_data.env);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	g_data.fd_i[0] = dup(0);
	g_data.fd_i[1] = dup(1);
	rl_catch_signals = 0;
	g_data.sig_i = 0;
	g_data.sig_q = 0;
	while (1)
	{
		g_data.signal = 0;
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
		add_history(line);
		if (lexer(line, node))
		{
			if (check_redirect(node))
				i = red_parcer(node);
			else
				i = parcer(node);
      		if (i == 1 && error_checker(node))
			{	
				//print(node);
				pipeit(node, &table);
			}
		}
		// g_data.env = ft_strdup_0(table.env);
		// g_data.export = ft_strdup_2(g_data.env);
		free(line);
		free_all(&node);
		dup2(g_data.fd_i[0], 0);
		dup2(g_data.fd_i[1], 1);
	}
}
