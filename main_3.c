/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:23:56 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/04 12:31:36 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(t_list *node)
{
	int	i;

	i = -1;
	while (node)
	{
		while (node->table[++i])
		{
			if (check_red(node->table[i]))
				return (1);
		}
		i = -1;
		node = node->next;
	}
	return (0);
}

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_data.sig_i == 0)
			rl_redisplay();
		g_data.sig_i = 0;
	}
	else if (signum == SIGQUIT && g_data.sig_q != 2)
	{
		if (g_data.sig_q == 1)
			printf("Quit: 3\n");
		g_data.sig_q = 0;
	}
}

void	exec(t_list *node, t_env table)
{
	table.export = ft_strdup_2(table.env);
	pipeit(node, &table);
	free(g_data.env);
	g_data.env = ft_strdup_0(table.env);
	g_data.signal = 0;
}

int	parc(t_list *node, char *line)
{
	int		i;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	rl_catch_signals = 0;
	g_data.sig_i = 0;
	g_data.sig_i = 0;
	i = 0;
	add_history(line);
	if (lexer(line, node))
	{
		if (check_redirect(node))
			i = red_parcer(node);
		else
			i = parcer(node);
		if (i == 1 && error_checker(node))
		{
			free(line);
			return (1);
		}
	}
	free(line);
	return (0);
}