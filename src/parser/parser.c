/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:46:41 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/26 17:40:37 by ahhammad         ###   ########.fr       */
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

t_single_command *build_cmd(t_lexer *token)
{
    t_single_command *cmds;

    t_lexer *tok = token;
    if(token  == NULL)
        return (NULL);
    while (tok)
    {
        if (tok->input[0] == '>' || tok->input[0] == '<')
        {
            cmds = handle_redir(tok, NULL, NULL);
            if (!cmds || !cmds->redirections)
                return (free_cmd_a_f(cmds, NULL, NULL));
        }
        else
            cmds = handle_word(tok);
        while (tok)
            if (tok->input[0] != '|')
                tok = tok->next;
            else 
            {
                tok = tok->next;
                break;
            }
    }
    return (cmds);
}
void parsing(t_command *cmds, t_lexer *token)
{
    int i;
    int num_cmds;

    i = 0;
   
    if (!token)
        return ;
    num_cmds = number_of_cmds(token);
    cmds = init_cmd(num_cmds);
    if (!cmds || !cmds->commands)
        return ;
    while (i < num_cmds)
    {
        cmds->commands[i] = build_cmd(token);
        if (!cmds->commands[i])
        {
            free_cmds(cmds);
            break ;
        }
        i++;
    }
    free_all(token);
    token = NULL;
}
