/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 03:12:41 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/06 18:22:22 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static int	skip_var(char *src, t_shell shell, int *i, int *j)
{
	int		start;
	char	*var[2];

	start = 0;
	if (src[*i] && src[*i] == '$')
	{
		start = ++(*i);
		while (src[*i] && (ft_isalnum(src[*i]) || src[*i] == '_'
				|| src[*i] == '?'))
			(*i)++;
		var[0] = ft_substr(src, start, *i - start);
		if (!var[0])
			return (0);
		if (src[*i - 1] != '?')
			var[1] = get_env_value(var[0], shell.env);
		else
			var[1] = ft_itoa(shell.exit_status);
		if (!var[1])
			return (clean_var(var, 0));
		(*j) += ft_strlen(var[1]) - 1;
		(*i)--;
		clean_var(var, 2);
	}
	return (1);
}

static int	check_var(t_expander_data *data, int *i_line, int *i_expanded)
{
	char	c;

	if (!data || !data->expanded || !data->line)
		return (0);
	c = data->line[*i_line];
	(*i_line)++;
	while (data->line[*i_line] && data->line[*i_line] != c
			&& data->expanded[*i_expanded])
	{
		if (data->line[*i_line] == '$')
		{
			if (skip_var(data->line, data->shell, i_line, i_expanded) == 0)
				return (0);
		}
		(*i_line)++;
		(*i_expanded)++;
	}
	if (data->line[*i_line] == c)
		(*i_line)++;
	return (1);
}

int	index_of_var(t_expander_data *data, int *i_line, int *i_expanded)
{
	if (!data || !data->expanded || !data->line)
		return (0);
	while (data->line[*i_line] && data->expanded[*i_expanded])
	{
		if (data->line[*i_line] == '\'' || data->line[*i_line] == '\"')
		{
			if (!check_var(data, i_line, i_expanded))
				return (0);
		}
		else if (data->line[*i_line] && data->line[*i_line] == '$')
			return (1);
		else
		{
			(*i_line)++;
			(*i_expanded)++;
		}
	}
	return (-1);
}
