#include "../../minishell.h"

int	parse_args(char **argv)
{
	int	i;
	int	j;

	i = 0;

	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (j == 0 && argv[i][j] != '-')
				break ;
			if (j != 0 && argv[i][j] != 'n')
				break ;
		}
		if (j != ft_strlen(argv[i]))
			break ;
	}
	return (i);
}

int	valid_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_strlen(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	echo(char **argv)
{
	int	i;

	i = parse_args(argv);
	while (i < ft_strlen_2(argv))
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (parse_args(argv) == 1 || valid_arg(argv))
		printf("\n");
}
