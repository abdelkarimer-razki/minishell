/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:44:46 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/04 21:11:21 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *source)
{
	char	*s;
	int		i;

	i = 0;
	while (source[i])
		i++;
	s = ft_calloc(i + 1, 1);
	if (!s)
		return (NULL);
	i = 0;
	while (source[i] != '\0')
	{
		s[i] = source[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	if (start < i)
	{
		if ((i - start) < len)
			str = ft_calloc(i - start + 1, 1);
		else
			str = ft_calloc(len + 1, 1);
		if (!str)
			return (NULL);
		i = 0;
		while (i < len && s[start])
			str[i++] = s[start++];
		str[i] = 0;
		return (str);
	}
	str = ft_calloc(1, 1);
	str[0] = 0;
	return (str);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*y;

	y = NULL;
	if (new)
	{
		if (*lst == NULL)
			*lst = new;
		y = ft_lstlast(*lst);
		y -> next = new;
		new -> next = NULL;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*y;

	y = NULL;
	if (lst)
	{
		y = lst;
		while (y -> next != NULL)
			y = y -> next;
	}
	return (y);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	k;

	i = 0;
	if (s)
	{
		k = ft_strlen(s);
		while (i < k)
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}
