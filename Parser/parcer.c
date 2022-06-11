/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:29:49 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/11 13:11:26 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *s, char *str, int *x, int *y)
{
	int		i;
	int		j;
	char	*env;

	env = NULL;
	i = *x;
	j = *y;
	j++;
	env = ft_substr(str, j, (i - j));
	env = get_env(env);
	j = -1;
	while (env[++j])
		s = add_char(s,env[j]);
	j = i;
	free(env);
	*x = i;
	*y = j;
	return (s);
}

char	*dollar_and_quote(char *s, char *str, int *x, int *y)
{
	char	*env;
	int		i;
	int		j;

	i = *x;
	j = *y;
	j = i;
	env = NULL;
	i = quoted(str, i);
	if (str[j] != str[i])
		ft_error(0);
	if (str[j] == '"')
	{
		if (check_dollar(str, j, i))
			s = get_env_value(s, str, &i, &j);		
	}
	if (j != i)
	{
		while (j++ < i - 1)
			s = add_char(s, str[j]);
	}
	*x = i;
	*y = j;
	return (s);
}

char	*only_dollar(char *s, char *str, int *x, int *y)
{
	int	i;
	int	j;

	i = *x;
	j = *y;
	if (str[i] == '$')
	{
		j = i++ - 1;
		while (str[i] && (ft_isalnum(str[i]) || ft_isalpha(str[i])))
			i++;
		s = get_env_value(s, str ,&i, &j);
		i--;
	}
	else
		s = add_char(s, str[i]);
	*x = i;
	*y = j;
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
	if (!s)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 39 || str[i] == '"')
			s = dollar_and_quote(s, str, &i, &j);
		else
			s = only_dollar(s, str, &i, &j);
		i++;
	}
	return (s);
}

int	parcer(t_list *node)
{
	t_list	*tmp;

	tmp = node;
	while (tmp)
	{
		cmd_and_args(tmp);
		tmp = tmp->next;
	}
	return (0);
}



// int	check_cmd(char *cmd)
// {
// 	int	i;

// 	i = 0;

// }

int	cmd_and_args(t_list *node)
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
		ft_error(1);
	i = 0;
	while (node->table[++i])
	{
		node->args[j] = put_arg(node->table[i]);
		if (node->args[j++] == NULL)
			ft_error(1);
	}
	node->args[j] = NULL;
	return (0);
}
