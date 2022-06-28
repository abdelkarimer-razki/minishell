/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/28 06:11:24 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(t_list *node)
{
	int	i;

	i = -1;
	while (node)
	{
		printf("%s\n", node->cmd);
		printf("||||||||||||\n");
		// while (node->args[++i])
		// 	printf("%s\n", node->args[i]);
		i = -1;
		//printf("*************************\n");
		if (node->red_args)
		{	while (node->red_args[++i])
				printf("%s\n", node->red_args[i]);
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

void	bulttins(t_list *node, t_env *table)
{
	int	pid;
	int	i;
	char **path;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
		if (simulate_redirection(node) == 1)
		{
			if (ft_strncmp(node->args[0], "export", ft_strlen(node->args[0])) == 0)
				export(table, node);
			else if (ft_strncmp(node->args[0], "echo", ft_strlen(node->args[0])) == 0)
				echo(node->args);
			else if (ft_strncmp(node->args[0], "cd", ft_strlen(node->args[0])) == 0)
				cd(table, node);
			else if (ft_strncmp(node->args[0], "pwd", ft_strlen(node->args[0])) == 0)
				pwd();
			else if (ft_strncmp(node->args[0], "env", ft_strlen(node->args[0])) == 0)
				env(table);
			else if (ft_strncmp(node->args[0], "exit", ft_strlen(node->args[0])) == 0)
				ft_exit();
			else
			{
				pid = fork();
				if (pid == 0)
				{
					while (i < 8)
					{
						if (execve(ft_strjoin(path[i], ft_strjoin("/", node->args[0])), node->args, table->env) != -1)
							break;
						i++;
					}
					if (execve(node->args[0], node->args, table->env) == -1)
						i++;
					if (i == 9)
						printf(ANSI_COLOR_RED "do3afa2: %s: command not found\n" ANSI_COLOR_RESET, node->args[0]);
					exit(0);
				}
			}
		}
	wait(NULL);
	ft_free(path);
}

int	check_redirect(t_list *node)
{
	int	i;

	i = -1;
	while (node->table[++i])
	{
		if (check_red(node->table[i]))
			return (1);
	}
	return (0);
}




void	handler(int sig)
{
	// if (sig == SIGINT)
	// 	return ;
	if (sig == SIGTTOU)
		printf("hey\n");
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
	while (1)
	{
		node = malloc(sizeof(t_list) * 1);
		init_node(node);
		line = readline("do3afa2-1.0$ ");
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
				print(node);
        		//bulttins(node, &table);
			}
		}
		signal(SIGTTOU, handler);
		free(line);
		free_all(&node);
	}
}


