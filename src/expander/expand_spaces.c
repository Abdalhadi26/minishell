/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 02:55:59 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/05 22:24:57 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	ft_intlen(int *spaces)
{
	int	i;

	i = 0;
	if (!spaces)
		return (0);
	while (spaces[i])
		i++;
	return (i);
}

static int	*add_space(int *spaces, int j)
{
	int	*space;
	int	i;

	i = 0;
	if (!spaces)
	{
		space = malloc(2 * sizeof(int));
		if (!space)
			return (NULL);
	}
	else
	{
		space = malloc((ft_intlen(spaces) + 2) * sizeof(int));
		if (!space)
			return (NULL);
		while (spaces[i])
		{
			space[i] = spaces[i];
			i++;
		}
	}
	space[i] = j;
	space[i + 1] = '\0';
	free(spaces);
	return (space);
}

static int	has_spaces(char *dest, int *j, int len, int **spaces)
{
	int	k;

	k = *j;
	if (!dest)
		return (0);
	if (!dest[*j])
		return (1);
	while (dest[*j] && *j < (k + len))
	{
		if (dest[*j] == ' ')
		{
			*spaces = add_space(*spaces, *j);
			if (!(*spaces))
				return (0);
		}
		(*j)++;
	}
	return (1);
}

static int	counting_spaces(t_data *data, int *i, int *j)
{
	int		start;
	char	*var[2];

	start = ++(*i);
	while (data->input[*i] && (ft_isalnum(data->input[*i])
			|| data->input[*i] == '_'))
		(*i)++;
	var[0] = ft_substr(data->input, start, *i - start);
	if (!var[0])
		return (0);
	var[1] = get_env_value(var[0], data->shell.env);
	if (!var[1])
		return (free_var(var, 1));
	if (!has_spaces(data->expanded, j, ft_strlen(var[1]), &data->spaces))
		return (free_var(var, 2));
	free_var(var, 2);
	return (1);
}

int	lol(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	if (!data || !data->expanded || !data->input)
		return (0);
	while (data->input[i] && data->expanded[j])
	{
		k = index_of_var(data, &i, &j);
		if (k == 1)
		{
			if (!counting_spaces(data, &i, &j))
				return (0);
		}
		else if (k == 0)
			return (0);
	}
	if (data->spaces == NULL)
		return (1);
	return (1);
}
