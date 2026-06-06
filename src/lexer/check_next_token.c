/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_next_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 21:00:49 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/06 18:14:25 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	s_token_check_o_p(t_lexer token)
{
	if (check_output_red(token, 2))
		return (1);
	else if (check_red_pipe(token.input[0]) == 2)
	{
		print_error("|4");
		return (1);
	}
	return (0);
}

static int	s_token_check_i_p(t_lexer token)
{
	if (check_input_red(token, 3))
		return (1);
	else if (check_red_pipe(token.input[0]) == 2)
	{
		print_error("|3");
		return (1);
	}
	return (0);
}

int	check_output_red(t_lexer token, int is_next)
{
	int	i;

	i = 0;
	while (token.input[i] && token.input[i] == '>')
		i++;
	if ((i + is_next) == 3)
		print_error(">");
	else if ((i + is_next) > 3)
		print_error(token.input + (i - 2));
	return (i);
}

int	check_input_red(t_lexer token, int is_next)
{
	int	i;

	i = 0;
	while (token.input[i] && token.input[i] == '<')
		i++;
	if ((i + is_next) == 4)
		print_error("<");
	else if ((i + is_next) == 5)
		print_error(token.input + (i - 2));
	else if ((i + is_next) > 5)
		print_error(token.input + (i - 3));
	return (i);
}

int	check_next_token(t_lexer f_token, t_lexer *s_token)
{
	if (!s_token)
	{
		print_error("newline");
		return (1);
	}
	else if (!s_token->qouted && check_input_red(f_token, 0))
	{
		if (s_token_check_o_p(*s_token) || s_token_check_i_p(*s_token))
			return (1);
		else
			return (0);
	}
	else if (!s_token->qouted && check_output_red(f_token, 0))
	{
		if (s_token_check_i_p(*s_token) || s_token_check_o_p(*s_token))
			return (1);
		else
			return (0);
	}
	return (0);
}
