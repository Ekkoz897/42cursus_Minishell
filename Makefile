NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g #fsanitize=address

SRC = main.c input_sanitize.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(addprefix SRC/,$(OBJ))
	@make -s -C ft_printf
	@make -s -C libft
	@$(CC) -lreadline $(addprefix SRC/,$(OBJ)) ft_printf/libftprintf.a libft/libft.a -o $(NAME)

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
	@make clean -s -C libft
	@$(RM) $(addprefix SRC/,$(OBJ))

fclean: clean
	@make fclean -s -C ft_printf
	@make fclean -s -C libft
	@$(RM) $(NAME) $(LIB)

re: fclean all