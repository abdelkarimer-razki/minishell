/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulttins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:58:24 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 21:08:51 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	access_cmd(char **path, char *arg, t_env *table, t_list *node)
{
	int		i;
	char	*arg1;
	char	*path1;

	i = 0;
	arg1 = ft_strjoin("/", arg);
	path1 = ft_strjoin(path[i], arg1);
	while (i < 8 && access(path1, F_OK) == -1)
	{
		free(path1);
		i++;
		path1 = ft_strjoin(path[i], arg1);
	}
	free(path1);
	if (i != 8)
	{
		path1 = ft_strjoin(path[i], arg1);
		execve(path1, node->args, table->env);
		free(path);
	}
	return (i);
}

void	error_exe(int i, char **path)
{
	if (i == 9 || path == NULL || !path[0])
	{
		write(2, "do3afa2: command not found\n", 27);
		exit(127);
	}
}

void	non_bulltins(t_list *node, t_env *table)
{
	int		pid;
	int		i;
	char	*path1;
	char	**path;

	path1 = getmyenv("PATH", table->env);
	path = ft_split(path1, ':');
	sigs(1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		i = access_cmd(path, node->args[0], table, node);
		if (i == 8 && execve(node->args[0], node->args, table->env) == -1)
			i++;
		error_exe(i, path);
	}
	waitpid(pid, &g_data.exit_status, 0);
	sigs(0);
	study_exit_status();
	ft_free(path);
	free(path1);
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
		pwd(table, node);
	else if (ft_strncmp(node->args[0],
			"env", ft_strlen(node->args[0])) == 0)
		env(table, node);
	else if (ft_strncmp(node->args[0],
			"exit", ft_strlen(node->args[0])) == 0)
		ft_exit(node);
	else if (ft_strncmp(node->args[0],
			"unset", ft_strlen(node->args[0])) == 0)
		unset(table, node);
	else
		non_bulltins(node, table);
}

void	bulttins(t_list *node, t_env *table)
{
	if (node->args[0] && g_data.signal == 0)
		bulttins_simulator(node, table);
}
