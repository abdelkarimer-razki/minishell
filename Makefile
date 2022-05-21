NAME = minishell

FILES = minishell.c ft_split.c ft_strjoin.c ft_strlen.c ft_memcpy.c

INCLUDE = minishell.h

CC = cc 

CFLAGS = -Wall -Wextra -Werror

OBJS = ${FILES:.c=.o}

all:$(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDE) -o $(NAME) -L/usr/local/lib -I/usr/local/include -lreadline
	@echo "SUUUUUUUUIIIIIII"

%.o : %.c $(INCLUDE)
	gcc  $(CFLAGS) -o $@ -c $<

clean:
	@rm -f ${OBJS}
	@echo "SUUUUUUUUIIIIIII"

fclean: clean
	@rm -f ${NAME}
	@rm -f fdf_bonus
	@echo "SUUUUUUUUIIIIIII"

re: fclean all
