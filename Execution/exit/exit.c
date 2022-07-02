#include "../../minishell.h"

int	ft_isntdigit(char *arv)
{
	int	i;

	i = -1;
	while (arv[++i])
	{
		if ((arv[i] == '-' || arv[i] == '+') && (i == 0))
			i++;
		else if ((arv[i] == '-' || arv[i] == '+') && (i > 0))
			return (1);
		if (arv[i] > '9' || arv[i] < '0')
			return (1);
	}
	if (i == 0)
		return (1);
	return (-1);
}

void	ft_exit(t_list *table)
{
	if (ft_isntdigit(table->args[1]) == -1)
	{
		printf("exit: numeric argument required: %s\n", table->args[1]);
		exit(255);
	}
	if (ft_strlen_2(table->args) != 2)
	{
		printf("exit: too many arguments\n");
		exit(1);
	}
	printf("exit\n");
	exit(0);
}
