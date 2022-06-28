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
		while (c < i)
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

void  close_fd(int **fd, int d, int c)
{
	int	i;

	i = 0;
	if (d != -1)
	{
		if (d == 0)
			close(fd[0][0]);
		while (i < c)
		{
			if (i != d - 1)
				close(fd[i][0]);
			if (i != d)
				close(fd[i][1]);
			i++;
		}
	}
	else
	{
		while (i < c)
		{
			close(fd[i][0]);
			close(fd[i][1]);
			i++;
		}
	}
}

void	pipeit(t_list *node, t_env *table)
{
	int		**fd;
	int		pid;
	int		i;
	int		d;

	fd = fdalloc(node);
	d = nodelen(node);
	i = -1;
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
				if (node->next)
				{
					dup2(fd[i][1], STDOUT_FILENO);
					close(fd[i][1]);
					if (i == 0)
						close(fd[i][0]);
				}
				if (i != 0)
				{
					dup2(fd[i - 1][0], STDIN_FILENO);
					close(fd[i - 1][0]);
				}
				bulttins(node, table);
				exit(0);
			}
		}
		if (!node->next && i != 0)
		{
			close_fd(fd, -1, d - 1);
			waitpid(pid, NULL, 0);
		}
		if (i == 0 && !node->next)
			bulttins(node, table);
		node = node->next;
		i++;
	}
	/*if (d > 1)
		free_fd(fd);*/
}
