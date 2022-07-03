#include "../../minishell.h"

int	ft_atoi(const char *str)
{
	char		*c;
	size_t		k;
	size_t		m;

	c = (char *)str;
	m = 1;
	k = 0;
	while (*c == ' ' || *c == '\n'
		|| *c == '\t' || *c == '\r'
		|| *c == '\f' || *c == '\v' )
	{
		c++;
	}
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			m = m * -1;
		c++;
	}
	while (*c >= '0' && *c <= '9')
	{
		k = (*c - 48) + k * 10;
		c++;
	}
	return ((int)(k * m));
}

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
	printf("exit\n");
	if (table->args[1] && ft_isntdigit(table->args[1]) != -1)
	{
		printf("exit: numeric argument required: %s\n", table->args[1]);
		exit(255);
	}
	if (ft_strlen_2(table->args) > 2)
	{
		printf("exit: too many arguments\n");
		exit(1);
	}
	if (table->args[1] && ft_atoi(table->args[1]) >= 0)
	{
		if (ft_atoi(table->args[1]) > 255)
			exit(ft_atoi(table->args[1]) % 256);
		else
			exit(ft_atoi(table->args[1]));
	}
	else if (table->args[1])
	{
		if (ft_atoi(table->args[1]) >= -256)
			exit(256 + ft_atoi(table->args[1]));
		else
			exit(256 - ((ft_atoi(table->args[1]) * -1) % 256));
	}
	exit(0);
}
