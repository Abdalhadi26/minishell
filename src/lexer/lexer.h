#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_lexer
{
    char *input; // The input string to be tokenized
    int qouted; // Flag to indicate if the input is quoted
    struct s_lexer *next; // Pointer to the next lexer node in the list
} t_lexer;

t_lexer   *add_tokens(char *input,int i,int j);
int check_redi_pipe(char c);
char * free_all(t_lexer *head, int exit_code);


#endif