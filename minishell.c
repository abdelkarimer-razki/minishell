/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:18:35 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/05 16:11:25 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checking if there is any pipe in the command line
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
	int i = 0;

	while (node)
	{
		while (node->table[i])
			printf("%s&\n", node->table[i++]);
		printf("%s$\n", node->cmd);
		printf("--------------------\n");
		i = 0;
		node = node->next;
	}
}

//free all the allocated memory
void	free_all(t_list **node)
{
	t_list	*tmp;
	
	tmp = *node;
	while ((*node))
	{
		ft_free((*node)->table);
		free((*node)->cmd);
		tmp = *node;
		(*node) = (*node)->next;
		free(tmp);
	}
}

int	main(void)
{
	t_list	*node;
	char	*line;
	//int		pid;

	line = NULL;
	node = NULL;
	
	while (1)
	{
		node = malloc(sizeof(t_list) * 1);
		node->next = NULL;
		line = readline("~$ ");
		parcing(line, node);
		print(node);
		free(line);
		free_all(&node);
	}
}
































	// while (1)
	// {
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		line = readline("~$ ");
	// 		//checker(line, &node);
	// 		//print(node);
	// 	}
	// }
// int	main(void)
// {
// 	char	**argv;
// 	char	*path[] = { "/bin/", "/bin/sh"};
// 	int		pid;

// 	while (1)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			argv = ft_split(readline("~$ "), ' ');
// 			if (execve(ft_strjoin(path[0], argv[0]), argv, NULL) == -1
// 				&& execve(path[1], argv, NULL) == -1)
// 			{
// 				perror("");
// 			}
// 			ft_free(argv);
// 		}
// 		wait(NULL);
// 	}
// 	return (0);
// }

