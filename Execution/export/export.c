#include <stdio.h>
#include <stdlib.h>
#include "../../minishell.h"

/*void	*ft_memcpy(void *dest, const void *src, size_t n)
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
}*/

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

/*int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}*/

int	ft_strlen_2(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
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
	free(s1);
	return (s);
}


/*char	*ft_strdup(const char *source)
{
	char	*s;
	int		i;

	s = malloc((ft_strlen(source) + 1) * sizeof(char));
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
}*/

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
	s = malloc((y) * sizeof(char *));
	if (!s)
		return (NULL);
	i = 0;
	while (source[i])
	{
		s[i] =ft_strdup(source[i]);
		i++;
	}
	if (y == ft_strlen_2(source) + 1 + 1)
	{
		s[i] = ft_strdup("OLDPWD");
		s[i + 1] = 0;
	}
	else
		s[i] = 0;
	sort_strings(s);
	return (s);
}

char	**ft_strdup_0(char **source)
{
	char	**s;
	int		i;

	s = malloc((ft_strlen_2(source) + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	i = 0;
	while (source[i])
	{
		s[i] = ft_strdup(source[i]);
		i++;
	}
	s[i] = 0;
	return (s);
}

int	ft_isalpha1(int c)
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
		printf("declare -x ");
		while (export[i][j])
		{
			printf("%c", export[i][j]);
			if (export[i][j] == '=' && n == 0)
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

	i = -1;
	while (arg[++i])
	{
		j = -1;
		while (arg[i][++j] && arg[i][j] != '=' && (arg[i][j] != '+' || arg[i][j + 1] != '='))
		{
			if (j == 0 && ft_isalpha1(arg[i][j]) == 0)
			{
				printf("syntax error\n");
				exit(1);
			}	
			else if ((j != 0 && ft_isalpha2(arg[i][j]) == 0))
			{
				printf("syntax error\n");
				exit(1);
			}	
		}
	}
}


/*void	*ft_free(char **c)
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

void	*ft_calloc(size_t num, size_t size)
{
	char	*x;
	int		y;

	y = num * size;
	x = malloc(y);
	if (!x)
		return (NULL);
	while (y--)
		x[y] = 0;
	return (x);
}

char	**ft_realloc(char **table, int size)
{
	char	**t;
	int		i;

	i = 0;
	t = ft_calloc((size + 1), sizeof(char *));
	if (!t)
		return (NULL);
	while (table[i])
	{
		t[i] = ft_strdup(table[i]);
		i++;
	}
	t[size] = NULL;
	ft_free(table);
	return (t);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start < i)
	{
		if ((i - start) < len)
			str = malloc(i - start + 1);
		else
			str = malloc(len + 1);
		if (!str)
			return (NULL);
		i = 0;
		while (i < len && s[start])
			str[i++] = s[start++];
		str[i] = 0;
		return (str);
	}
	str = malloc(1);
	str[0] = 0;
	return (str);
}*/

int	find_equal(char *table)
{
	int	i;

	i = 0;
	while (table[i] && table[i] != '=' && table[i] != '+')
		i++;
	return (i);
}

int	check_table(char **table, char *arg)
{
	int		i;
	char	*str;
	char	*str1;

	i = -1;
	while (table[++i])
	{
		str = ft_substr(table[i], 0, find_equal(table[i]));
		str1 = ft_substr(arg, 0, find_equal(arg));
		if (ft_memcmp(str, str1, find_equal(table[i])) == 0 && find_equal(table[i]) == find_equal(arg))
			return (free(str), free(str1), i);
		free(str);
		free(str1);
	}
	return (-1);
}

void	just_equal(char *arg, t_env *env)
{
	int	i;

	i = check_table(env->env, arg);
	if (i != -1)
	{
		free(env->env[i]);
		env->env[i] = ft_strdup(arg);
	}
	else
	{
		env->env = ft_realloc(env->env, ft_strlen_2(env->env) + 1);
		env->env[ft_strlen_2(env->env)] = ft_strdup(arg);
	}
	ft_free(env->export);
	env->export = ft_strdup_2(env->env);
}

char	*remove_plus(char *source)
{
	char	*s;
	int		i;
	int		j;

	s = malloc((ft_strlen(source)) * sizeof(char));
	if (!s)
		return (NULL);
	i = -1;
	j = -1;
	while (source[++i])
	{
		if (source[i] == '+')
			continue ;
		j++;
		s[j] = source[i];
	}
	s[j + 1] = 0;
	return (s);
}

void	plus_equal(char *arg, t_env *env)
{
	int		i;

	i = check_table(env->env, arg);
	if (i != -1)
		env->env[i] = ft_strjoin1(env->env[i], ft_substr(arg, find_equal(arg) + 2, ft_strlen(arg) - 1));
	else
	{
		env->env = ft_realloc(env->env, ft_strlen_2(env->env) + 1);
		env->env[ft_strlen_2(env->env)] = remove_plus(arg);
	}
	ft_free(env->export);
	env->export = ft_strdup_2(env->env);
}

void	no_value(char *arg, t_env *env)
{
	int		i;

	i = check_table(env->export, arg);
	if (i == -1)
	{
		env->export = ft_realloc(env->export, ft_strlen_2(env->export) + 1);
		env->export[ft_strlen_2(env->export)] = ft_strdup(arg);
	}
}

void	fill_args(t_env *env, t_list *table)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	while (table->args[++i])
	{
		j = -1;
		n = 0;
		while (table->args[i][++j] && ft_memcmp(table->args[i], "_", find_equal(table->args[i])) != 0)
		{
			if (table->args[i][j] == '=' && n == 0)
			{
				just_equal(table->args[i], env);
				n++;
			}
			else if (table->args[i][j] == '+' && table->args[i][j + 1] == '=' && n == 0)
			{
				plus_equal(table->args[i], env);
				n++;
			}
		}
		if (n == 0)
			no_value(table->args[i], env);
	}
	sort_strings(env->export);
}

void	export(t_env *env, t_list *table)
{
	if (ft_strlen_2(table->args) == 0)
		show_export(env->export);
	else
	{
		check_args(table->args);
		fill_args(env, table);
	}
}