/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 02:11:29 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/02 02:11:36 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
/* Safely appends a single character to an allocated string and frees the old one */

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
        {return (NULL);}
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



/* Looks up "VAR=" in the env array and returns an allocated copy of the value */
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
	return (ft_strdup("")); // Not found, return empty string
}

char	*expand_string(char *str, t_shell shell, int flag)
{
	char	*res;
	int		i;
	int		sq;
	int		dq;

	res = ft_calloc(1, 1);
	i = 0;
	sq = 0;
	dq = 0;
	while (str && str[i] && res)
	{
		if (handle_quotes(str[i], &sq, &dq) && flag != -1) 
			i++;
		else if (str[i] == '$' && (!sq) && flag != 1)
			res = handle_dollar(res, str, shell, &i);
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

int has_var(t_lexer *token, int flag)
{
    int i;

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
			printf("hi");
            (token)->qouted = 3;
            return (1);
        }
        i++;
    }
    return (0);
}

/* Main entry point: Iterates through the lexer list and expands every token */
t_lexer *expand_lexer_tokens(t_lexer *lexer, t_shell shell)
{
	t_lexer	*curr;
	char	*expanded;
	int flag;

	curr = lexer;
	flag = 0;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->input, "<<", 2) == 0 && !curr->qouted)
			flag = 1;
        has_var(curr, flag);
		if (curr->input && curr->qouted)
		{
			expanded = expand_string(curr->input, shell, flag);
            if (!expanded)
                return (NULL);
			main_expander(expanded, shell, &curr);
			flag = 0;
		}
		curr = curr->next;
	}
    return (lexer);
}
