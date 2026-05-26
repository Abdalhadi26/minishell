/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_array2sll.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:42:41 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/26 17:36:13 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


static int num_args(t_args *args)
{
    t_args *tok = args;
    int len;

    len = 0;
    while(tok)
    {
        len++;
        tok = tok->next;
    }
    return (len);
}

static int num_files(t_files *args)
{
    t_files *tok = args;
    int len;

    len = 0;
    while(tok)
    {
        len++;
        tok = tok->next;
    }
    return (len);
}

static int merge_args_files(t_single_command *cmd, t_args *arg, t_files *file)
{
    int i;
    
    i = 0;
    while (arg)
    {
        cmd->args[i] = ft_strdup(arg->arg);
        if (!cmd->args[i]) 
            return (0);
        arg = arg->next;
        i++;
        cmd->args[i] = NULL;
    }
    while (file)
    {
        cmd->args[i] = ft_strdup(file->files);
        if (!cmd->args[i]) 
            return (0);
        file = file->next;
        i++;
        cmd->args[i] = NULL;
    }
    return (1);
}
int convert_args_files(t_single_command *cmd, t_args *args, t_files *files)
{
    t_args *arg;
    t_files *file;

    if (!cmd)
        return (0);
    arg = args;
    file = files;
    if (arg)
    {
        if (file)
            cmd->args =malloc((num_args(args)+num_files(files) + 1)
                         * sizeof(char *)); 
        else 
            cmd->args = malloc((num_args(args) + 1) * sizeof(char *));
        if  (!cmd->args)
            return (0);
    }
    if (!merge_args_files(cmd, args, files))
        return (0);
    return (1);
}

