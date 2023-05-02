NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g #fsanitize=address

SRC = main.c input_sanitize.c processes.c split_cmds.c utils.c utils2.c signals.c

SRC_GNL = get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

OBJ_GNL = $(SRC_GNL:.c=.o)

all: $(NAME)

$(NAME): $(addprefix SRC/,$(OBJ))  $(addprefix GNL/,$(OBJ_GNL))
	@make -s -C ft_printf
	@make -s -C libft
	@$(CC) $(addprefix SRC/,$(OBJ)) $(addprefix GNL/,$(OBJ_GNL)) ft_printf/libftprintf.a libft/libft.a -o $(NAME) -lreadline

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

commit: fclean

clean: 
	@make clean -s -C ft_printf
	@make clean -s -C libft
	@$(RM) $(addprefix SRC/,$(OBJ))

fclean: clean
	@make fclean -s -C ft_printf
	@make fclean -s -C libft
	@$(RM) $(NAME) $(LIB)

re: fclean all