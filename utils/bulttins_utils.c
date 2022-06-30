#include "../minishell.h"

void	non_bulltins(t_list *node, t_env *table)
{
	int		pid;
	int		i;
	char	**path;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (i < 8)
		{
			if (execve(ft_strjoin(path[i], ft_strjoin("/", node->args[0])),
					node->args, table->env) != -1)
				break ;
			i++;
		}
		if (execve(node->args[0], node->args, table->env) == -1)
			i++;
		if (i == 9)
			printf(ANSI_COLOR_RED "do3afa2: %s: command not found\n"
				ANSI_COLOR_RESET, node->args[0]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	ft_free(path);
}

void	bulttins_simulator(t_list *node, t_env *table)
{
	if (ft_strncmp(node->args[0], "export", ft_strlen(node->args[0])) == 0)
		export(table, node);
	else if (ft_strncmp(node->args[0],
			"echo", ft_strlen(node->args[0])) == 0)
		echo(node->args);
	else if (ft_strncmp(node->args[0], "cd", ft_strlen(node->args[0])) == 0)
		cd(table, node);
	else if (ft_strncmp(node->args[0],
			"pwd", ft_strlen(node->args[0])) == 0)
		pwd(table);
	else if (ft_strncmp(node->args[0],
			"env", ft_strlen(node->args[0])) == 0)
		env(table);
	else if (ft_strncmp(node->args[0],
			"exit", ft_strlen(node->args[0])) == 0)
		ft_exit();
	else
		non_bulltins(node, table);
}

void	bulttins(t_list *node, t_env *table)
{
	int	fd[2];

	fd[0] = dup(1);
	fd[1] = dup(0);
	if (simulate_redirection(node) == 1)
		bulttins_simulator(node, table);
	error_dup(fd, 0);
}
