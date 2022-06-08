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

// char	*clean_quote(char *str)
// {
// 	char	*s;

// 	s = NULL;
// 	if (str[0] == '"' || str[0] == 39)
// 		s = ft_strdup(&str[1]);
// 	if ((str[ft_strlen(str) - 1] == '"' || str[ft_strlen(str) - 1] == 39) && *s)
// 		s[ft_strlen(s) - 1] = '\0';
// 	if (*s)
// 		return (s);
// 	return (str);
// }

char	*add_char(char *str, char c)
{
	char	*s;
	int		j;

	j = -1;
	s = ft_calloc(ft_strlen(str) + 2, 1);
	if (!s)
		return (NULL);
	while (str[++j])
		s[j] = str[j];
	if (j == -1)
		j = 0;
	s[j++] = c;
	s[j] = 0;
	free(str);
	return (s);
}

char	*put_arg(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = ft_calloc(1, 1);
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
		{
			j = i;
			i = quoted(str, i);
			while (j++ < i - 1)
				s = add_char(s, str[j]);
		}
		else
			s = add_char(s, str[i]);
		i++;
	}
	return (s);
}

void	parcer(t_list *node)
{
	t_list	*tmp;

	tmp = node;
	while (tmp)
	{
		cmd_and_args(tmp);
		tmp = tmp->next;
	}
}

void	cmd_and_args(t_list *node)
{
	int	i;
	int	j;
	
	j = 0;
	i = 0;

	node->cmd = ft_strdup(node->table[0]);
	while (node->table[i])
		i++;
	node->args = malloc(sizeof(char *) * i);
	if (!node->args)
		exit (0);
	i = 0;
	while (node->table[++i])
		node->args[j++] = put_arg(node->table[i]);
	node->args[j] = NULL;
}







	// while (node->table[++i])
	// {
	// 	if ((node->table[i][0] == '"' && node->table[i][ft_strlen(node->table[i]) - 1] == '"') || 
	// 		(node->table[i][0] == 39 && node->table[i][ft_strlen(node->table[i]) - 1] == 39))
	// 	{
	// 		node->args[j] = clean_quote(node->table[i]);
	// 	}
	// 	else
	// 		node->args[j] = ft_strdup(node->table[i]);
	// 	j++;
	// }