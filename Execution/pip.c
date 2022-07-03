#include "../minishell.h"

int	nodelen(t_list *node)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = node;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	**fdalloc(t_list *node, int *d)
{
	int	**fd;
	int	c;

	(*d) = nodelen(node);
	fd = malloc(sizeof(int *) * ((*d) + 1));
	c = 0;
	while (c < (*d) - 1)
	{
		fd[c] = malloc(sizeof(int) * 2);
		c++;
	}
	fd[c] = malloc(sizeof(int) * 2);
	fd[c][0] = dup(1);
	fd[c][1] = dup(0);
	fd[c + 1] = NULL;
	return (fd);
}

void	free_fd(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	close_fd(int **fd, int i, int d)
{
	int	n;

	n = 0;
	if (i != -1)
	{
		while (n < d - 1)
		{
			if (n != i - 1)
				close(fd[n][0]);
			if (n != i)
				close(fd[n][1]);
			n++;
		}
	}
	else
	{
		while (n < d - 1)
		{
			close(fd[n][0]);
			close(fd[n][1]);
			n++;
		}
	}
}

void	pipeit(t_list *node, t_env *table)
{
	int		**fd;
	int		pid;
	int		i;

	fd = fdalloc(node, &table->d);
	pipe_all(table->d, fd);
	i = -1;
	g_data.sig_i = 1;
	g_data.sig_q = 1;
	while (node && ++i >= 0 && g_data.signal != 1)
	{
		if (node->next || i != 0)
		{
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				red_dup_bulttins(fd, i, node, table);
			}
			if (here_check(node->red_args) == 1)
				waitpid(pid, NULL, 0);
		}
		if (!node->next && i != 0)
			last_node(fd, pid, table->d);
		if (table->d == 1 && i == 0 && node)
			one_node(node, table, fd[0]);
		node = node->next;
	}
	g_data.sig_i = 0;
	g_data.sig_q = 0;
}
