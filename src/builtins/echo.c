/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:04 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/28 14:10:17 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_a_flag(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[i] == '-')
		i++;
	else
		return (0);
	if (!arg[i])
		return (0);
	while (arg[i] == 'n')
		i++;
	if (!arg[i])
		return (1);
	return (0);
}

int	builtin_echo(t_single_command cmd)
{
	int	i;
	int	flag_status;

	flag_status = 0;
	i = 1;
	while (is_a_flag(cmd.args[i]))
	{
		flag_status = 1;
		i++;
	}
	while (cmd.args[i])
	{
		ft_putstr_fd(cmd.args[i], 1);
		if (cmd.args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag_status)
		write(1, "\n", 1);
	return (0);
}
