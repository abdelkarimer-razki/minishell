#include "stdio.h"
#include "../../minishell.h"

/*int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/
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
	if (parse_args(argv) == 1)
		printf("\n");
}