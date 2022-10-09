/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:31:26 by aer-razk          #+#    #+#             */
/*   Updated: 2022/07/04 20:47:51 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	no_value_fill(t_list *table, int n, int i, t_env *env)
{
	if (n == 0)
		no_value(table->args[i], env);
}

void	set_values(int *j, int *n)
{
	(*j) = -1;
	(*n) = 0;
}

int	tester_args(t_list *table, int i, int j)
{
	if ((table->args[i][j] == '=')
		|| ((table->args[i][j] == '+' && table->args[i][j + 1] == '=')))
		return (1);
	return (0);
}
