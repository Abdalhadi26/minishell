/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:07:01 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/05 22:35:24 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/lexer/lexer.h"
#include "../src/parser/parsing.h"

int	number_of_cmds(t_lexer *token)
{
	t_lexer	*tok;
	int		num_cmds;

	if (!token)
		return (0);
	tok = token;
	num_cmds = 1;
	while (tok)
	{
		if (tok->input[0] == '|' && !tok->qouted)
			num_cmds++;
		tok = tok->next;
	}
	return (num_cmds);
}

t_command	*main_parsing(char *input, t_shell shell)
{
	t_lexer		*tokens;
	t_command	*cmds;

	tokens = add_tokens(input, 0, 0);
	if (!tokens)
		return (NULL);
	if (pipe_red_dup(tokens))
		return (free_all(tokens), NULL);
	tokens = expand_lexer_tokens(tokens, shell);
	if (!tokens)
		return (NULL);
	cmds = NULL;
	cmds = parsing(tokens, number_of_cmds(tokens));
	free_all(tokens);
	tokens = NULL;
	return (cmds);
}
