/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/11 09:33:19 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int Er)
{
	if (Er == 1)
		printf("Error\n");
	else if (Er == 2)
		printf("command not found\n");
	else if (Er == 3)
		printf("syntax error\n");
	
	return (1);
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

void	free_all(t_list **node)
{
	int		i;
	t_list	*tmp;

	tmp = *node;
	i = 0;
	while (tmp)
	{
		ft_free(tmp->table);
		free(tmp->str);
		free(tmp->cmd);
		//free(tmp->args_index);
		ft_free(tmp->args);
		*node = tmp;
		tmp = tmp->next;
		free(*node);
	}
}

void	bulttins(t_list *node, t_env *table)
{
	if (ft_memcmp(node->cmd, "export", ft_strlen(node->cmd)) == 0)
		export(table ,node);
	else if (ft_memcmp(node->cmd, "echo", ft_strlen(node->cmd)) == 0)
		echo(node->args);
	else if (ft_memcmp(node->cmd, "cd", ft_strlen(node->cmd)) == 0)
		cd(table, node);
	else if (ft_memcmp(node->cmd, "pwd", ft_strlen(node->cmd)) == 0)
		pwd();
	else if (ft_memcmp(node->cmd, "env", ft_strlen(node->cmd)) == 0)
		env(table);
	else if (ft_memcmp(node->cmd, "exit", ft_strlen(node->cmd)) == 0)
		ft_exit();
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
		node->next = NULL;
		line = readline("do3afa2-1.0$ ");
		if (*line == 0)
		{
			free(line);
			free(node);
			continue;
		}
		parcing(line, node);
		if (!parcer(node))
		{
			print(node);
			bulttins(node, &table);
		}
		free(line);
		free_all(&node);
	}
}














// int	main(void)
// {
//  	char	*line;
//  	char	*path;
// 	char 	**argv;
//  	int		pid;

//  	path = "/bin/";
//  	while (1)
//  	{
//  		line = readline("~$ ");
//  		pid = fork();
//  		if (pid == 0)
//  		{
//  			argv = ft_split(readline("~$ "), ' ');
//  			if (execve(ft_strjoin(path, argv[0]), argv, NULL) == -1)
//  				perror("");
//  			ft_free(argv);
//  			/*if (pipe_checker(line) == 1)
//  				with_pipe(line, path);
//  			else
//  				without_pipe(line, path);*/
//  		}
//  		wait(NULL);
//  	}
// }