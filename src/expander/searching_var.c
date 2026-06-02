/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 03:12:41 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/02 03:21:29 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"



static int skip_var(char *src, t_shell shell, int *i, int *j)
{
	int start;
	char *var[2];

	start = 0;
	if (src[*i] && src[*i] == '$')
	{
		start = ++(*i);
		while (src[*i] && (ft_isalnum(src[*i]) 
			|| src[*i] == '_' || src[*i] == '?'))
			(*i)++;
		var[0] = ft_substr(src, start, *i - start);
		if (!var[0])
			return (0);
		if (src[*i - 1] != '?')
			var[1] = get_env_value(var[0], shell.env);
		else
			var[1] = ft_itoa(shell.exit_status);
		if (!var[1])
			return (free_var(var, 0));
		(*j) += ft_strlen(var[1]) -1;
		(*i)--;
		free_var(var, 2);
	}
	return (1);
}

static int check_var(t_data *data, int*i, int*j)
{
	char	c;

	if (!data ||!data->expanded || !data->input)
		return (0);
	c = data->input[*i];
	(*i)++;
	while(data->input[*i] && data->input[*i] != c 
		&& data->expanded[*j])
	{
		if (data->input[*i] == '$')
		{
			if (skip_var(data->input, data->shell, i, j) == 0)
				return(0);
		}
		(*i)++;
		(*j)++;
	}
	if (data->input[*i] == c)
		(*i)++;
	return (1);
}

int index_of_var(t_data *data, int*i,int *j)
{
	if (!data || !data->expanded || !data->input)
		return (0);
	while(data->input[*i] && data->expanded[*j])
	{
		if (data->input[*i] == '\'' || data->input[*i] == '\"')
		{
			if (!check_var(data, i, j))
				return (0);
		}
		else if (data->input[*i] &&  data->input[*i] == '$')
			return (1);
		else
		{
			(*i)++;
			(*j)++;
		}
	}
	return (-1);
}
