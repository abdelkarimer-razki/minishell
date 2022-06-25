/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/21 17:58:57 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_error(int Er, char **table, char *str)
{
	if (Er == 1)
		printf("Error\n");
	else if (Er == 2)
		printf("command not found\n");
	else if (Er == 3)
		printf("syntax error\n");
	else if (Er == 4)
		printf(ANSI_COLOR_RED "do3afa2: quote not closed \n" ANSI_COLOR_RESET);
	else if (Er == 5)
		printf(ANSI_COLOR_RED "syntax error near unexpected token `||'\n" ANSI_COLOR_RESET);
	if (table)
	{
		ft_free(table);
		return (NULL);
	}
	if (str)
	{
		free(str);
		return (NULL);
	}
	return (0);
}

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
	
	i = -1;
	while (node)
	{
		//printf("%s\n", node->str);
		printf("%s\n", node->cmd);
		printf("||||||||||||\n");
		while (node->args[++i])
			printf("%s\n", node->args[i]);
		i = -1;
		// while (node->table[++i])
		// 	printf("%s\n", node->table[i]);
		//printf("%s\n" ,node->args_index);
		i = -1;
		printf("--------------------\n");
		node = node->next;
	}
}

void	check_memory(t_list *node)
{
	if (node->table)
		ft_free(node->table);
	if (node->str)
		free(node->str);
	if (node->cmd)
	{
		//printf("2\n");
		free(node->cmd);
	}
	if (node->args)
		ft_free(node->args);
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

void	bulttins(t_list *node, t_env *table)
{
	int	pid;
	int	i;
	char **path;

	pid = fork();
	i = 0;
	path = ft_split(getenv("PATH"), ':');
	if (pid == 0)
	{
		simulate_redirection(node); 
		if (ft_strncmp(node->cmd, "export", ft_strlen(node->cmd)) == 0) 
			export(table, node);
		else if (ft_strncmp(node->cmd, "echo", ft_strlen(node->cmd)) == 0)
			echo(node->args);
		else if (ft_strncmp(node->cmd, "cd", ft_strlen(node->cmd)) == 0)
			cd(table, node);
		else if (ft_strncmp(node->cmd, "pwd", ft_strlen(node->cmd)) == 0)
			pwd();
		else if (ft_strncmp(node->cmd, "env", ft_strlen(node->cmd)) == 0)
			env(table);
		else if (ft_strncmp(node->cmd, "exit", ft_strlen(node->cmd)) == 0)
			ft_exit();
		else
		{
			while (i < 8)
			{
				if (execve(ft_strjoin(path[i], ft_strjoin("/", node->cmd)), ft_strdup_red(node->args), table->env) != -1)
					break;
				i++;
			}
			if (i == 8)
				printf(ANSI_COLOR_RED "do3afa2: %s: command not found\n" ANSI_COLOR_RESET, node->cmd);
		}
	}
	wait(NULL);
	ft_free(path);
}

void	init_node(t_list *node)
{
	node->args = NULL;
	node->cmd = NULL;
	node->next = NULL;
	node->red = NULL;
	node->str = NULL;
	node->table = NULL;
}

int	main(void)
{
	t_list	*node;
	t_env	table;
	char	*line;

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
			continue;
		}
		add_history(line);
		if (lexer(line, node))
		{
			if (parcer(node))
      		{
				//print(node);
        		bulttins(node, &table);
      		}
		}
		//else
		//	free(node);
			free_all(&node);
		free(line);
	}
}


