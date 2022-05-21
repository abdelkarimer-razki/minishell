NAME = minishell

FILES = minishell.c ft_split.c ft_strjoin.c ft_strlen.c ft_memcpy.c

INCLUDE = minishell.h

CC = cc 

CFLAGS = -Wall -Wextra -Werror

OBJS = ${FILES:.c=.o}

all:$(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDE) -o $(NAME) -L/usr/local/lib -I/usr/local/include -lreadline
	@echo "_______oBBBBB8o______oBBBBBBB "
	@echo "_____o8BBBBBBBBBBB__BBBBBBBBB8________o88o "
	@echo "___o8BBBBBB**8BBBB__BBBBBBBBBB_____oBBBBBBBo, "
	@echo "__oBBBBBBB*___***___BBBBBBBBBB_____BBBBBBBBBBo,  "
	@echo "_8BBBBBBBBBBooooo___*BBBBBBB8______*BB*_8BBBBBBo,  "
	@echo "_8BBBBBBBBBBBBBBBB8ooBBBBBBB8___________8BBBBBBB8, "
	@echo "__*BBBBBBBBBBBBBBBBBBBBBBBBBB8_o88BB88BBBBBBBBBBBB,  "
	@echo "____*BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB8,  "
	@echo "______**8BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB*,  "
	@echo "___________*BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB8*,  "
	@echo "____________*BBBBBBBBBBBBBBBBBBBBBBBB8888**,  "
	@echo "_____________BBBBBBBBBBBBBBBBBBBBBBB*,  "
	@echo "_____________*BBBBBBBBBBBBBBBBBBBBB*,  "
	@echo "______________*BBBBBBBBBBBBBBBBBB8, "
	@echo "_______________*BBBBBBBBBBBBBBBB*,  "
	@echo "________________8BBBBBBBBBBBBBBB8,  "
	@echo "_________________8BBBBBBBBBBBBBBBo,  "
	@echo "__________________BBBBBBBBBBBBBBB8,  "
	@echo "__________________BBBBBBBBBBBBBBBB,  "
	@echo "__________________8BBBBBBBBBBBBBBB8,  "
	@echo "__________________*BBBBBBBBBBBBBBBB,  "
	@echo "__________________8BBBBBBBBBBBBBBBB8, "
	@echo "_________________oBBBBBBBBBBBBBBBBBB,  "
	@echo "________________oBBBBBBBBBBBBBBBBBBB,  "
	@echo "________________BBBBBBBBBBBBBBBBBBBB,  "
	@echo "_______________8BBBBBBBBBBBBBBBBBBB8,  "
	@echo "______________oBBBBBBBBB88BBBBBBBBB8,  "
	@echo "______________8BBBBBBBBB*8BBBBBBBBB*,  "
	@echo "______________BBBBBBBBB*_BBBBBBBBB8,  "
	@echo "______________BBBBBBBB8_oBBBBBBBBB*,  "
	@echo "______________8BBBBBBB__oBBBBBBBB*,  "
	@echo "______________BBBBBBB*__8BBBBBBB*,  "
	@echo "_____________8BBBBBB*___BBBBBBB*,  "
	@echo "____________8BBBBBB8___oBBBBBB8,  "
	@echo "___________8BBBBBB8____8BBBBBB  "
	@echo "__________oBBBBBB8____BBBBBBB8,  "
	@echo "__________BBBBBBB8___BBBBBBBB,  "
	@echo "_________oBBBBBBB8___BBBBBBBB,  "
	@echo "_________8BBBBBB8____BBBBBBB,  "
	@echo "_________BBBBBB*_____8BBBBB*,  "
	@echo "________oBBBB8_______BBBBB,  "
	@echo "________oBBB8________BBBB,  "
	@echo "______8BBBB*_______*BBBBBBBB8o,  "
	@echo "______BBBBB*____________*88BBBo,  "
	@echo "SUUUUUUUUIIIIIII"

%.o : %.c $(INCLUDE)
	@gcc  $(CFLAGS) -o $@ -c $<

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all
