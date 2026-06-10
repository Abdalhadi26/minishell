/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:47:03 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/08 17:52:12 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	lexer_append_token(t_lexer **head, t_lexer *token)
{
	t_lexer	*temp;

	if (!token && !token->input)
		return ;
	temp = *head;
	if (!(*head))
	{
		*head = token;
		return ;
	}
	while ((temp)->next)
	{
		(temp) = (temp)->next;
	}
	(temp)->next = token;
}

static t_lexer	*create_token(char *line, int len, int *i, int j)
{
	t_lexer	*current;
	int		k;

	k = 0;
	if (line[*i + 1] == '\0' && (get_char_type(line[*i]) == 0
			|| get_char_type(line[*i]) == 5))
	{
		(*i)++;
		len++;
	}
	current = init_lexer(len);
	if (!current)
		return (NULL);
	while (j < *i)
	{
		current->input[k] = line[j];
		j++;
		k++;
		current->input[k] = '\0';
	}
	if (line[*i] == '\0')
		(*i)--;
	return (current);
}

static int	new_token(t_lexer **head, char *line, int j, int *i)
{
	int		len;
	t_lexer	*current;
	t_lexer	*another_token;

	len = *i - j;
	if ((line[*i] == '\0' || get_char_type(line[*i]) == 3) && len == 0)
		return (1);
	if (len != 0)
	{
		current = create_token(line, len, i, j);
		if (!current)
			return (0);
		lexer_append_token(head, current);
		if (get_char_type(line[*i]) != 1 && get_char_type(line[*i]) != 2)
			return (1);
	}
	if (line[*i] && (get_char_type(line[*i]) == 1
			|| get_char_type(line[*i]) == 2 || line[*i + 1] == '\0'))
	{
		another_token = new_operator_token(line, line[*i], i);
		if (!another_token)
			return (0);
		lexer_append_token(head, another_token);
	}
	return (1);
}

static int	handle_quotes(t_lexer **head, char *line, int *i, int *j)
{
	char	c;
	int		x;

	x = 0;
	c = line[*i];
	(*i)++;
	while (line[*i])
	{
		if (c == line[*i])
		{
			if (line[*i + 1] == '\0')
			{
				x = new_token(head, line, (*j), (i));
				return (x);
			}
			return (1);
		}
		(*i)++;
	}
	return (0);
}

t_lexer	*add_tokens(char *line, int start, int end)
{
	t_lexer	*head;

	if (!line)
		return (NULL);
	head = NULL;
	while (get_char_type(line[start]) != 4)
	{
		if (get_char_type(line[start]) == 5)
		{
			if (!handle_quotes(&head, line, &start, &end))
				return ((t_lexer *)clean_lexer(head));
		}
		else if ((get_char_type(line[start])
				|| get_char_type(line[start + 1]) == 4))
		{
			if (!new_token(&head, line, end, &start))
				return ((t_lexer *)clean_lexer(head));
			skip_spaces(line, &start);
			end = start;
			if (get_char_type(line[start]) || !line[start + 1])
				end++;
		}
		start++;
	}
	return (head);
}
