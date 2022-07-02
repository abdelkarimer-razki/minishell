/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/02 07:10:06 by bboulhan         ###   ########.fr       */
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
	if (signum == SIGINT)
	{
		printf("\n");
	}
	else if (signum == SIGQUIT)
	{	//printf("Quit: 3\n");
		SIG_IGN;
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	print(t_list *node)
{
	int	i;

	i = -1;
	while (node)
	{
		printf("%s\n", node->cmd);
		printf("||||||||||||\n");
		while (node->args[++i])
			printf("%s\n", node->args[i]);
		i = -1;
		//printf("*************************\n");
		if (node->red_args)
		{
			while (node->red_args[++i])
				printf("*%s\n", node->red_args[i]);
		}
		// i = -1;
		// while (node->table[++i])
		// 	printf("%s\n", node->table[i]);
		//printf("%s\n" ,node->args_index);
		i = -1;
		printf("--------------------\n");
		node = node->next;
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
	rl_catch_signals = 0;
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
		g_data.env = ft_strdup_0(table.env);
		g_data.export = ft_strdup_2(g_data.env);
		free(line);
		free_all(&node);
	}
}
