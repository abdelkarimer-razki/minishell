/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:08:12 by aer-razk          #+#    #+#             */
/*   Updated: 2022/05/20 12:08:14 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_checker(char *str)
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
