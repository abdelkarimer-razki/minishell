/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/30 03:40:24 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_red(t_red *red)
// {
// 	red->args = NULL;
// 	red->red_args = NULL;
// 	red->cmd = NULL;
// }
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

void	handler(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGSEGV)
		printf("Segmentation fault: 11\n");
	//rl_replace_line("", 0);
	//rl_on_new_line();
	//rl_redisplay();
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

// void	handler(int sig)
// {
// 	if (sig == SIGINT && g_sig == 0)	
// 	{	printf("\n");
// 		g_sig = 1;
// 	}
// }


int	main(void)
{
	t_list	*node;
	t_env	table;
	char	*line;
	// struct sigaction	sa;

	// sa.sa_sigaction = &handler;
	// sa.sa_flags = SA_RESTART;
	
	int		i;

	i = -1;
	table.env = ft_strdup_0(environ);
	table.export = ft_strdup_2(table.env);
	
	signal(SIGINT, handler);
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
		free(line);
		free_all(&node);
	}
}
