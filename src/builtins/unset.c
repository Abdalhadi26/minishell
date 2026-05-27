/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:20 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/19 12:30:21 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(t_single_command cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd.args[i])
	{
		env_unset(&shell->env, cmd.args[i]);
		i++;
	}
	return (0);
}
