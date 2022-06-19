/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parcer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:20:47 by brahim            #+#    #+#             */
/*   Updated: 2022/06/19 00:19:35 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_red(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
// 			return (2);
// 		else if (str[i] == '>')
// 			return (1);
// 		else if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
// 			return (4);
// 		else if (str[i] == '<')
// 			return (3);		
// 	}
// 	return (0);
// }

// int	check_dif_red(char *str)
// {
// 	int	i;
// 	char	c;
	
// 	i = 0;
// 	c = str[i];
// 	while (str[++i])
// 	{
// 		if (str[i] != c)
// 			return (1);
// 	}
// 	return (0);
// }

// char	*split_red(char *str)
// {
// 	int	i;

// 	i = -1;
// }

// void	set_args(t_list *node)
// {
// 	t_red	*tmp;
// 	int		i;

// 	i = -1;
// 	node->red = malloc(sizeof(t_red) * 1);
// 	tmp = node->red;
// 	tmp->cmd = ft_strdup(node->cmd);
// 	while (node->args[++i])
// 	{
// 		if (check_red(node->args[i]))
// 		{
// 			while (node->args)
// 		}
// 	}
	
// }


// int	red_parcer(t_list *node)
// {
// 	char	*s;
// 	int		i;

// 	i = -1;
// 	s = ft_calloc(1, 1);
// 	while (node->args[++i])
// 	{
// 		if (check_red(node->args[i]) > 0)
// 			s = add_char(s, i + 48);
// 	}
	
// 	if (check_dif_red(s))
// 		set_args();
	
// 	i = -1;
// 	while (s[++i])
// 	{
// 		if ()
// 	}
	
	
// }






