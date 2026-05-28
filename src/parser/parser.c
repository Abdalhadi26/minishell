/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:46:41 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/28 15:14:09 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command *init_cmd(int num_cmds)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->num_single_commands = num_cmds;
    cmd->commands = malloc(sizeof(t_single_command *) * (num_cmds + 1));
    if (!cmd->commands)
    {
        free(cmd);
        return (NULL);
    }
    return (cmd);
}
int number_of_cmds(t_lexer *token)
{
    t_lexer *tok;
    int num_cmds;

    if (!token)
        return (0);
    tok = token;
    num_cmds = 1;
    while (tok)
    {
        if (tok->input[0] == '|' && !tok->qouted)
            num_cmds++;
        tok = tok->next;
    }
    return (num_cmds);
}

t_single_command *build_cmd(t_lexer **tok)
{
    t_single_command *cmds;
    
    if(tok  == NULL)
        return (NULL);
    while (tok && (*tok) &&  pipe_not_qouted(*tok))
    {
        if (check_red_pipe((*tok)->input[0]) == 1 && !(*tok)->qouted)
        {
            cmds = handle_redir(*tok, NULL, NULL);
            if (!cmds || !cmds->redirections)
                return (free_cmd_a_f(cmds, NULL, NULL));
        }
        else
            cmds = handle_word(*tok);
        if (!cmds)
            return (free_cmd_a_f(cmds, NULL, NULL));
        while (*tok)
            if (!(*tok)->qouted && (*tok)->input[0] == '|')
            {
               return (cmds);
            }
            else 
                (*tok) = (*tok)->next;
    }
    return (cmds);
}
t_command *parsing(t_lexer *token)
{
    int i;
    int num_cmds;
    t_lexer *tok;
    t_command *cmds;

    i = 0;
   
    if (!token)
        return (NULL);
    
    num_cmds = number_of_cmds(token);
    cmds = init_cmd(num_cmds);
    if (!cmds || !cmds->commands)
        return (NULL);
    tok = token;
    printf("num %d\n" , cmds->num_single_commands);
    while (i < num_cmds)
    {
        cmds->commands[i] = build_cmd(&tok);
        if (!cmds->commands[i])
        {
            free_cmds(cmds);
            break ;
        }
        
        if (tok)
            {printf("%s\n" , tok->input);
                tok = tok->next;}
        i++;
    }
    free_all(token);
    token = NULL;
    return (cmds);
}
