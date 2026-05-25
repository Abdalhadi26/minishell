# Libft

Libft is a custom C library developed as part of the **42 School curriculum**.  
The purpose of this project is to reimplement a set of standard C library functions and create a solid foundation library that will be reused in future projects.

---

##  Objectives

- Gain a deep understanding of how standard C functions work
- Improve skills in:
  - Memory management
  - Pointers and arrays
  - String manipulation
  - File descriptors
  - Linked lists
- Build a reusable and reliable C library

---

## Implemented Functions

### 1. Libc Functions

Reimplementation of common functions from `<ctype.h>`, `<string.h>`, and `<stdlib.h>`:

- `ft_isalpha`
- `ft_isdigit`
- `ft_isalnum`
- `ft_isascii`
- `ft_isprint`
- `ft_strlen`
- `ft_memset`
- `ft_bzero`
- `ft_memcpy`
- `ft_memmove`
- `ft_strlcpy`
- `ft_strlcat`
- `ft_toupper`
- `ft_tolower`
- `ft_strchr`
- `ft_strrchr`
- `ft_strncmp`
- `ft_memchr`
- `ft_memcmp`
- `ft_strnstr`
- `ft_atoi`
- `ft_calloc`
- `ft_strdup`

---

### 2. Additional Functions

Extra utility functions to extend the standard library:

- `ft_substr`
- `ft_strjoin`
- `ft_strtrim`
- `ft_split`
- `ft_itoa`
- `ft_strmapi`
- `ft_striteri`
- `ft_putchar_fd`
- `ft_putstr_fd`
- `ft_putendl_fd`
- `ft_putnbr_fd`

---

## Project Structure

libft/

├── ft_*.c

├── libft.h

├── Makefile

└── README.md

---

##  Compilation

To compile the library:

```bash
make
```

This will generate:
```bash
libft.a and <files>.o
```

After creating main.c
```bash
cc main.c libft.a
```
---
## Addition Rules
```bash
make clean     # Remove object files
make fclean    # Remove object files and libft.a
make re        # Recompile the library
```



