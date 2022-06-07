# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bboulhan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 14:06:22 by bboulhan          #+#    #+#              #
#    Updated: 2022/05/21 14:06:24 by bboulhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

CC = cc

HEADER = minishell.h \

FILES = minishell.c utils.c ft_split.c utils_2.c checking.c ft_strtrim.c \
		./Parser/lexer.c\

OBJS = $(FILES:%.c=%.o)

all : $(NAME)
	cd ./Execution/echo/printf && make

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean : 
	rm -f $(OBJS)
	cd ./Execution/echo/printf && make clean

fclean : clean
	rm -f $(NAME)
	cd ./Execution/echo/printf && make fclean

re : fclean all

.PHONY : re fclean clean all
