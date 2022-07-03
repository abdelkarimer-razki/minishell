#include "../../minishell.h"

char	**tabup(char **tab, char *str)
{
	char	**new;
	int		i;
	int		j;
	int		k;
	char	*str_new;

	j = ft_strlen_2(tab);
	i = -1;
	k = 0;
	new = malloc(sizeof(char *) * (j));
	while (++i < j)
	{
		str_new = cut_string(tab[i], 0, find_equal(tab[i]));
		if (ft_strncmp(str_new, str, ft_strlen(str_new)) != 0)
			new[k++] = tab[i];
		free(str_new);
	}
	new[i - 1] = NULL;
	return (new);
}

void	unset(t_env *env, t_list *table)
{
	int	i;

	i = 0;
	if (table->args[1] && table->args[1][0] == '-')
	{
		ft_putstr_fd("do3afa2: pwd: option not supported\n", 2);
		g_data.exit_status = 2;
		return ;
	}
	while (table->args[++i])
	{
		if (check_args(table->args[1]) == -1)
		{
			ft_putstr_fd("unset :invalid argument\n", 2);
			g_data.exit_status = 2;
			return ;
		}
	}
	i = 0;
	while (table->args[++i])
	{
		if (check_table(env->env, table->args[i]) != -1)
			env->env = tabup(env->env, table->args[i]);
		if (check_table(env->export, table->args[i]) != -1)
			env->export = tabup(env->export, table->args[i]);
	}
}
