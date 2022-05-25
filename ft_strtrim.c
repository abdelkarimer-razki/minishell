/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:29:00 by bboulhan          #+#    #+#             */
/*   Updated: 2021/11/23 02:32:23 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	f1_check(char *x, char const *y)
{
	int	z;

	z = 0;
	while (y[z])
	{
		if (y[z] == *x)
			return (1);
		z++;
	}
	return (0);
}

int	f2_count(char *x, char const *y, char const *s1, int k)
{
	int	j;

	j = 0;
	if (*x != 0)
	{
		while (f1_check(x, y) == 1 && *x)
		{
			j++;
			x++;
		}
		return (j);
	}
	else if (*x == 0)
	{
		x = x - 1;
		while (f1_check(x, y) == 1)
		{
			if (k == (int)ft_strlen(s1) - 1)
				return (k);
			k++;
			x--;
		}
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*x;
	int		n;

	if (!s1 || !set)
		return (NULL);
	x = (char *)s1;
	n = ft_strlen(x) - f2_count(x, set, s1, 0)
		- f2_count(x + ft_strlen(x), set, s1, 0);
	if (n < 0)
	{
		str = malloc (1);
		if (!str)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	x = x + f2_count(x, set, s1, 0);
	str = ft_memcpy(str, x, n);
	str[n] = '\0';
	return (str);
}
