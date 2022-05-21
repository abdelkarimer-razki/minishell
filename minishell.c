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

int	main(void)
{
	char	**argv;
	char	*path[] = { "/bin/", "/bin/sh"};
	int		pid;

	while (1)
	{
		pid = fork();
		if (pid == 0)
		{
			argv = ft_split(readline("~$ "), ' ');
			if (execve(ft_strjoin(path[0], argv[0]), argv, NULL) == -1
				&& execve(path[1], argv, NULL) == -1)
			{
				perror("");
			}
			ft_free(argv);
		}
		wait(NULL);
	}
	return (0);
}
