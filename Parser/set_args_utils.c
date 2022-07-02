/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:57:15 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/02 10:15:01 by bboulhan         ###   ########.fr       */
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
		return (0);
	while (str[++j])
		s[j] = str[j];
	if (j == -1)
		j = 0;
	s[j++] = c;
	s[j] = 0;
	free(str);
	return (s);
}

int	check_dollar(char *str, int start, int end)
{
	while (start < end && str[start])
	{
		if (str[start] == '$' && (ft_isalpha(str[start + 1]) || str[start + 1] == '_' || ft_isalnum(str[start + 1])))
			return (start);
		start++;
	}
	return (0);
}

char	*get_env_2(char **s1, char **s2, char **s3, char **s4)
{
	char	*s;
	char	*env;

	env = getmyenv(*s2, g_data.env);
	free(*s2);
	*s2 = ft_strjoin(*s1 ,env);
	free(*s1);
	*s1 = ft_strjoin(*s2, *s3);
	free(*s2);
	*s2 = ft_strjoin(*s4, *s1);
	free(*s4);
	s = ft_strdup(*s2);
	free(*s3);
	free(*s2);
	free(*s1);
	free(env);
	return (s);
}

char	*get_env(char *str)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	int		i;

	i = 0;
	s4 = ft_calloc(1, 1);
	while (str[i])
	{
		s1 = ft_calloc(1, 1);
		s2 = ft_calloc(1, 1);
		s3 = ft_calloc(1, 1);
		while (str[i] && str[i] != '$')
			s1 = add_char(s1, str[i++]);
		i++;
		while (ft_isalpha(str[i]) || ft_isalnum(str[i]) || str[i] == '_')
			s2 = add_char(s2, str[i++]);
		while (str[i] && str[i] != '$')
			s3 = add_char(s3, str[i++]);
		s4 = get_env_2(&s1, &s2, &s3, &s4);
	}
	free(str);
	return (s4);
}