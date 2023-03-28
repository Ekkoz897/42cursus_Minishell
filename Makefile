NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g #fsanitize=address

SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(addprefix SRC/,$(OBJ))
	@make -s -C ft_printf
	@$(CC) -lreadline $(addprefix SRC/,$(OBJ)) ft_printf/libftprintf.a -o $(NAME)

run: $(NAME)
	@./minishell

valgrind: $(NAME)
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./minishell

git: fclean
	@git add .
	@git commit
	@git push
	@clear
	@echo "                                                  "
	@echo "                                                  "
	@echo "         -------Commited and Pushed-------        "
	@echo "                                                  "
	@echo "                                                  "

clean: 
	@make clean -s -C ft_printf
	@$(RM) $(addprefix SRC/,$(OBJ))

fclean: clean
	@make fclean -s -C ft_printf
	@$(RM) $(NAME) $(LIB)

re: fclean all