/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:47:03 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/28 14:39:16 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Function to add the current token to the lexer list
static void add_current_token(t_lexer **head, t_lexer *current)
{
    t_lexer *temp;

    if (!current && !current->input)
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

static t_lexer *add_token(char *input, int len,int i, int j)
{
    t_lexer *current;
    int k;

    k = 0;
    if (check_red_pipe(input[i + 1]) == 4)
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
        current->input[k] = '\0';
    }
    current->next = NULL;
    return (current);
}

// Function to create a new lexer node based on the input string and add it to the lexer list
static int    new_token(t_lexer **head, char *input, int j, int *i)
{
    int len;
    t_lexer *current;
    t_lexer *another_token;

    len = *i - j;
    if ((input[*i] == '\0' || check_red_pipe(input[*i]) == 3) && len == 0)  //check if there is space or NULL or len is Zero
        return (1); // will go to next index if return 3
    if (len != 0)
    {
            current = add_token(input, len, *i, j);
            if (!current)
                return (0);
            add_current_token(head, current);
            if (check_red_pipe(input[*i + 1]) == 4)
                return (1);
    }
    if (check_red_pipe(input[*i]) == 1 || check_red_pipe(input[*i]) == 2 
        || check_red_pipe(input[*i + 1]) == 4)
    {
        another_token = new_pipe_red(input,input[*i], i);
        if (!another_token)
            return (0);
        add_current_token(head, another_token);
    }
    return (1);
}


static int check_add_qoution(t_lexer **head, char *input, int *i, int *j)
{
    char c;
    int x;

    x = 0;
    c = input[*i];
    (*i)++;
    while (input[*i])
    {
        if (c == input[*i])
        {
            if (input[*i + 1] == '\0')
            {   
                x = new_token(head, input, (*j), (i));
                return (x);
            }
            return (1);
        }
        (*i)++;
    }
    return (0);
}

t_lexer   *add_tokens(char *input,int i,int j)
{
    t_lexer *head;

    if (!input)
        return (NULL);
    head = NULL;
    while (input[i])
    {
        if (check_red_pipe(input[i]) == 5) // should i check if new_token or add_qouted are work currectly or not because malloc fail 
        {
            if (!check_add_qoution(&head, input, &i, &j))
                return ((t_lexer *)free_all(head));
        }
        else if (check_red_pipe(input[i]) || check_red_pipe(input[i + 1]) == 4)
        {
            if (!new_token(&head, input, j, &i))
                return ((t_lexer *)free_all(head));
            j = i;
            if (check_red_pipe(input[i]) || !input[i + 1])
                j++;
        }
        i++;
    }
    return (head);
}


