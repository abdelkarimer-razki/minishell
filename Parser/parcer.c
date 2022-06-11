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
	char	*env;
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
		{
			j = i;
			i = quoted(str, i);
			if (str[j] != str[i])
				ft_error(0);
			if (str[j] == '"')
			{
				if (check_dollar(str, ++j, i))
				{
					env = ft_substr(str, j, (i - j));
					env = get_env(env);
					j = -1;
					while (env[++j])
						s = add_char(s,env[j]);
					j = i;
					free(env);
				}			
			}
			else if (j != i)
			{
				while (j++ < i - 1)
				s = add_char(s, str[j]);
			}
		}
		else
		{
			if (str[i] == '$')
			{
				j = i++ - 1;
				while (str[i] && (ft_isalnum(str[i]) || ft_isalpha(str[i])))
					i++;
				env = ft_substr(str, j, (i - j));
				env = get_env(env);
				j = -1;
				while (env[++j])
					s = add_char(s,env[j]);
				j = i;
				free(env);
			}
			else
				s = add_char(s, str[i]);
		}
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

int	check_dollar(char *str, int start, int end)
{
	while (start < end && str[start])
	{
		if (str[start] == '$')
			return (1);
		start++;
	}
	return (0);
}

char	*get_env(char *str)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*env;
	int		i;

	i = 0;
	s1 = ft_calloc(1, 1);
	s2 = ft_calloc(1, 1);
	s3 = ft_calloc(1, 1);
	while (str[i] && str[i] != '$')
		s1 = add_char(s1, str[i++]);
	i++;
	while (ft_isalpha(str[i]) || ft_isalnum(str[i]))
		s2 = add_char(s2, str[i++]);
	while (str[i])
		s3 = add_char(s3, str[i++]);
	env = getenv(s2);
	free(s2);
	s2 = ft_strjoin(s1 ,env);
	free(s1);
	s1 = ft_strjoin(s2, s3);
	free(s2);
	free(s3);
	free(str);
	return (s1);
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


//----------------------------------------------------------------------------------------------------------------

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