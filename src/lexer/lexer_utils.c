/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 21:13:47 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/10 10:05:25 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_lexer	*new_operator_token(char *line, char operator, int *i)
{
	t_lexer	*token;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (line[*i + len] == operator)
		len++;
	token = init_lexer(len);
	if (!token)
		return (NULL);
	while (j < len)
	{
		token->input[j] = line[*i];
		(*i)++;
		j++;
	}
	token->input[j] = '\0';
	(*i)--;
	return (token);
}

t_lexer	*init_lexer(int len)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (lexer == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	lexer->input = malloc(len + 1);
	lexer->input[0] = '\0';
	if (!lexer->input)
	{
		free(lexer);
		return (NULL);
	}
	lexer->next = NULL;
	lexer->qouted = 0;
	return (lexer);
}

char	*clean_lexer(t_lexer *head)
{
	t_lexer	*temp;

	if (!head)
		return (NULL);
	while (head)
	{
		temp = head;
		head = head->next;
		temp->next = NULL;
		free(temp->input);
		free(temp);
	}
	head = NULL;
	return (NULL);
}

int	get_char_type(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '|')
		return (2);
	else if (c == ' ' || (c >= 9 && c <= 13))
		return (3);
	else if (c == '\n' || c == '\0')
		return (4);
	else if (c == '\"' || c == '\'')
		return (5);
	return (0);
}

void	skip_spaces(char *line, int *i)
{
	if (!line || !line[*i] || get_char_type(line[*i + 1]) != 4)
		return ;
	while (get_char_type(line[*i + 1]) != 4 && get_char_type(line[*i]) == 3
		&& get_char_type(line[*i + 1]) == 3)
		(*i)++;
}
