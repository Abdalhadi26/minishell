/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:25:46 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/06 18:22:12 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

#include <stdio.h>

int	clean_var(char **var, int i)
{
	if (i == 0)
	{
		free(var[0]);
		var[0] = NULL;
	}
	else if (i == 1)
	{
		free(var[1]);
		var[1] = NULL;
	}
	else
	{
		free(var[0]);
		free(var[1]);
		var[0] = NULL;
		var[1] = NULL;
	}
	return (0);
}

static int	clean_data(t_expander_data *data)
{
	if (!data)
		return (0);
	if (data->expanded)
		free(data->expanded);
	if (data->spaces)
		free(data->spaces);
	free(data);
	data = NULL;
	return (0);
}

static t_expander_data	*init_expander_data(char *input, char *expanded, t_shell shell)
{
	t_expander_data	*data;

	data = (t_expander_data *)malloc(sizeof(t_expander_data));
	if (data == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	data->line = input;
	data->expanded = expanded;
	data->spaces = NULL;
	data->shell = shell;
	return (data);
}

static int	move_tokens(t_lexer **tok, t_lexer *tokens)
{
	t_lexer	*last_token;

	if (!tokens || !tok || !(*tok))
		return (0);
	last_token = tokens;
	while (last_token && last_token->next)
		last_token = last_token->next;
	if (last_token)
		last_token->next = (*tok)->next;
	free((*tok)->input);
	(*tok)->input = ft_strdup(tokens->input);
	if (!(*tok)->input)
		return (0);
	(*tok)->next = tokens->next;
	tokens->next = NULL;
	clean_lexer(tokens);
	return (1);
}

int	split_after_expansion(char *expanded, t_shell shell, t_lexer **tok)
{
	t_expander_data	*data;
	t_lexer	*tokens;

	data = init_expander_data((*tok)->input, expanded, shell);
	if (!data)
		return (0);
	if (!collect_spaces(data))
		return (clean_data(data));
	if (data->spaces == NULL)
	{
		free((*tok)->input);
		(*tok)->input = ft_strdup(expanded);
		clean_data(data);
		if (!(*tok)->input)
			return (0);
		return (1);
	}
	tokens = makesplit(data->expanded, data->spaces);
	clean_data(data);
	if (!tokens)
		return (0);
	if (!move_tokens(tok, tokens))
		return (0);
	return (1);
}
