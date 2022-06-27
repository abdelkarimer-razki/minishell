#include "../minishell.h"

int	check_redirection(char **table)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (table && table[i])
	{
		if (ft_strncmp(table[i], ">>", ft_strlen(table[i])) == 0
			|| ft_strncmp(table[i], ">", ft_strlen(table[i])) == 0
			|| ft_strncmp(table[i], "<", ft_strlen(table[i])) == 0
			|| ft_strncmp(table[i], "<<", ft_strlen(table[i])) == 0)
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
		if (ft_strncmp(table[i], ">>", ft_strlen(table[i])) == 0
			|| ft_strncmp(table[i], ">", ft_strlen(table[i])) == 0
			|| ft_strncmp(table[i], "<", ft_strlen(table[i])) == 0
			|| ft_strncmp(table[i], "<<", ft_strlen(table[i])) == 0)
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
