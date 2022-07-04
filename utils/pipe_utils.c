/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:58:20 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 19:15:55 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_all(int d)
{
	int	m;

	m = -1;
	while (++m < d)
		wait(NULL);
}

void	last_node(int **fd, int pid, int d)
{
	close_fd(fd, -1, d);
	wait_and_study(pid);
	wait_all(d - 1);
}

void	one_node(t_list *node, t_env *table, int *fi)
{
	if (simulate_redirection(node))
		bulttins(node, table);
	error_dup(fi, 0);
}

void	red_dup_bulttins(int **fd, int i, t_list *node, t_env *table)
{
	int	f;

	close_fd(fd, i, table->d);
	f = simulate_redirection(node);
	if (node->next && f != 3 && f != 2 && f != 0)
		dup_and_close(fd, i, 1);
	if (i != 0 && f != 1 && f != 3 && f != 0)
		dup_and_close(fd, i, 0);
	if (f != 0 && g_data.signal == 0)
		bulttins(node, table);
	exit(0);
}

void	pipe_all(int d, int **fd, int *e)
{
	int	i;

	*e = -1;
	i = -1;
	while (++i < d - 1 && d > 1)
		pipe(fd[i]);
}
