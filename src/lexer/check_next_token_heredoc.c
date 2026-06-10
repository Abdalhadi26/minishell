/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_next_token_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 21:00:49 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/08 14:38:09 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parsing.h"

static int	is_next_output_redir_pipe(t_lexer token)
{
	if (is_output_redir(token))
		return (1);
	else if (get_char_type(token.input[0]) == 2)
	{
		return (1);
	}
	return (0);
}

static int	is_next_input_redir_pipe(t_lexer token)
{
	if (is_input_redir(token))
		return (1);
	else if (get_char_type(token.input[0]) == 2)
	{
		return (1);
	}
	return (0);
}

int	is_output_redir(t_lexer token)
{
	int	i;

	i = 0;
	while (token.input[i] && token.input[i] == '>')
		i++;
	return (i);
}

int	is_input_redir(t_lexer token)
{
	int	i;

	i = 0;
	while (token.input[i] && token.input[i] == '<')
		i++;
	return (i);
}

int	check_sec_token(t_lexer f_token, t_lexer *s_token, t_redirections **here)
{
	if (!s_token)
		return (2);
	if (is_next_output_redir_pipe(*s_token) && !s_token->qouted)
		return (0);
	else if (is_next_input_redir_pipe(*s_token) && !s_token->qouted)
		return (0);
	else if (is_input_redir(f_token) == 2)
	{
		if (!link_red(here, (t_redirections *)init_red(3, s_token)))
		{
			clean_redirections(*here);
			*here = NULL;
			return (0);
		}
	}
	else if (!s_token->qouted && is_output_redir(f_token))
	{
		if (is_next_input_redir_pipe(*s_token)
			|| is_next_output_redir_pipe(*s_token))
			return (0);
	}
	return (4);
}
