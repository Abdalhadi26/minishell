/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:20 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/19 12:30:21 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** unset.c
**
** Implements the unset builtin.
** unset removes variables from the environment.
**
** Usage:
**   unset VARNAME        removes one variable
**   unset VAR1 VAR2 VAR3 removes multiple variables at once
**
** How it works:
**   We walk our environment linked list looking for a node whose
**   key matches the given variable name. When we find it, we
**   unlink it from the list and free its memory.
**   If the variable doesnt exist, we do nothing (no error).
**
** Why must unset be a builtin?
**   Same reason as cd and export - it modifies the shells own
**   environment. A child process cannot remove variables from
**   its parent's environment.
**
** An important test case:
**   unset PATH
**   ls
**   This should fail with "command not found" because without PATH
**   the shell cannot find ls. This tests that your unset actually
**   removes the variable and that your PATH searching respects its absence.
**
** Think of unset as the eraser that removes entries from the
** shells environment dictionary.
*/

#include "../../includes/minishell.h"

int builtin_unset(t_single_command cmd, t_shell *shell)
{
    int i;

    i = 1;
    while (cmd.args[i])
    {
        env_unset(&shell->env, cmd.args[i]);
        i++;
    }
    return (0);
}