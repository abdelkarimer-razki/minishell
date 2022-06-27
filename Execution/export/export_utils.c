#include "../../minishell.h"

char	*getmyenv(char *str, char **env)
{
	int	i;

	i = check_table(env, str);
	if (i != -1)
		return (cut_string(env[i], find_equal(env[i]) + 1, ft_strlen(env[i])));
	return (NULL);
}

int find_equal(char *table)
{
	int i;

	i = 0;
	while (table[i] && table[i] != '=' && table[i] != '+')
		i++;
	return (i);
}