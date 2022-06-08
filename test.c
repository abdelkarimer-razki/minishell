/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:42:57 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/08 16:33:01 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*int	pipe_checker(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '|')
			return (1);
	return (0);
}

void	without_pipe(char *line, char *path)
{
	char	**argv;

	argv = ft_split(line, ' ');
	if (execve(ft_strjoin(path, argv[0]), argv, NULL) == -1)
		perror("");
	ft_free(argv);
}

void	with_pipe(char *line, char *path)
{
	char	**argv;
	int		i;

	argv = ft_split(line, '|');
	i = -1;
	while (argv[++i])
		without_pipe(argv[i], path);
}

int	main(void)
{
	char	*line;
	char	*path;
	int		pid;

	path = "/bin/";
	while (1)
	{
		line = readline("~$ ");
		pid = fork();
		if (pid == 0)
		{
			if (pipe_checker(line) == 1)
				with_pipe(line, path);
			else
				without_pipe(line, path);
		}
		wait(NULL);
	}
	return (0);
}
*/