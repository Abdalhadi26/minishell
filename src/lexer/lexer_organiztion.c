/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_organiztion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:49:49 by ahhammad          #+#    #+#             */
/*   Updated: 2026/04/29 14:56:47 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void delete_token(t_lexer *token)
{
    t_lexer *temp;
    temp = token->next;
    token->next = temp->next;
    temp->next = NULL;
    free(temp->input);
    free(temp);
}
t_lexer    *redirection_check(t_lexer *head)
{
    t_lexer *token;
    
    if (!head)
        return (NULL); // empty list
    token = head;
    while(token && token->next)
    {
        if (!token->qouted && check_redi_pipe(token->input[0]) == 1)
        {
            if (token->input[0] == token->next->input[0] && !token->next->qouted)
                {
                    token->input = ft_strjoin(token->input, token->next->input);
                    if (!token->input)
                    {
                        free_all(head, 1);
                        return (NULL);
                    }
                    delete_token(token);
                    continue;
                }
        }
        token = token-> next;
    }
    return (head);
}

void print_error(char *str)
{
    ft_putstr_fd("bash: syntax error near unexpected token `", 1);
    ft_putstr_fd(str, 1);
    ft_putendl_fd("\'", 1);
}

int check_output_red(t_lexer token, int is_next)
{
    int i;

    i = 0;
    while (token.input[i] && token.input[i] == '>')
        i++;
    if ((i + is_next) == 3)
        print_error(">");
    else if ((i + is_next) > 3)
        print_error(token.input + (i - 2));
    return (i);
}

int check_input_red(t_lexer token, int is_next)
{
    int i;

    i = 0;
    while (token.input[i] && token.input[i] == '<')
        i++;
    if ((i + is_next) == 4)
        print_error("<");
    else if ((i + is_next) == 5)
        print_error(token.input + (i - 2));
    else if ((i + is_next) > 5)
        print_error(token.input + (i - 3));
    return (i);
}

int s_token_check_o_p(t_lexer token)
{
    if (check_output_red(token, 2))
        return (1);
    else if (check_redi_pipe(token.input[0]) == 2) // "< or >" return 1 , "|" return 2 ,  ' ' return 3 , NULL return 4 , < ' or " > return 5
    {
            print_error("|4");
            return (1);
    }
    return (0);
}

int s_token_check_i_p(t_lexer token)
{
    if (check_input_red(token, 3))
        return (1);
    else if (check_redi_pipe(token.input[0]) == 2) // "< or >" return 1 , "|" return 2 ,  ' ' return 3 , NULL return 4 , < ' or " > return 5 
    {
        print_error("|3");
        return (1);
    }
    return (0);
}
int check_next_token(t_lexer f_token,t_lexer *s_token)
{
    if (!s_token)
    {
        print_error("newline");// after that Will make free all then goback to main or 
        return (1);
    }
    else if (!s_token->qouted && check_input_red(f_token, 0))
    {
        if (s_token_check_o_p(*s_token))
            return (1);
        else 
            return (0);
    }
    else if (!s_token->qouted && check_output_red(f_token, 0))
    {
        if (s_token_check_i_p(*s_token))
            return(1);
        else 
            return (0);
    }
    return (0);
}

int pipe_dup(t_lexer *token)
{
    if (!token)
        return (1);
    if (!token->qouted && token->input[0] == '|')
    {
        if (token->next && !token->next->qouted  && token->next->input[0] == '|')
        {
            print_error("|10");
            return (1);
        }
        else if (!token->next)
        {
            print_error("|1");
            return (1);
        }    
    }
    return (0);
}

int pipe_redir_dup(t_lexer *head)
{
    t_lexer *tk;
    
    tk = head;
    if (!tk->qouted  && check_redi_pipe(tk->input[0]) == 2)
    {
        print_error("|2");
        return (1);
    }
    while (tk)
    {
        if (!tk->qouted  && check_redi_pipe(tk->input[0]) == 1)
        {
            if (check_output_red(*tk, 0) > 2 || check_input_red(*tk, 0) > 3)
                return (1);
            else if (!tk->next || check_redi_pipe(tk->next->input[0]))// "< or >" return 1 , "|" return 2 ,  ' ' return 3 , NULL return 4 , < ' or " > return 5
                if (check_next_token(*tk, tk->next) == 1)
                    return (1);
        }
        if (pipe_dup(tk))
            return (1);
        tk = tk->next;
    }
    return (0);
}
int main()
{
    char *input_line = NULL;

    

    while(1)
    {
        write(1,"Input command: ", 15);
            input_line = readline("minishell$ ");
        // input_line = get_next_line(0); // Read a line of input from the user
        if (!input_line) // Ctrl+D
            break;

        if (*input_line)           // don't save empty command
            add_history(input_line);

        printf("You entered: %s\n", input_line);
        if (input_line == NULL)
        {
            fprintf(stderr, "Error: Failed to read input\n");
            return (1);
        }  
        t_lexer *current ;
        
        current = add_tokens(input_line, 0 , 0); //  as "ls > out.txt | cat < in.txt |> file.txt ls"
        free(input_line);
        t_lexer *temp ;
        current = redirection_check(current);
        if (!current)
            continue;;
            
        temp = current; //  as "ls > out.txt | cat < in.txt |> file.txt ls"
        //free_all(current, 1);
        if (pipe_redir_dup(current))
        {
            free_all(current, 1);
            continue;
        }
        // printf("\n");
        while (temp != NULL)
        {
            printf("%s \n", temp->input);
            //printf("qouted: %d \n", temp->qouted);
            // write(1,temp->input, strlen(temp->input));
            // write(1,"\n", 1);
            temp = temp->next;
        }
        free_all(current, 1);
        //printf("new input\n");
    }
    return 0;
}
