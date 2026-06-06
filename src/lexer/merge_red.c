/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:58:50 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/06 18:14:44 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	delete_token(t_lexer *token)
{
	t_lexer	*temp;

	temp = token->next;
	token->next = temp->next;
	temp->next = NULL;
	free(temp->input);
	free(temp);
}

t_lexer	*merge_red(t_lexer *head)
{
	t_lexer	*tok;

	if (!head)
		return (NULL);
	tok = head;
	while (tok && tok->next)
	{
		if (!tok->qouted && check_red_pipe(tok->input[0]) == 1)
		{
			if (tok->input[0] == tok->next->input[0] && !tok->next->qouted)
			{
				tok->input = ft_strjoin(tok->input, tok->next->input);
				if (!tok->input)
					return ((t_lexer *)free_all(head));
				delete_token(tok);
				continue ;
			}
		}
		tok = tok->next;
	}
	return (head);
}
