/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:19:27 by bboulhan          #+#    #+#             */
/*   Updated: 2022/06/11 14:07:42 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char			**table;
	char			*str;
	char			*args_index;
	char			*cmd;
	char			**args;
	struct s_list	*next;
}	t_list;

char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t num, size_t size);
void	*ft_free(char **c);
char	**ft_split(char const *s, char c);
char	**ft_realloc(char **table, int size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(int content);
void	checker(char *line, t_list **node);
char	*ft_strtrim(char *s1, char *set);
char	**lexer(char *line, char c);
char	*cut_string(char *str, int i0, int i1);
void	parcing(char *line, t_list *node);
char	*ft_strdup(const char *source);
char	**lexer_space(char *line, char c);
void	ft_putstr_fd(char *s, int fd);
char	*clean_quote(char *str);
int		parcer(t_list *node);
int		cmd_and_args(t_list *node);
char	*put_arg(char *str);
int		quoted(char	*line, int i);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_error(int Er);
char	**lexer2(char *line, char c);
int		check_dollar(char *str, int start, int end);
char	*get_env(char *str);
char	*add_char(char *str, char c);



#endif
