/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_files_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:22:16 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/26 17:38:48 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
t_args *init_arg(char *arg)
{
    t_args *new_arg;

    if (!arg)
        return (NULL);
    new_arg = malloc(sizeof(t_args));
    if (!new_arg)
        return (NULL);
    new_arg->arg = ft_strdup(arg);
    new_arg->next = NULL;
    return (new_arg);
}

static t_files *init_files(char *file)
{
    t_files *new_file;

    if (!file)
        return (NULL);
    new_file = malloc(sizeof(t_files));
    if (!new_file)
        return (NULL);
    new_file->files = ft_strdup(file);
    new_file->next = NULL;
    return (new_file);
} 

static int	append_arg(t_lexer *tok, t_args **args)
{
	t_args	*new_arg;
	t_args	*last_arg;

	if ((*args) == NULL)
    	return (0);
    (void)tok;
    new_arg = init_arg(tok->input);
	if (!new_arg)
        return (0);
	last_arg = *args;
	while (last_arg->next)
		last_arg = last_arg->next;
	last_arg->next = new_arg;
	return (1);
}

static int	append_file(t_lexer *tok, t_files **files)
{
	t_files	*new_file;
	t_files	*last_file;

	if (*files == NULL)
	{
		*files = init_files(tok->input);
		if (!*files)
			return (0);
		return (1);
	}
	new_file = init_files(tok->input);
	if (!new_file)
        return (0);
	last_file = *files;
	while (last_file->next)
		last_file = last_file->next;
	last_file->next = new_file;
	return (1);
}

int	add_arg_file(t_lexer *tok, t_args **args, t_files **files)
{
	if (!tok || (!tok->qouted && (check_red_pipe(tok->input[0]) == 1
				|| tok->input[0] == '|')))
	{
		return (1);
	}
	if (tok->input[0] == '-')
		return (append_arg(tok, args));
	else
        return (append_file(tok, files));
    return (1);
}
