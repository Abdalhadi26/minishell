CC = cc
#CFLAGS = -Wall -Wextra -Werror -I./includes
OUTDIR = build
OBJDIR = $(OUTDIR)/obj

# Source files
LEXER_SRC = new_lexer.c lexer_organiztion.c expander.c
ALL_SRC = $(LEXER_SRC) $(GNL_SRC)

OBJ         = $(LEXER_SRC:.c=.o)
AR          = ar 
ARFLAGS 	= rcs
libft_DIR   = ./libft
gnl_DIR     = ./gnl
# Object files



# Output targets
NAME = ../lexer.a
LIBNAME = liblexer.a
LIBFT_A = $(libft_DIR)/libft.a
GNL_A = $(gnl_DIR)/libgnl.a

# Default target

# Create build directories



all:$(LIBFT_A) $(NAME)
#$(AR) $(ARFLAGS) $(NAME) ./liblexer.a ./libft/libft.a ./gnl/libgnl.a 
$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJ)

%.o: %.c
	$(CC) $ -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(libft_DIR)

# Create static library (optional)

clean:
	rm -f $(OBJ) $(LIBNAME) 
	$(MAKE) -C $(libft_DIR) clean


fclean: clean
	rm -f a.out
	rm -f $(NAME)
	$(MAKE) -C $(libft_DIR) fclean
# Phony targets
re : fclean all

.PHONY: clean fclean re all