/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:25:46 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/05 22:25:47 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../lexer/lexer.h"
#include "expander.h"
#include <stdio.h>

int	free_var(char **var, int i)
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

static int	free_data(t_data *data)
{
	if (!data)
		return (0);
	if (data->expanded)
		free(data->expanded);
	if (data->spaces)
		free(data->spaces);
	free(data);
	return (1);
}

static t_data	*init_data(char *input, char *expanded, t_shell shell)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	data->input = input;
	data->expanded = expanded;
	data->index[0] = 0;
	data->index[1] = 0;
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
	free_all(tokens);
	return (1);
}

int	main_expander(char *expanded, t_shell shell, t_lexer **tok)
{
	t_data	*data;
	t_lexer	*tokens;

	data = init_data((*tok)->input, expanded, shell);
	if (!data)
		return (0);
	if (!lol(data))
		return (0);
	if (data->spaces == NULL)
	{
		free((*tok)->input);
		(*tok)->input = ft_strdup(expanded);
		return (free_data(data));
	}
	tokens = makesplit(data->expanded, data->spaces);
	if (!tokens)
		return (0);
	if (!move_tokens(tok, tokens))
		return (0);
	free_data(data);
	return (0);
}
