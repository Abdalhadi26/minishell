/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_spliting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 03:19:57 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/02 03:27:23 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"


static t_lexer *create_token(char *str, int *i, int j)
{
	t_lexer *token;
	int k;

	k = 0;
	token = init_s_lexer(j - *i);
	if (!token)
		return (NULL);
	while(*i < j)
	{
		token->input[k] = str[*i];
		k++;
		(*i)++;
		token->input[k] = '\0';
	}
	token->qouted = 2;
	(*i)++;
	return (token);
}

static t_lexer *set_all_values(char *dest, int *spaces, int i, t_lexer *token)
{
	t_lexer *tok;
	int j;

	tok = token;
	j = 0;
	while(spaces && spaces[j])
	{
		token->next = create_token(dest, &i, spaces[j]);
		if (!token->next)
			return (NULL);
		j++;
		token = token->next; 
	}
	if (dest[i])
	{
		if (!token)
			 return (create_token(dest, &i, ft_strlen(dest)));
		else 
			token->next = create_token(dest, &i, ft_strlen(dest));
		if (!token->next)
			return ((t_lexer *)free_all(token));
	}
	return (tok);
}

t_lexer *makesplit(char *dest, int *spaces)
{
	int	i;
	int j;
	t_lexer *token;

	i = 0;
	j = 1;
	token = create_token(dest, &i, spaces[0]);
	if (!token)
		return (NULL);
	if (spaces[j])
	{
		token->next = create_token(dest, &i, spaces[1]);
		if (!token->next)
			return ((t_lexer *)free_all(token));
		j++;
	}
	if (dest[i])
	{
		token->next = set_all_values(dest, spaces + j, i, token->next);
		if (!token->next)
			return ((t_lexer *)free_all(token));
	}
	return (token);
}