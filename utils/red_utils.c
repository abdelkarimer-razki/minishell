#include "../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

void	here_doc(char *arg, int *fd, int k, int i)
{
	char	*str;
	int		pid;

	str = ft_strdup("herdoc");
	fd[k] = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	pid = fork();
	if (pid == 0)
	{
		error_dup(fd, i);
		while (ft_strncmp(arg, str, ft_strlen(str)) != 0)
		{
			free(str);
			str = readline(">");
			if (ft_strncmp(arg, str, ft_strlen(str)) != 0)
			{
				write(fd[k], str, ft_strlen(str));
				write(fd[k], "\n", 1);
			}
		}
		exit(1);
	}
	waitpid(pid, NULL, 0);
	close(fd[k]);
	fd[k] = open("/tmp/heredoc", O_RDWR, 0777);
	dup2(fd[k], 0);
	close(fd[k]);
}

void	redirect_output(int i, int *fd, int k, char *arg, char **str)
{
	if (i == 0 && check_fd(fd, k, str, 1) != -1)
	{
		fd[k] = open(arg, O_RDWR | O_CREAT | O_TRUNC, 0777);
		dup2(fd[k], 1);
		close(fd[k]);
	}
	else if (i == 1 && check_fd(fd, k, str, 1) != -1)
	{
		fd[k] = open(arg, O_RDWR | O_CREAT | O_APPEND, 0777);
		dup2(fd[k], 1);
		close(fd[k]);
	}
}

int	check_fd(int *fd, int k, char **str, int c)
{
	int	i;
	int	in;
	int	out;

	i = 0;
	while (i < k)
	{
		if (fd[i] == -1)
		{
			if (c == 0)
				printf(ANSI_COLOR_RED "do3afa2: %s:no such file or directory\n"
					ANSI_COLOR_RESET, str[(i * 2) + 1]);
			return (-1);
		}
		i++;
	}
	i = 0;
	in = 0;
	out = 0;
	while (i < k * 2)
	{
		if (ft_strncmp(str[i], ">", 1) == 0
			|| ft_strncmp(str[i], ">>", 2) == 0)
			out++;
		else if (ft_strncmp(str[i], "<", 4) == 0
			|| ft_strncmp(str[i], "<<", 2) == 0)
			in++;
		i++;
	}
	if (out > 0 && in > 0)
		return (3);
	if (out > 0)
		return (2);
	if (in > 0)
		return (1);
	return (0);
}

int	simulate_redirection(t_list *node)
{
	int	i;
	int	j;
	int	*fd;
	int	k;

	j = 0;
	k = -1;
	i = check_redirection(node->red_args);
	fd = malloc(sizeof(int) * (i + 2));
	fd[i] = dup(1);
	fd[i + 1] = dup(0);
	if (i != 0)
	{
		while (++k < i)
		{
			j = check_redirection_index(node->red_args, j, k);
			if (!ft_strncmp(node->red_args[j], ">", 1))
				redirect_output(0, fd, k, node->red_args[j + 1], node->red_args);
			else if (!ft_strncmp(node->red_args[j], "<", 1))
			{
				fd[k] = open(node->red_args[j + 1], O_RDWR, 0777);
				if (fd[k] == -1)
					error_dup(fd, i);
				else if (fd[k] != -1)
					dup2(fd[k], 0);
				close(fd[k]);
			}
			else if (!ft_strncmp(node->red_args[j], ">>", 2))
				redirect_output(1, fd, k, node->red_args[j + 1], node->red_args);
			else if (!ft_strncmp(node->red_args[j], "<<", 2))
				here_doc(node->red_args[j + 1], fd, k, i);
		}
	}
	return (check_fd(fd, i, node->red_args, 0));
}
