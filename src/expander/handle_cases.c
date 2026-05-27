/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 22:23:14 by ahhammad          #+#    #+#             */
/*   Updated: 2026/05/27 22:32:06 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "expander.h"

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
