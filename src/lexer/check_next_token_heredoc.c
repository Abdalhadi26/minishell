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

static int	s_token_check_o_paa(t_lexer token)
{
	if (check_output_redaa(token))
		return (1);
	else if (check_red_pipe(token.input[0]) == 2)
	{
		return (1);
	}
	return (0);
}

static int	s_token_check_i_paa(t_lexer token)
{
	if (check_input_redaa(token))
		return (1);
	else if (check_red_pipe(token.input[0]) == 2)
	{
		return (1);
	}
	return (0);
}

int	check_output_redaa(t_lexer token)
{
	int	i;

	i = 0;
	while (token.input[i] && token.input[i] == '>')
		i++;
	return (i);
}

int	check_input_redaa(t_lexer token)
{
	int	i;

	i = 0;
	while (token.input[i] && token.input[i] == '<')
		i++;
	return (i);
}



int	check_next_tokenaa(t_lexer f_token, t_lexer *s_token,t_redirections **here)
{
	if (!s_token)
		return (2);
	if (s_token_check_o_paa(*s_token) && !s_token->qouted)
			return (0);
	else if (s_token_check_i_paa(*s_token) && !s_token->qouted)
			return (0);
	else if (check_input_redaa(f_token) == 2)
	{
		if (!link_red(here,(t_redirections *)init_red(3, s_token)))
		{
			free_redirections(*here);
			*here = NULL;
			return (0);
		}
	}
	else if (!s_token->qouted && check_output_redaa(f_token))
	{
		if (s_token_check_i_paa(*s_token) || s_token_check_o_paa(*s_token))
			return (0);
	}
	return (4);
}
