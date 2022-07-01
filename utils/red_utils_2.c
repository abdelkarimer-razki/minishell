#include "../minishell.h"

int	check_redirection(char **table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (table && table[i])
	{
		if (ft_strncmp(table[i], ">>", 2) == 0
			|| ft_strncmp(table[i], ">", 1) == 0
			|| ft_strncmp(table[i], "<", 1) == 0
			|| ft_strncmp(table[i], "<<", 2) == 0)
			j++;
		i++;
	}
	return (j);
}

int	check_redirection_index(char **table, int index, int k)
{
	int	i;

	if (k == 0)
		i = 0;
	else
		i = index + 1;
	while (table && table[i])
	{
		if (ft_strncmp(table[i], ">>", 2) == 0
			|| ft_strncmp(table[i], ">", 1) == 0
			|| ft_strncmp(table[i], "<", 1) == 0
			|| ft_strncmp(table[i], "<<", 2) == 0)
			break ;
		i++;
	}
	return (i);
}

void	error_dup(int *fd, int i)
{
	dup2(fd[i], 1);
	dup2(fd[i + 1], 0);
}

int	count_red(int k, char **str)
{
	int	i;
	int	in;
	int	out;

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