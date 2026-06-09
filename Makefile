NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I includes -I $(LIBFT_DIR)

SRC = \
	src/main.c \
	src/expander/expander.c \
	src/expander/main_split.c \
	src/expander/expand_spaces.c \
	src/expander/expansion_spliting.c \
	src/expander/searching_var.c \
	src/expander/handle_cases.c \
	src/lexer/lexer_utils.c \
	src/lexer/lexer_organiztion.c \
	src/lexer/lexer_organiztion_heredoc.c \
	src/lexer/check_next_token.c \
	src/lexer/check_next_token_heredoc.c \
	src/lexer/new_lexer.c \
	src/parser/init_strcut.c \
	src/parser/free_data.c \
	src/parser/convert_array2sll.c \
	src/parser/add_files_args.c \
	src/parser/parser_utils.c \
	src/parser/parser.c \
	src/builtins/env.c \
	src/env/env_init.c \
	src/env/env_utils.c \
	src/env/env_utils2.c \
	src/executor/exec_utils.c \
	src/executor/find_path.c \
	src/main_parsing.c \
	src/executor/redirections.c \
	src/executor/heredoc.c \
	src/executor/heredoc_utils.c \
	src/executor/exec_utils2.c \
 	src/executor/executor.c \
 	src/executor/pipes.c \
 	src/builtins/builtins.c \
 	src/builtins/cd.c \
 	src/builtins/echo.c \
 	src/builtins/exit.c \
 	src/builtins/export.c \
 	src/builtins/export_utils.c \
 	src/builtins/pwd.c \
 	src/builtins/unset.c \
 	src/signals/signals.c \
 	src/signals/signal_wait.c \
	src/shell_init.c
	

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c ./includes/minishell.h
	$(CC)  $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
