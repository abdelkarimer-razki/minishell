/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulttins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:58:24 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 11:06:08 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	access_cmd(char **path, char *arg)
{
	int		i;

	i = 0;
	while (i < 8 && access(ft_strjoin(path[i],
				ft_strjoin("/", arg)), F_OK) == -1)
	i++;
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
	char	**path;

	path = ft_split(getmyenv("PATH", table->env), ':');
	pid = fork();
	if (pid == 0)
	{
		i = access_cmd(path, node->args[0]);
		if (i != 8)
			execve(ft_strjoin(path[i], ft_strjoin("/", node->args[0])),
				node->args, table->env);
		if (i == 8 && execve(node->args[0], node->args, table->env) == -1)
			i++;
		error_exe(i, path);
	}
	waitpid(pid, &g_data.exit_status, 0);
	study_exit_status();
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
	if (node->args[0])
		bulttins_simulator(node, table);
}
