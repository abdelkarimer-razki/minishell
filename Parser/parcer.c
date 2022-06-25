/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:29:49 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/25 22:53:37 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	parcer(t_list *node)
{
	t_list	*tmp;

	tmp = node;
	while (tmp)
	{
		if (!cmd_and_args(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}


// void	lower_case(char	*str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] >= 65 && str[i] <= 90)
// 			str[i] += 32;	
// 	}
// }


char	*delete_quote(char *str)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = -1;
	s = ft_calloc(1, 1);
	s[0] = 0;
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == '"')
		{
			j = i + 1;
			i = quoted(str, i);
			while (str[j] && j < i)
				s = add_char(s, str[j++]);
		}
		else
			s = add_char(s, str[i]);
	}
	free(str);
	return (s);
}


char	*check_cmd(char *str)
{
	int		i;
	char	*cmd;

	i = -1;
	if (str[0] == '$' || str[0] == '.' || str[0] == '/')
	{
		cmd = put_arg(str);
		free(str);
		return (cmd);
	}
	cmd = delete_quote(str);
	while (cmd[++i])
	{
		if (!ft_isalpha(cmd[i]))
			return (ft_error(9, NULL, cmd));			
	}
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] >= 65 && cmd[i] <= 90)
			cmd[i] += 32;	
	}
	return (cmd);
}

int	cmd_and_args(t_list *node)
{
	int	i;
	int	j;
	
	j = 1;
	i = 0;
	node->cmd = ft_strdup(node->table[0]);
	node->cmd = check_cmd(node->cmd);
	if (!node->cmd)
		return (0);
	while (node->table[i])
		i++;
	node->args = malloc(sizeof(char *) * (i + 1));
	if (!node->args)
		ft_error(1, NULL, NULL);
	i = 0;
	node->args[0] = ft_strdup(node->cmd);
	while (node->table[++i])
	{
		node->args[j] = put_arg(node->table[i]);
		if (node->args[j++] == NULL)
			ft_error(1, NULL, NULL);
	}
	node->args[j] = NULL;
	return (1);
}


//------------------------------------------------



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