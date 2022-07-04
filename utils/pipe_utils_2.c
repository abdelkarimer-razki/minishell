/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:58:29 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 10:05:31 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_and_close(int **fd, int i, int ioo)
{
	if (ioo == 1)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][1]);
	}
	else if (ioo == 0)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
	}
}

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	*short_readline(void)
{
	char	*s;
	char	*t;
	int		i;

	i = 1;
	s = ft_calloc(1, 1);
	t = ft_calloc(2, 1);
	while (i)
	{
		write(1, ">", 1);
		while (read(0, t, 1) >= 0)
		{
			if (t[0] == '\n')
			{
				i = 0;
				break ;
			}
			s = add_char(s, t[0]);
			free(t);
			t = ft_calloc(2, 1);
		}
	}
	return (s);
}
