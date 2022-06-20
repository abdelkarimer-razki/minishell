#include <stdio.h>
#include <stdlib.h>
#include "../../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	if (s3 != NULL || s4 != NULL)
	{
		while ((s3[i] != '\0' || s4[i] != '\0')
			&& i != n)
		{
			if (s3[i] != s4[i])
				return (s3[i] - s4[i]);
			i++;
		}
	}
	return (0);
}

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
	char	*s;

	if (!s1 || !s2)
		return (NULL);
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
			if (ft_strncmp(string[i], string[j], 20) > 0)
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
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c == '_') || ft_isdigit(c))
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

int	check_args(char *arg)
{
	int	j;

	j = -1;
	while (arg[++j]
		&& ((arg[j] != '=' && (arg[j] != '+' || arg[j + 1] != '=')) || j == 0))
	{
		if (j == 0 && ft_isalpha1(arg[j]) == 0)
			return (-1);
		else if ((j != 0 && ft_isalpha2(arg[j]) == 0))
			return (-1);
	}
	return (1);
}

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
		if (ft_strncmp(str, str1, find_equal(table[i])) == 0
			&& find_equal(table[i]) == find_equal(arg))
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
		env->env[ft_strlen_2(env->env) - 1] = ft_strdup(arg);
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
		env->env[i] = ft_strjoin1(env->env[i], ft_substr(arg, find_equal(arg)
					+ 2, ft_strlen(arg) - 1));
	else
	{
		env->env = ft_realloc(env->env, ft_strlen_2(env->env) + 1);
		env->env[ft_strlen_2(env->env) - 1] = remove_plus(arg);
	}
	ft_free(env->export);
	env->export = ft_strdup_2(env->env);
}

void	no_value(char *arg, t_env *env)
{
	int		i;

	i = check_table(env->export, arg);
	printf("%s %d\n ", arg, i);
	if (i == -1)
	{
		env->export = ft_realloc(env->export, ft_strlen_2(env->export) + 1);
		env->export[ft_strlen_2(env->export) - 1] = ft_strdup(arg);
	}
}

void	fill_args(t_env *env, t_list *table)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	while (table->args[++i])
	{
		j = -1;
		n = 0;
		if (check_args(table->args[i]) == -1)
		{
			printf("do3afa2: export: `%s': not a valid identifier\n",
				table->args[i]);
			continue ;
		}
		while (table->args[i][++j] && ft_strncmp(table->args[i], "_",
				find_equal(table->args[i])) != 0)
		{
			if (table->args[i][j] == '=' && n == 0)
			{
				just_equal(table->args[i], env);
				n++;
			}
			else if (table->args[i][j] == '+'
				&& table->args[i][j + 1] == '=' && n == 0)
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
	if (ft_strlen_2(table->args) == 1)
		show_export(env->export);
	else
		fill_args(env, table);
}
