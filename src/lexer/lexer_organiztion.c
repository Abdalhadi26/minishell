/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_organiztion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:49:49 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/26 17:30:55 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void print_error(char *str)
{
    ft_putstr_fd("bash: syntax error near unexpected token `", 1);
    ft_putstr_fd(str, 1);
    ft_putendl_fd("\'", 1);
}

static int pipe_dup(t_lexer *token)
{
    if (!token)
        return (1);
    if (!token->qouted && token->input[0] == '|')
    {
        if (token->next && !token->next->qouted  && token->next->input[0] == '|')
        {
            print_error("|");
            return (1);
        }
        else if (!token->next)
        {
            print_error("|");
            return (1);
        }    
    }
    return (0);
}

int pipe_red_dup(t_lexer *head)
{
    t_lexer *tk;
    
    tk = head;
    if (!tk->qouted  && check_red_pipe(tk->input[0]) == 2)
    {
        print_error("|");
        return (1);
    }
    while (tk)
    {
        if (!tk->qouted  && check_red_pipe(tk->input[0]) == 1)
        {
            if (check_output_red(*tk, 0) > 2 || check_input_red(*tk, 0) > 3)
                return (1);
            else if (!tk->next || check_red_pipe(tk->next->input[0]))// "< or >" return 1 , "|" return 2 ,  ' ' return 3 , NULL return 4 , < ' or " > return 5
                if (check_next_token(*tk, tk->next) == 1)
                    return (1);
        }
        if (pipe_dup(tk))
            return (1);
        tk = tk->next;
    }
    return (0);
}
