/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 02:11:29 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/06 18:21:28 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*append_char(char *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

char	*get_env_value(char *var_name, char **env)
{
	int	i;
	int	len;

	if (!env || !var_name)
		return (ft_strdup(""));
	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_variables(char *str, t_shell shell, int flag)
{
	char	*res;
	int		i;
	int		single_qoute;
	int		douple_qoute;

	res = ft_calloc(1, 1);
	i = 0;
	single_qoute = 0;
	douple_qoute = 0;
	while (str && str[i] && res)
	{
		if (flag != -1 && handle_quotes(str[i], &single_qoute, &douple_qoute))
			i++;
		else if (str[i] == '$' && (!single_qoute) && flag != 1)
			res = handle_dollar(res, str, shell, &i);
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

int	has_variable(t_lexer *token, int flag)
{
	int	i;

	if (!(token) && !((token)->input))
		return (0);
	i = 0;
	while ((token)->input[i])
	{
		if ((token)->input[i] == '\'')
			token->qouted = 1;
		else if ((token)->input[i] == '\"')
			token->qouted = 2;
		else if ((token)->input[i] == '$' && flag != 1)
		{
			(token)->qouted = 3;
			return (1);
		}
		i++;
	}
	return (0);
}

/* Main entry point: Iterates through the lexer list and expands every token */
t_lexer	*expand_tokens(t_lexer *head, t_shell shell)
{
	t_lexer	*token;
	char	*expanded;
	int		flag;

	token = head;
	flag = 0;
	while (token != NULL)
	{
		if (ft_strncmp(token->input, "<<", 2) == 0 && !token->qouted)
			flag = 1;
		has_variable(token, flag);
		if (token->input && token->qouted)
		{
			expanded = expand_variables(token->input, shell, flag);
			if (!expanded)
				return (NULL);
			if (!split_after_expansion(expanded, shell, &token))
				return ((t_lexer *)clean_lexer(token));
			flag = 0;
		}
		token = token->next;
	}
	return (head);
}
