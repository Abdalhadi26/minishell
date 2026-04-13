NAME        = libgnl.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs
RM          = rm -f

SRC         = get_next_line.c \
              get_next_line_utils.c
OBJ         = $(SRC:.c=.o)

BONUS_SRC   = get_next_line_bonus.c \
              get_next_line_utils_bonus.c
BONUS_OBJ   = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	$(AR) $(NAME) $(BONUS_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
