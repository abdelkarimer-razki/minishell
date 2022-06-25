#include "../minishell.h"

int	check_redirection(char **table)
{
	int	i;
	int	j;

	i = 0;
    j = 0;
    while (table[i])
    {
        if (ft_strncmp(table[i], ">>", ft_strlen(table[i])) == 0 || ft_strncmp(table[i], ">", ft_strlen(table[i])) == 0
            || ft_strncmp(table[i], "<", ft_strlen(table[i])) == 0 || ft_strncmp(table[i], "<<", ft_strlen(table[i])) == 0)
            j++;
        i++;
	}
    return (j);
}

int	check_redirection_index(char **table, int index)
{
	int	i;

	i = index;
	while (table[i])
	{
		if (ft_strncmp(table[i], ">>", ft_strlen(table[i])) == 0 || ft_strncmp(table[i], ">", ft_strlen(table[i])) == 0
			|| ft_strncmp(table[i], "<", ft_strlen(table[i])) == 0 || ft_strncmp(table[i], "<<", ft_strlen(table[i])) == 0)
			break ;
		i++;
	}
	return (i);
}

void here_doc(char *arg, int fd)
{

	char	*str;

	str = ft_strdup("herdoc");
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (ft_strncmp(arg, str, ft_strlen(str)) != 0)
	{
		free(str);
		str = readline(">");
		if (ft_strncmp(arg, str, ft_strlen(str)) != 0)
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
		}
	}
	close(fd);
	dup2(fd, 0);
}

void	redirect_output(int i, int *fd, int k , char *arg)
{
	if (i == 0)
	{
		fd[k] = open(arg, O_RDWR | O_CREAT | O_TRUNC, 0777);
		dup2(fd[k], 1);
	}
	else
	{
		fd[k] = open(arg, O_RDWR | O_CREAT | O_APPEND, 0777);
		dup2(fd[k], 1);
	}
}

int error_dup(int *fd, int k, int i, char *arg)
{
	while (--k >= 0)
		close(fd[k]);
	dup2(fd[i + 1], 1);
	printf(ANSI_COLOR_RED "do3afa2: %s:no such file or directory\n" ANSI_COLOR_RESET, arg);
	return (-1);
}

int	simulate_redirection(t_list *node)
{
	int	i;
	int	j;
	int	*fd;
	int	k;

	j = 0;
	k = -1;
	i = check_redirection(node->args);
	fd = malloc(sizeof(int) * (i + 1));
	fd[i + 1] = dup(1);
	if (i != 0)
	{
		while (++k < i)
		{
			j = check_redirection_index(node->args, j + 1);
			if (ft_strncmp(node->args[j], ">", ft_strlen(node->args[j])) == 0)
				redirect_output(0, fd, k, node->args[j + 1]);
			else if (ft_strncmp(node->args[j], "<", ft_strlen(node->args[j])) == 0)
			{
				fd[k] = open(node->args[j + 1], O_RDWR, 0777);
				if (fd[k] == -1)
					return (error_dup(fd, k, i, node->args[j + 1]));
				else if (fd[k] != -1)
					dup2(fd[k], 0);
			}
			else if (ft_strncmp(node->args[j], ">>", ft_strlen(node->args[j])) == 0)
				redirect_output(1, fd, k, node->args[j + 1]);
			else if (ft_strncmp(node->args[j], "<<", ft_strlen(node->args[j])) == 0)
				here_doc(node->args[j + 1], fd[k]);
		}
	}
	return (1);
}