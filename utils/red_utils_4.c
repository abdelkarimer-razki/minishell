/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:09:33 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 21:58:52 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	study_exit_status(void)
{
	if (WIFEXITED(g_data.exit_status))
	{
		WEXITSTATUS(g_data.exit_status);
		g_data.exit_status = g_data.exit_status % 255;
	}
	else if (WIFSIGNALED(g_data.exit_status))
	{
		g_data.exit_status = WTERMSIG(g_data.exit_status) + 128;
		if (g_data.exit_status == 130)
			printf("\n");
		g_data.signal = 1;
	}
	else if (WIFSTOPPED(g_data.exit_status))
		WSTOPSIG(g_data.exit_status);
}

void	here_doc2(int pid, int fd, char *str)
{
	wait_and_study(pid);
	close(fd);
	fd = open("/tmp/heredoc", O_RDWR, 0777);
	dup2(fd, 0);
	close(fd);
	free(str);
	g_data.sig_q = 0;
}
