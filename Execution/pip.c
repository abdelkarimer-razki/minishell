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

int	**fdalloc(t_list *node)
{
	int	**fd;
	int	c;
	int	i;

	i = nodelen(node);
	if (i > 1)
	{
		fd = malloc(sizeof(int *) * i);
		c = 0;
		while (c < i - 1)
		{
			fd[c] = malloc(sizeof(int) * 2);
			c++;
		}
		fd[c] = NULL;
		return (fd);
	}
	return (NULL);
}

void free_fd(int **fd)
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

void  close_fd(int **fd, int i, int d)
{
	int	n;

	n = 0;
	if (i != -1)
	{
		while (n < d)
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
		while (n < d)
		{
			close(fd[n][0]);
			close(fd[n][1]);
			n++;
		}
	}
}

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

void	pipeit(t_list *node, t_env *table)
{
	int		**fd;
	int		pid;
	int		fd1;
	int		i;
	int		f;
	int		d;
	int		fi[2];

	fd = fdalloc(node);
	d = nodelen(node);
	fi[0] = dup(1);
	fi[1] = dup(0);
	i = -1;
	fd1 = dup(1);
	while (++i < d - 1 && d > 1)
		pipe(fd[i]);
	i = 0;
	while (node)
	{
		if (node->next || i != 0)
		{
			pid = fork();
			if (pid == 0)
			{
				close_fd(fd, i, d - 1);
				f = simulate_redirection(node);
				if (node->next)
					dup_and_close(fd, i, 1);
				if (i != 0 && f != 1 && f != 3 && f != -1)
					dup_and_close(fd, i, 0);
				if (f != -1)
					bulttins(node, table);
				//error_dup(fi, 0);
				exit(0);
			}
		}
		if (node->next)
			waitpid(pid, NULL, 0);
		if (!node->next && i != 0)
		{
			close_fd(fd, -1, d - 1);
			waitpid(pid, NULL, 0);
		}
		if (d == 1 && i == 0)
		{
			if (simulate_redirection(node) != -1)
				bulttins(node, table);
			error_dup(fi, 0);
		}
		node = node->next;
		i++;
	}
	/*if (d > 1)
		free_fd(fd);*/
	
}
