/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:44 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/19 12:30:45 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int wait_exit_code(int status) //"W Exit Status" — what was the exit code?
{
	int exit_code;

	exit_code = ((status >> 8) & 0xff);
	return (exit_code);
}

int wait_exit_state(int status) //if killed by signal return the signal if not return 0
{
	if ((status & 0x7f) == 0)
		return (0);
	else
		return (status & 0x7f);
}
