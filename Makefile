NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRC = SRC/main.c

all:	$(NAME)

$(NAME): $(SRC)
	@echo "\nCompiling the program files...\n"
	@make -s -C libft
	@make -s -C ft_printf
	@$(CC) $(CFLAGS) $(SRC) libft/libft.a ft_printf/libftprintf.a -o $(NAME)

clean:
	@find . -type f \( -name "*.o" \) -delete

fclean: clean
	@find . -type f \( -name "*.a" -o -name "minishell" \) -delete

re: fclean all

valgrind: all
	valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all ./minishell

git: fclean
	@git add .
	@git commit
	git push