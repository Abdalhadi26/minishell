NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I includes -I $(LIBFT_DIR)

SRC =	src/main.c \
		src/executor/executor.c src/executor/exec_utils.c src/executor/redirections.c src/executor/pipes.c \
		src/env/env_init.c src/env/env_utils.c \
		src/builtins/builtins.c src/builtins/cd.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c \
		src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c src/signals/signals.c src/signals/signal_wait.c \
		src/executor/heredoc.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

%.o: %.c ./includes/minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re