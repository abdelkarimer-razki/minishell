#include "../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

char	*short_readline()
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

void	here_doc(char *arg, int *fd, int k, int i)
{
	char	*str;
	int		pid;
	int		status;

	str = ft_strdup("herdoc");
	fd[k] = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	g_data.sig_q = 2;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		error_dup(fd, i);
		while (ft_strncmp(arg, str, ft_strlen(g_data.str)) != 0)
		{
			free(str);
			str = short_readline();
			if (str == NULL || str[0] == 0)
				exit(0);
			write_str(str, fd[k], arg);
		}
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		g_data.signal = 1;
	close(fd[k]);
	fd[k] = open("/tmp/heredoc", O_RDONLY, 0777);
	dup2(fd[k], 0);
	close(fd[k]);
	g_data.sig_q = 0;
}

void	redirect_input(int *fd, int k, char **str, int j)
{
	fd[k] = open(str[j + 1], O_RDWR, 0777);
	if (fd[k] == -1)
		error_dup(fd, check_redirection(str));
	else if (fd[k] != -1)
		dup2(fd[k], 0);
	close(fd[k]);
}

void	redirect_output(int i, int *fd, int k, char *arg)
{
	if (i == 0)
		fd[k] = open(arg, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (i == 1)
		fd[k] = open(arg, O_RDWR | O_CREAT | O_APPEND, 0777);
	dup2(fd[k], 1);
	close(fd[k]);
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
			{
				printf(ANSI_COLOR_RED "do3afa2: %s:no such file or directory\n"
					ANSI_COLOR_RESET, str[(i * 2) + 1]);
				g_data.exit_status = 1;
			}
			return (0);
		}
		i++;
	}
	return (count_red(k, str));
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
	fd = save_dup_malloc(i);
	if (i != 0)
	{
		while (++k < i && g_data.signal != 1)
		{
			j = check_redirection_index(node->red_args, j, k);
			if (check_fd(fd, i, node->red_args, 1) && ouble(node->red_args[j]))
				ouput_redirections(fd, j, node->red_args, k);
			else if (!ft_strncmp(node->red_args[j], "<", 1))
				redirect_input(fd, k, node->red_args, j);
			else if (!ft_strncmp(node->red_args[j], "<<", 2))
				here_doc(node->red_args[j + 1], fd, k, i);
		}
	}
	return (check_fd(fd, i, node->red_args, 0));
}
