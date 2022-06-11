#include <stdio.h>
#include <stdlib.h>
#include "../../minishell.h"

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

int	ft_strlen_2(char **s)
{
	int	i;

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

	s = malloc((ft_strlen(source) + 1) * sizeof(char *));
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
	int		y;

	if (getenv("OLDPWD"))
		y = ft_strlen_2(source) + 1;
	else
		y = ft_strlen_2(source) + 1 + 1;
	s = malloc((y) * sizeof(char **));
	if (!s)
		return (NULL);
	i = 0;
	while (source[i])
	{
		s[i] = ft_strjoin1("declare -x ", ft_strdup(source[i]));
		i++;
	}
	if (y == ft_strlen_2(source) + 1 + 1)
	{
		s[i] = "declare -x OLDPWD";
		s[i + 1] = 0;
	}
	else
		s[i] = 0;
	sort_strings(s);
	return (s);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '_'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha2(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '_') || ft_isdigit(c)) 
		return (1);
	return (0);
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

void	check_args(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[++i])
	{
		j = -1;
		while (arg[i][++j] && arg[i][j] != '=')
		{
			if (ft_isalpha(arg[i][j]) == 0)
			if ((j != 0 && ft_isdigit(arg[i][j]) == 0))
			{
				write(2, "syntax error", 12);
				exit(1);
			}	
		}
	}
}


void	*ft_free(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	while (--i >= 0)
		free(c[i]);
	free(c);
	return (NULL);
}

char	**ft_realloc(char **table, int size)
{
	char	**t;
	int		i;

	i = 0;
	t = malloc((size + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (table[i])
	{
		t[i] = ft_strdup(table[i]);
		i++;
	}
	t[size] = NULL;
	//ft_free(table);
	return (t);
}

void	just_equal(int j, char *arg, t_list *table)
{
	environ = ft_realloc(environ, ft_strlen_2(environ) + 1);
	environ[ft_strlen_2(environ) - 1] = ft_strdup(arg);
	table->export = ft_strdup_2(environ);
}

void plus_equal(int j, char *arg, t_list *table)
{
	table->export = ft_realloc(table->export, ft_strlen_2(table->export) + 1);
	table->export[ft_strlen_2(table->export) - 1] = ft_strjoin1("declare -x ", ft_strjoin1(ft_strdup(arg), arg));
	sort_strings(table->export);
}

void	fill_args(char **arg, t_list *table)
{
	int	i;
	int	j;

	i = 0;
	while (arg[++i])
	{
		j = -1;
		while (arg[i][++j])
		{
			if (arg[i][j] == '=')
			{
				just_equal(j, arg[i], table);
				break ;
			}
			else if (arg[i][j] == '+' && arg[i][j + 1] == '=')
			{
				plus_equal(j, arg[i], table);
				break ;
			}
		}
		table->export = ft_realloc(table->export, ft_strlen_2(table->export) + 1);
		table->export[ft_strlen_2(table->export) - 1] = ft_strjoin1("declare -x ", ft_strdup(arg[i]));
	}
	sort_strings(table->export);
}

int main(int arc, char **argv)
{
	t_list table;
	char	**export;

    table.export = ft_strdup_2(environ);
	if (arc == 1)
		show_export(table.export);
	else
	{
		check_args(argv);
		fill_args(argv, &table);
	}
	show_export(table.export);
	while (1);
}
