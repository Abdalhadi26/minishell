#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../includes/minishell.h"


typedef struct s_lexer
{
    char *input; // The input string to be tokenized
    int qouted; // Flag to indicate if the input is quoted
    struct s_lexer *next; // Pointer to the next lexer node in the list
} t_lexer;

t_lexer   *init_s_lexer(int len);
char *free_all(t_lexer *head);
t_lexer *new_pipe_red(char *str, char c, int *i);
int check_next_token(t_lexer f_token,t_lexer *s_token);
int pipe_red_dup(t_lexer *head);
void print_error(char *str);
t_lexer    *merge_red(t_lexer *head);
int check_red_pipe(char c);
t_lexer   *add_tokens(char *input,int i,int j);
int check_output_red(t_lexer token, int is_next);
int check_input_red(t_lexer token, int is_next);
t_lexer	*expand_lexer_tokens(t_lexer *lexer, t_shell shell);
void skip_spaces(char *input, int *i);
#endif