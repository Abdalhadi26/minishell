/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_organiztion_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:49:49 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/08 16:11:04 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parsing.h"

static int	is_double_pipe(t_lexer *token)
{
	if (!token)
		return (1);
	if (!token->qouted && token->input[0] == '|')
	{
		if (token->next && !token->next->qouted && token->next->input[0] == '|')
			return (1);
		else if (!token->next)
			return (1);
	}
	return (0);
}

int	heredoc_syntax(t_lexer *head, t_redirections **here)
{
	t_lexer	*tk;
	int		flag;

	tk = head;
	*here = NULL;
	if (!tk->qouted && get_char_type(tk->input[0]) == 2)
		return (-1);
	while (tk)
	{
		if (!tk->qouted && get_char_type(tk->input[0]) == 1)
		{
			if (is_output_redir(*tk) > 2 || is_input_redir(*tk) >= 3)
				return (-1);
			flag = check_sec_token(*tk, tk->next, here);
			if (flag == 2 && (*here))
				return (0);
			else if (flag == 0)
				return (-1);
		}
		if (is_double_pipe(tk))
			return (-1);
		tk = tk->next;
	}
	return (1);
}
