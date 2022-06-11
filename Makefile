# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 14:06:22 by bboulhan          #+#    #+#              #
#    Updated: 2022/06/11 12:18:01 by bboulhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

CC = cc

HEADER = minishell.h \

FILES = minishell.c ./utils/utils.c ./utils/ft_split.c ./utils/utils_2.c ./utils/ft_strtrim.c \
		./Parser/lexer.c ./Parser/parcer.c ./Parser/parcer_utils.c \

OBJS = $(FILES:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : re fclean clean all
