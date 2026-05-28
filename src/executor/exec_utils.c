/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:30 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/28 14:13:20 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	free_pipes(int **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	create_pipes(t_command command, int ***pipes)
{
	int	i;

	*pipes = malloc((command.num_single_commands - 1) * sizeof(int *));
	if (!*pipes)
		return (1);
	i = 0;
	while (i < (command.num_single_commands - 1))
	{
		(*pipes)[i] = malloc(2 * sizeof(int));
		if (!(*pipes)[i])
		{
			close_all_pipes(*pipes, i);
			return (1);
		}
		if (pipe((*pipes)[i]) < 0)
		{
			close_all_pipes(*pipes, i + 1);
			perror("minishell");
			return (1);
		}
		i++;
	}
	return (0);
}
