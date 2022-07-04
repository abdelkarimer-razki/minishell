/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:29:00 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/04 10:00:50 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check(char *s1, char *set, int i)
{
	int	j;
	int	c;

	j = 0;
	c = i;
	while (set[j] && c >= 0)
	{
		if (s1[c] != set[j])
			j++;
		else
		{
			if (i == 0)
				c++;
			else
				c--;
			j = 0;
		}
	}
	if (i == 0)
		return (c);
	return (i - c);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		c;
	char	*s;

	if (!s1 || !set)
		return (NULL);
	i = check(s1, set, 0);
	c = check(s1, set, ft_strlen(s1) - 1);
	if (i + c > (int)ft_strlen(s1))
	{
		s = malloc(1);
		s[0] = 0;
		free(s1);
		return (s);
	}
	s = malloc(ft_strlen(s1) - (i + c) + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1 + i, ft_strlen(s1) - (i + c));
	s[ft_strlen(s1) - (i + c)] = 0;
	free(s1);
	return (s);
}

char	*ft_strtrim2(char *s1, char *set)
{
	int		i;
	int		c;
	char	*s;

	if (!s1 || !set)
		return (NULL);
	i = check(s1, set, 0);
	c = check(s1, set, ft_strlen(s1) - 1);
	if (i + c > (int)ft_strlen(s1))
	{
		s = malloc(1);
		s[0] = 0;
		free(s1);
		return (s);
	}
	s = malloc(ft_strlen(s1) - (i + c) + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1 + i, ft_strlen(s1) - (i + c));
	s[ft_strlen(s1) - (i + c)] = 0;
	return (s);
}
