/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_strcut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:49:45 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/26 17:37:51 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_single_command *init_single_command()
{
    t_single_command *cmd;

    cmd = malloc(sizeof(t_single_command));
    if (!cmd)
        return (NULL);   
    cmd->num_args = 0;
    cmd->args = NULL;
    cmd->redirections = NULL;
    return (cmd);
}


t_redirections  *init_red(t_redirections_types type, t_lexer *token)
{
    t_redirections *redir;
    
    if (!token || !type)
        return (NULL);
    redir = malloc(sizeof(t_redirections));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->file_name = ft_strdup(token->input);
    if (!redir->file_name)
    {
        free(redir);
        return (NULL);
    }
    redir->heredoc_fd = -1;
    redir->heredoc_expansion_status = token->qouted;
    redir->next = NULL;
    return (redir);
}
