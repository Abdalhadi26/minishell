/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_organiztion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:49:49 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/08 16:11:11 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	print_error(char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 1);
	ft_putstr_fd(str, 1);
	ft_putendl_fd("\'", 1);
}

static int	is_double_pipe(t_lexer *token)
{
	if (!token)
		return (1);
	if (!token->qouted && token->input[0] == '|')
	{
		if (token->next && !token->next->qouted && token->next->input[0] == '|')
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

int	check_pipe_redir_syntax(t_lexer *head)
{
	t_lexer	*token;

	token = head;
	if (!token->qouted && get_char_type(token->input[0]) == 2)
	{
		print_error("|");
		return (0);
	}
	while (token)
	{
		if (!token->qouted && get_char_type(token->input[0]) == 1)
		{
			if (check_output_red(*token, 0) > 2
				|| check_input_red(*token, 0) >= 3)
				return (0);
			else if (!token->next || get_char_type(token->next->input[0]))
				if (!check_next_token(*token, token->next))
					return (0);
		}
		if (is_double_pipe(token))
			return (0);
		token = token->next;
	}
	return (1);
}
