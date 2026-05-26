

#include "../../includes/minishell.h"

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
    // if ()
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup("")); // Not found, return empty string
}

/* Handles the "$?" expansion */
char	*handle_exit_status(char *res, t_shell shell, int *i)
{
	char	*status_str;
	char	*temp;

	status_str = ft_itoa(shell.exit_status);
	if (!status_str)
        return (NULL);
    temp = ft_strjoin(res, status_str);
    if (!temp)
		{return (NULL);}
	free(status_str);
	(*i) += 2;
	return (temp);
}

/* Handles standard "$VAR" expansion */
char	*handle_env_var(char *res, char *str, t_shell shell, int *i)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*temp;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	var_value = get_env_value(var_name, shell.env);
	
	temp = ft_strjoin(res, var_value);
	
	free(var_name);
	free(var_value);
	return (temp);
}


int	handle_quotes(char c, int *sq, int *dq)
{
	if (c == '\'' && !(*dq))
	{
		*sq = !(*sq);
		return (1);
	}
	if (c == '\"' && !(*sq))
	{
		*dq = !(*dq);
		return (1);
	}
	return (0);
}
char	*handle_digit(char *res, char *str, int *i)
{
	char	*temp;

    if (str[*i + 1] == '0')
		temp = ft_strjoin(res, "Bash");
	else
		temp = ft_strjoin(res, "");
    if (!temp)
        {return (NULL);}
	(*i) += 2; // Skip over the "$?"
	return (temp);
}

char	*handle_dollar(char *res, char *str, t_shell shell, int *i)
{
	if (str[*i + 1] == '?')
		res = handle_exit_status(res, shell, i);
	else if (ft_isdigit(str[*i + 1]))
	    res = handle_digit(res, str, i);
	else if (str[*i + 1] && (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_'))
		res = handle_env_var(res, str, shell, i);
	else
	{
		res = append_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*expand_string(char *str, t_shell shell)
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
		if (handle_quotes(str[i], &sq, &dq))
			i++;
		else if (str[i] == '$' && !sq)
			res = handle_dollar(res, str, shell, &i);
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

int has_var(t_lexer *token)
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
        else if ((token)->input[i] == '$')
        {
            (token)->qouted = 2;
            return (1);
        }
        i++;
    }
    return (0);
}
// int make_split(t_lexer *token, char *str)
// {
//     t_lexer *new_token;
//     t_lexer *next_token;
//     char **tokens;
//     int i;

//     i = 0;
//     next_token = token->next;
//     tokens = ft_split(str, ' ');
//     while(tokens[i])
//     {
//         new_token = init_s_lexer(ft_strlen(tokens[i]));
//         if (!new_token)
//             return (0);
//         new_token->input = ft_strdup(tokens[i]);
//         // tokens[i] = NULL; // Mark as used
//         new_token->qouted = 0;
//         token ->next = new_token;
//         token = new_token;
//         i++;
//     }
//     free(str);
//     return (0);
// }
/* Main entry point: Iterates through the lexer list and expands every token */
t_lexer	*expand_lexer_tokens(t_lexer *lexer, t_shell shell)
{
	t_lexer	*curr;
	char	*expanded;

	curr = lexer;
	while (curr != NULL)
	{
        has_var(curr);
		if (curr->input && curr->qouted)
		{
			expanded = expand_string(curr->input, shell);
            if (!expanded)
                return (NULL);
			free(curr->input);      // Free the raw, unexpanded token
            // make_split(curr, expanded);
			curr->input = expanded; // Replace with the quote-stripped, expanded token
		}
		curr = curr->next;
	}
    return (lexer);
}
