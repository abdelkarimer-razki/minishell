# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 14:06:22 by bboulhan          #+#    #+#              #
#    Updated: 2022/07/04 16:00:23 by bboulhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

CC = cc

HEADER = minishell.h \

INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)

READLINE = $(shell brew --prefix readline)


FILES = minishell.c main_2.c main_3.c ./utils/utils.c ./utils/ft_split.c ./utils/utils_2.c \
		./utils/red_utils_2.c ./Execution/export/export_utils.c ./utils/red_utils_3.c\
		./utils/red_utils.c ./utils/ft_strtrim.c ./Parser/checker.c ./utils/bulttins_utils.c \
		./Parser/lexer.c ./Parser/parcer.c ./Parser/set_args_utils.c ./Parser/set_args.c \
		./Parser/lexer_utils.c ./Parser/redirection_parcer.c ./Parser/red_parcer_utils.c \
		./Execution/export/export.c ./Execution/echo/echo.c ./Execution/cd/cd.c ./Execution/pwd/pwd.c \
		./Execution/env/env.c ./Execution/exit/exit.c ./Execution/unset/unset.c \
		./Execution/pip.c ./utils/pipe_utils.c ./utils/pipe_utils_2.c ./utils/ft_itoa.c \


OBJS = $(FILES:.c=.o)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE_READLINE) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDE_READLINE)  -L $(LIB_READLINE) -o $(NAME) -lreadline
	clear

clean : 
	rm -f $(OBJS)
	clear

fclean : clean
	rm -f $(NAME)
	clear

re : fclean all

.PHONY : re fclean clean all
