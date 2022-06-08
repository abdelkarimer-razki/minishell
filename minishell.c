/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/08 11:10:05 by bboulhan         ###   ########.fr       */
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

	i = -1;
	while (node)
	{
		printf("%s\n", node->cmd);
		printf("|||||||\n");
		while (node->args[++i])
			printf("%s\n", node->args[i]);
		// while (node->table[++i])
		// 	printf("%s\n", node->table[i]);
		i = -1;
		printf("--------------------\n");
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
		free(tmp->str);
		free(tmp->cmd);
		ft_free(tmp->args);
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
		parcing(line, node);
		parcer(node);
		print(node);
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