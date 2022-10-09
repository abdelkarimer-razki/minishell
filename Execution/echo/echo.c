/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:08:37 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 21:53:45 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	g_data.exit_status = 0;
}
