#include "../minishell.h"

#include <sys/types.h>
#include <sys/stat.h>

int	check_redirection(char **table)
{
	int	i;
	int	j;

	i = 0;
    j = 0;
    while (table && table[i])
    {
        if (ft_strncmp(table[i], ">>", ft_strlen(table[i])) == 0 || ft_strncmp(table[i], ">", ft_strlen(table[i])) == 0
            || ft_strncmp(table[i], "<", ft_strlen(table[i])) == 0 || ft_strncmp(table[i], "<<", ft_strlen(table[i])) == 0)
            j++;
        i++;
	}
    return (j);
}

int	check_redirection_index(char **table, int index , int k)
{
	int	i;

	if (k == 0)
		i = 0;
	else
		i = index + 1;
	while (table && table[i])
	{
		if (ft_strncmp(table[i], ">>", ft_strlen(table[i])) == 0 || ft_strncmp(table[i], ">", ft_strlen(table[i])) == 0
			|| ft_strncmp(table[i], "<", ft_strlen(table[i])) == 0 || ft_strncmp(table[i], "<<", ft_strlen(table[i])) == 0)
			break ;
		i++;
	}
	return (i);
}

void	here_doc(char *arg, int *fd, int k, int i)
{
	char	*str;
	int		pid;

	str = ft_strdup("herdoc");
	fd[k] = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[i + 1], 0);
		dup2(fd[i], 1);
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
	wait(NULL);
	fd[k] = open("/tmp/heredoc", O_RDWR, 0777);
	dup2(fd[k], 0);
	close(fd[k]);
}

void	redirect_output(int i, int *fd, int k , char *arg, char **str)
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

void error_dup(int *fd, int i)
{
	dup2(fd[i], 1);
	dup2(fd[i + 1], 0);
}

int	check_fd(int *fd, int k, char **str, int c)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (fd[i] == -1)
		{
			if (c == 0)
				printf(ANSI_COLOR_RED "do3afa2: %s:no such file or directory\n" ANSI_COLOR_RESET, str[(i * 2) + 1]);
			return (-1);
		}
		i++;
	}
	return (1);
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
			if (ft_strncmp(node->red_args[j], ">", ft_strlen(node->red_args[j])) == 0)
				redirect_output(0, fd, k, node->red_args[j + 1], node->red_args);
			else if (ft_strncmp(node->red_args[j], "<", ft_strlen(node->red_args[j])) == 0)
			{
				fd[k] = open(node->red_args[j + 1], O_RDWR, 0777);
				if (fd[k] == -1)
					error_dup(fd, i);
				else if (fd[k] != -1)
					dup2(fd[k], 0);
				close(fd[k]);
			}
			else if (ft_strncmp(node->red_args[j], ">>", ft_strlen(node->red_args[j])) == 0)
				redirect_output(1, fd, k, node->red_args[j + 1], node->red_args);
			else if (ft_strncmp(node->red_args[j], "<<", ft_strlen(node->red_args[j])) == 0)
				here_doc(node->red_args[j + 1], fd, k, i);
		}
	}
	return (check_fd(fd, i, node->red_args, 0));
}
