/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:52:44 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/06 18:13:48 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static t_redirections_types	type_red(char *redir)
{
	int	len;

	len = 0;
	while (redir[len])
		len++;
	if (redir[0] == '>' && len == 1)
		return (redir_out);
	else if (redir[0] == '>' && len == 2)
		return (redir_append);
	else if (redir[0] == '<' && len == 1)
		return (redir_in);
	else
		return (redir_heredoc);
}

static int	parse_cmd_tokens(t_lexer **tok, t_args **a, t_files **f,
		t_redirections **red)
{
	while (*tok && pipe_not_qouted(*tok))
	{
		if (!(*tok)->qouted && check_red_pipe((*tok)->input[0]) == 1)
		{
			(*red)->next = init_red(type_red((*tok)->input), (*tok)->next);
			if (!(*red)->next)
				return (0);
			(*tok) = (*tok)->next->next;
			(*red) = (*red)->next;
			continue ;
		}
		if (*a == NULL)
		{
			*a = init_arg((*tok)->input);
			if (!(*a))
				return (0);
			(*tok) = (*tok)->next;
		}
		if (!(*tok))
			break ;
		if (!add_arg_file(*tok, a, f))
			return (0);
		(*tok) = (*tok)->next;
	}
	return (1);
}

t_single_command	*handle_redir(t_lexer *tok, t_args *args, t_files *files)
{
	t_single_command	*cmds;
	t_redirections		*new_red;

	cmds = init_single_command();
	if (!cmds)
		return (NULL);
	new_red = init_red(type_red(tok->input), tok->next);
	if (!new_red)
		return (free_cmd_a_f(cmds, NULL, NULL));
	cmds->redirections = new_red;
	tok = tok->next->next;
	if (!parse_cmd_tokens(&tok, &args, &files, &new_red))
		return (free_cmd_a_f(cmds, args, files));
	if (!convert_args_files(cmds, args, files))
		return (free_cmd_a_f(cmds, args, files));
	free_cmd_a_f(NULL, args, files);
	return (cmds);
}

static t_single_command	*finalize_word_cmd(t_lexer *tok, t_args *args,
		t_files *files)
{
	t_single_command	*cmds;

	if (tok && pipe_not_qouted(tok))
		return (handle_redir(tok, args, files));
	cmds = init_single_command();
	if (!cmds)
		return (NULL);
	if (!convert_args_files(cmds, args, files))
		return (free_cmd_a_f(cmds, args, files));
	free_cmd_a_f(NULL, args, files);
	return (cmds);
}

t_single_command	*handle_word(t_lexer *tok)
{
	t_args	*args;
	t_files	*files;

	files = NULL;
	args = init_arg(tok->input);
	if (!args)
		return (NULL);
	tok = tok->next;
	while (tok && (tok->qouted || check_red_pipe(tok->input[0]) != 1))
	{
		if (!pipe_not_qouted(tok))
			break ;
		if (!add_arg_file(tok, &args, &files))
			return ((t_single_command *)free_cmd_a_f(NULL, args, files));
		tok = tok->next;
	}
	return (finalize_word_cmd(tok, args, files));
}
