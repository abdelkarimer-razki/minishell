#include <stdio.h>
#include <stdlib.h>
#include "../../minishell.h"

extern char **environ;

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;

	s = (char *)dest;
	d = (char *)src;
	if (src != NULL || dest != NULL)
	{
		while (n--)
		{
			*s = *d;
			s++;
			d++;
		}
	}
	return (dest);
}

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*str3;
	unsigned char	*str4;

	i = 0;
	str3 = (unsigned char *)str1;
	str4 = (unsigned char *)str2;
	if (str1 != NULL || str2 != NULL)
	{
		while (n--)
		{
			if (*str3 != *str4)
				return (*str3 - *str4);
			str4++;
			str3++;
		}
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2);
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, ft_strlen(s1));
	ft_memcpy(s + ft_strlen(s1), s2, ft_strlen(s2));
	s[i] = 0;
	free(s2);
	return (s);
}


char	*ft_strdup(const char *source)
{
	char	*s;
	int		i;

	i = 0;
	while (source[i])
		i++;
	s = malloc((i + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	i = 0;
	while (source[i])
	{
		s[i] = source[i];
		i++;
	}
	s[i] = 0;
	return (s);
}

void	sort_strings(char **string)
{
	int		i;
	int		j;
	char	*c;

	i = -1;
	while (string[++i])
	{
		j = i + 1;
		while (string[j])
		{
			if (ft_memcmp(string[i], string[j], 20) > 0)
			{
				c = string[i];
				string[i] = string[j];
				string[j] = c;
			}
			j++;
		}
	}
}

char	**ft_strdup_2(char **source)
{
	char	**s;
	int		i;

	i = 0;
	while (source[i])
		i++;
	s = malloc((i + 1) * sizeof(char **));
	if (!s)
		return (NULL);
	i = 0;
	while (source[i])
	{
		s[i] = ft_strjoin1("declare -x ", ft_strdup(source[i]));
		i++;
	}
	s[i] = 0;
	sort_strings(s);
	return (s);
}

void	show_export(char **export)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	while (export[i])
	{
		j = 0;
		n = 0;
		while (export[i][j])
		{
			printf("%c", export[i][j]);
			if (export[i][j] == '=')
			{
				printf("%c", 34);
				n++;
			}
			if (!export[i][j + 1] && n != 0)
				printf("%c", 34);
			j++;
		}
		printf("\n");
		i++;
	}
}

int main(int arc, char **argv)
{
	char	**export;

    export = ft_strdup_2(environ);
	if (arc == 1)
		show_export(export);
}
