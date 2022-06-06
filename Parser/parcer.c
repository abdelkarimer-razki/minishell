/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:29:49 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/06 16:29:03 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*clean_quote(char *str)
{
	char	*s;

	s = NULL;
	if (str[0] == '"' || str[0] == 39)
		s = ft_strdup(&str[1]);
	if ((str[ft_strlen(str) - 1] == '"' || str[ft_strlen(str) - 1] == 39) && *s)
		s[ft_strlen(s) - 1] = '\0';
	if (*s)
		return (s);
	return (str);
}

//count how many quote in the command
// int		count_quote(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] == 32 || str[i] == '"')
// 			j++;
// 	}
// 	return (j);
// }

void	parcer(t_list *node)
{
	int	i;
	int	j;

	j = 0;
	i = 0;

	node->cmd = ft_strdup(node->table[0]);
	node->args = malloc(sizeof(char *) * 1);
	if (!node->args)
		exit (0);
	node->args[0] = NULL;
	while (node->table[++i])
	{
		if ((node->table[i][0] == '"' && node->table[i][ft_strlen(node->table[i]) - 1] == '"') || 
			(node->table[i][0] == 39 && node->table[i][ft_strlen(node->table[i]) - 1] == 39))
		{
			//printf("%p\n", node->args);
			printf("heho1\n");
			node->args = ft_realloc(node->args, j + 1);
			usleep(5000);
			//printf("%s\n", clean_quote(node->table[i]));
			node->args[j] = clean_quote(node->table[i]);
			printf("heho\n");
			//printf("%p\n", node->args);
		}
		else
		{
			printf("hey1\n");
			node->args = ft_realloc(node->args, j + 1);
			node->args[j] = node->table[i];
			printf("hey\n");
		}
		printf("%s\t%d\n", node->args[j], j);
		j++;
	}
}