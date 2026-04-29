
#include "lexer.h"


// Function to initialize a new lexer node
t_lexer   *init_s_lexer(int len)
{
    t_lexer   *lexer;
    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    if (lexer == NULL)
    {
        perror("malloc");
        //fprintf(stderr, "Error: Memory allocation failed for t_lexer\n");
        return (NULL);
    }
    lexer->input = malloc(len + 1);
    if (!lexer->input)
    {
        free(lexer);
        return (NULL);
    }
    lexer->next = NULL;
    lexer->qouted = 0;
    return lexer;
}
// Function to free all lexer nodes and their associated input strings
char *free_all(t_lexer *head, int exit_code)
{
    t_lexer *temp;

    if (!head)
        return (NULL);
    while (head)
    {
        temp = head;
        head = head->next;
        temp->next = NULL;
        free(temp->input);
        free(temp);

    }
    if (exit_code == 0)
        exit(1);
    return (NULL);
}

// Function to check if a character is a redirection operator, pipe, space, null terminator, or quote
int check_redi_pipe(char c)
{
    if (c == '<')
        return(1);
    else if (c == '>')
        return(1);
    else if (c == '|')
        return(2);
    else if (c == ' ' || (c >= 9 && c <= 13))
        return (3);
    else if (c == '\0' || c == '\n')
        return (4);
    else if (c == '\"' || c == '\'')
        return (5);
    return(0);
}

// Function to add the current token to the lexer list
void add_current_token(t_lexer **head, t_lexer *current)
{
    t_lexer *temp;

    if (!current &&!current->input)
        return ; // free all and exit
    temp = *head;
    if (!(*head))
    {
        *head = current;
        return ;
    }
    while((temp)->next)
    {
        (temp) = (temp)->next;
    }
    (temp)->next = current;
}
t_lexer *new_pipe_redir(char c)
{
    t_lexer *token;

    token = init_s_lexer(1);
    if (!token)
        return (NULL);
    token->input[0] = c;
    token->input[1] = '\0';
    return (token);
}

t_lexer *add_token(char *input, int len,int i, int j)
{
    t_lexer *current;
    int k;

    k = 0;
    if (check_redi_pipe(input[i + 1]) == 4)
    {
        i++;
        len++;    
    }
    current = init_s_lexer(len);
    if (!current)
        return (NULL); // free all and exit
    while (j < i)
    {
        current->input[k] = input[j];
        j++;
        k++; 
    }
    current->input[k] = '\0';
    return (current);
}

// Function to create a new lexer node based on the input string and add it to the lexer list
int    new_token(t_lexer **head, char *input, int j, int i)
{
    int len;
    int k;
    t_lexer *current;
    t_lexer *another_token;

    len = i - j;
    k = 0;
    if ((input[i] == '\0' || check_redi_pipe(input[i]) == 3) && len == 0)  //check if there is space or NULL or len is Zero
        return (1); // will go to next index if return 3
    if (len != 0)
    {
        current = add_token(input, len, i, j);
        if (!current)
            return (0);
        add_current_token(head, current);
    }
    if (check_redi_pipe(input[i]) == 1 || check_redi_pipe(input[i]) == 2)
    {
        another_token = new_pipe_redir(input[i]);
        if (!another_token)
            return (0);
        add_current_token(head, another_token);
    }
    return (1);
}
//// 0
//// 0 1 2 3
//// c a t >
//// 
int check_closed(char * input, char c, int i)
{
    while (input[i])
    {
        if (c == input[i])
            return (1);
        i++;
    }
    return (0);
}

int add_qouted(t_lexer **head, char *input,char c, int i)
{
    int len;
    int j;
    t_lexer *current;

    len = 0;
    j = 0;
    while (input[i + len] != c)
        len++;
    if (len == 0)
        return (0);
    current = init_s_lexer(len);
    if (!current)
        return (-1);
    current->qouted = 1;
    if (input[i - 1] == '\"')
        current->qouted = 2;
    while(input[i] != c)
    {
        current->input[j] = input[i];
        j++;
        i++;
    }
    current->input[j] = '\0';
    add_current_token(head, current);
    return (len);
}

int check_add_qoution(t_lexer **head, char *input, int *i, int *j)
{
    int x;

    x = 0;
    if (check_closed(input,input[*i], (*i) + 1) == 0)
            return (0);
    if ((*i) != 0 && check_redi_pipe(input[(*i) - 1]) == 0)//ahskd >> ">>>>>>" ha '>>>'gsda>>'>>' >> >>  >>make leaks must be fixed "the porblem //" >>'>>' " because there is no token before the quote and there is space before the quote // I fixed it, but check if there are leaks or not
    {
        x = new_token(head, input, (*j), (*i));// error if there is no token before the quote}
        if (x == 0)
            return (0);
    }
    x = add_qouted(head, input,input[(*i)], (*i) + 1);
    if (x == -1)
        return (0);
    (*i) = (*i) + 1 + x;
    *j = *i + 1;
    return (1);
}
t_lexer   *add_tokens(char *input,int i,int j)
{
    t_lexer *head;

    if (!input)
        return (NULL);
    head = NULL;
    while (input[i])
    {
        if (check_redi_pipe(input[i]) == 5) // should i check if new_token or add_qouted are work currectly or not because malloc fail 
        {
            if (!check_add_qoution(&head, input, &i, &j))
                return ((t_lexer *)free_all(head, 1));
        }
        else if (check_redi_pipe(input[i]) || check_redi_pipe(input[i + 1]) == 4)
        {
            if (!new_token(&head, input, j, i))
                return ((t_lexer *)free_all(head, 1));
            j = i;
            if (check_redi_pipe(input[i]) || !input[i + 1])
                j++;
        }
        i++;
    }
    return (head);
}


