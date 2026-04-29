CC = cc
#CFLAGS = -Wall -Wextra -Werror -I./includes
OUTDIR = build
OBJDIR = $(OUTDIR)/obj

# Source files
LEXER_SRC = new_lexer.c lexer_organiztion.c
ALL_SRC = $(LEXER_SRC) $(GNL_SRC)

OBJ         = $(LEXER_SRC:.c=.o)
AR          = ar rcs
libft_DIR   = ./libft
gnl_DIR     = ./gnl
# Object files



# Output targets
NAME = lexer.a
LIBNAME = liblexer.a
LIBFT_A = $(libft_DIR)/libft.a
GNL_A = $(gnl_DIR)/libgnl.a

# Default target

# Create build directories



all:$(LIBFT_A) $(GNL_A) $(NAME)
	$(CC) lexer_organiztion.c ./lexer.a ./libft/libft.a ./gnl/libgnl.a -lreadline
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $ -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(libft_DIR)

$(GNL_A):
	$(MAKE) -C $(gnl_DIR)
# Create static library (optional)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(libft_DIR) clean
	$(MAKE) -C $(gnl_DIR) clean

fclean: clean
	rm -f a.out
	rm -f $(NAME)
	$(MAKE) -C $(libft_DIR) fclean
	$(MAKE) -C $(gnl_DIR) fclean
# Phony targets
re : fclean all

.PHONY: clean fclean re all