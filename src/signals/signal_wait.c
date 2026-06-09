/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:44 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/09 22:37:45 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_child_exit_code(int status)
{
	int	exit_code;

	exit_code = ((status >> 8) & 0xff);
	return (exit_code);
}

int	get_child_exit_signal(int status)
{
	if ((status & 0x7f) == 0)
		return (0);
	else
		return (status & 0x7f);
}

void	check_sigint_status(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		shell->exit_status = 130;
	}
}

void	set_execution_signals_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
