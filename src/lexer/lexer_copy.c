
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gnl/get_next_line.h"

typedef struct s_cmd
{
    char *cmd; // The text of the token, e.g. "ls", "cat" ...
    char *arg; // The argument for the token, if applicable (e.g. -a , -la, ...)
    char *file; // The file associated with redirection tokens, if applicable (e.g. "out.txt" for > out.txt)
    char operator; // The operator character for redirection tokens, if applicable (e.g. '>' for > out.txt)
    struct s_cmd *next; // Pointer to the next token in the list
} t_cmd;

t_cmd   *init_s_cmd()
{
    t_cmd   *cmd;
    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (cmd == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for t_cmd\n");
        return (NULL);
    }
    cmd->cmd = NULL;
    cmd->arg = NULL;
    cmd->file = NULL;
    cmd->operator = '\0';
    cmd->next = NULL;
    return cmd;
}

char    *free_s_cmd(t_cmd *cmd)
{
    t_cmd   *temp;
    while (cmd != NULL)
    {
        temp = cmd;
        cmd = cmd->next;
        if (temp->cmd)
            free(temp->cmd);
        if (temp->arg)
            free(temp->arg);
        if (temp->file)
            free(temp->file);
        free(temp);
    }
    return (NULL);
}
char *ft_strcpy(char *dest, const char *src)
{
    char *ptr = dest;
    while (*src)
    {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}

t_cmd   *add_command(char *cmd, char *arg, char *file, char operator)
{
    t_cmd   *new_cmd;
    
    new_cmd = init_s_cmd();

    new_cmd->cmd = malloc(strlen(cmd) + 1);
 

    if (new_cmd->cmd == NULL)
        return ((t_cmd *)free_s_cmd);

    ft_strcpy(new_cmd->cmd, cmd);
    printf("cmmd: %s\n", new_cmd->cmd);
 
    if (arg != NULL)
        new_cmd->arg = malloc(strlen(arg) + 1);
    printf("test2\n");
    if (arg != NULL && new_cmd->arg == NULL)
        return ((t_cmd *)free_s_cmd);
    if (arg != NULL && new_cmd->arg == NULL)
        ft_strcpy(new_cmd->arg, arg);
    
    new_cmd->file = malloc(strlen(file) + 1);
    printf("test3\n");
    
    if (new_cmd->file == NULL)
        return ((t_cmd *)free_s_cmd);
        
    ft_strcpy(new_cmd->file, file);
    
    new_cmd->operator = operator;
    printf("test5\n");
    
    new_cmd->next = NULL;
    return (new_cmd);
}

char    *ft_strdup_lexer( const char *src)
{
    char *ptr = malloc(strlen(src) + 1);
    while (*src)
    {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return ptr;
}

int ft_strlen_lex(const char *str)
{
    int len = 0;
    while (str[len] && str[len] != ' ' && str[len] != '|' && str[len] != '>' && str[len] != '<')
        len++;
    return len;
}
char   *ft_file(char *src, int i, int *j)
{
    char *ptr = malloc(4);
    int k = 0;
    while (k < 4)
    {
        ptr[k] = src[i + *j];
        (*j)++;
        k++;
    }
    ptr[k] = '\0';
    return ptr;
}
char   ft_not_special_chars(char c)
{
    if (c != ' ' && c != '|' && c != '>' && c != '<')
        return (0);
    return (1);
}
char    *ft_token(const char *src)
{
    char *ptr = malloc(strlen(src) + 1);
    while (*src && *src != ' ' && *src != '|' && *src != '>' && *src != '<')
    {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return ptr;
}

t_cmd   *start_lexer(char *argv)
{
    t_cmd   *head;
    t_cmd   *current;
    char    *token;
    char    *arg;
    char    *file;
    char    operator;

    int j; // Index for iterating through the input string
    head = NULL;
    current = NULL;
    file = NULL;
    arg = NULL;
    int i = 0; // Start from 1 to skip the program name in argv[0]
    while(argv[i])
    {
        printf("Processing character: '%c' at index %d\n", argv[i], i);
        j = 0;
        if (argv[i + j] == '>' && file == NULL)
        {
            j++;
            if (argv[i + j] == '>')
            {
                operator = 'A';
                j++;
            } // insert data after last line (append)
            else if (argv[i + j] == '\0' || ft_not_special_chars(argv[i + j]))
                operator = '>'; // insert data into file (overwrite)
            else
            {
                fprintf(stderr, "Error: Invalid syntax near '>'\n");
                return (NULL);
            }
            while (argv[i+j] && argv[i+j] == ' ')
                j++;
            printf("Operator: %c, looking for file after index %d %c\n", operator, i + j, argv[i + j]);
            
            if (argv[i + j] != '\0')
                file = ft_file(argv, i, &j);//the name of file will be after the operator and before pipe 
            //| or end of string
            else
                return (NULL);// error: no file specified after operator
            
            // if (file != NULL)
            // {
            //     i++;
            //     if (!argv[i] && argv[i] != '|')
            //     {
            //         token = ft_token(argv[i]);
            //     }
            //     else
            //     {
            //         token = ft_strdup_lexer("cat");
            //     }

            //     if (token == NULL)
            //     {
            //         fprintf(stderr, "Error: Memory allocation failed for token\n");
            //         return (NULL); // call function to free all allocated memory 
            //     }
            // }
            token = malloc(2);
            token[0] = '1';
            token[1] = '\0';
            printf("Added command: %s, file: %s, operator: %cuu\n", token, file, operator);
            i= i + j;

            head = add_command(token, arg, file, operator);
            printf("Head command: %s, file: %s, operator: %cuu\n", head->cmd, head->file, head->operator);
            break;
            //continue;
        }
    }
    // Tokenization logic goes here
    // For example, you would loop through the input string, identify tokens,
    // and use add_command to create new t_cmd nodes for each token.
    
    return head; // Return the head of the linked list of tokens
}

int main()
{
    char *input_line = NULL;
    // t_cmd *tokens = start_lexer(argv, argc);
    // argc (void); // To avoid unused parameter warning
    write(1, "Input command: " , 15);
    input_line = get_next_line(0); // Read a line of input from the user
    if (input_line == NULL)
    {
        fprintf(stderr, "Error: Failed to read input\n");
        return (1);
    }  
    
    //printf("You entered: %s", input_line);
    // free(input_line); // Free the allocated memory for the input line

    //For testing purposes, you can print the tokens here
    t_cmd *current ;
    
    current = start_lexer(input_line); //  as "ls > out.txt | cat < in.txt |> file.txt ls"
    while (current != NULL)
    {
        printf("Command: %s, Argument: %s, File: %s, Operator: %c\n",
               current->cmd ? current->cmd : "NULL",
               current->arg ? current->arg : "NULL",
               current->file ? current->file : "NULL",
               current->operator);
        current = current->next;
    }
    free (input_line);
    //Free the allocated memory for tokens
    free_s_cmd(current);
    
    return 0;
}