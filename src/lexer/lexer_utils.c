/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 21:13:47 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/30 23:07:41 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer *new_pipe_red(char *str, char c, int *i)
{
    t_lexer *token;
    int len;
    int j;
    
    len = 0;
    j = 0;
    while (str[*i + len] == c)
        len++;
    token = init_s_lexer(len);
    if (!token)
        return (NULL);
    while (j < len)
    {
        token->input[j] = str[*i];
        (*i)++;
        j++;
    }
    token->input[j] = '\0';
    (*i)--;
    return (token);
}

t_lexer   *init_s_lexer(int len)
{
    t_lexer   *lexer;
    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    if (lexer == NULL)
    {
        perror("malloc");
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

char *free_all(t_lexer *head)
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
    return (NULL);
}

int check_red_pipe(char c)
{
    if (c == '<')
        return(1);
    else if (c == '>')
        return(1);
    else if (c == '|')
        return(2);
    else if (c == ' ' || (c >= 9 && c <= 13))
        return (3);
    else if (c == '\n' ||  c == '\0')
        return (4);
    else if (c == '\"' || c == '\'')
        return (5);
    return(0);
}

void skip_spaces(char *input, int *i)
{
    if (!input || !input[*i] || check_red_pipe(input[*i + 1])!= 4)
        return;
    
    while(check_red_pipe(input[*i + 1])!= 4 && check_red_pipe(input[*i]) == 3 
            && check_red_pipe(input[*i + 1]) == 3)
        (*i)++;
}