/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:10 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/28 14:09:57 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_cmds_shell(t_command *cmds, t_shell *shell)
{
	free_cmds(cmds);
	free_2d(shell->env);
	free(shell);
}
static long long	ft_atol(const char *str, int *overflow)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			*overflow = 1;
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

static int	is_valid_number(char *arg)
{
	int	i;
	int	overflow;

	overflow = 0;
	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	ft_atol(arg, &overflow);
	if (overflow)
		return (0);
	return (1);
}

static int	handle_exit_args(t_command *cmds, t_single_command *cmd, t_shell *shell)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd->num_args == 1)
	{
		rl_clear_history();
		free_cmds_shell(cmds, shell);
		exit(shell->exit_status);
	}
	else if (cmd->num_args > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	builtin_exit(t_command *cmds, t_single_command *cmd, t_shell *shell)
{
	long	result;
	int		dummy;

	if (handle_exit_args(cmd, shell))
		return (1);
	if (cmd->num_args == 2)
	{
		if (!is_valid_number(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_cmds_shell(cmds, shell);
			rl_clear_history();
			exit(2);
		}
		free_cmds_shell(cmds, shell);
		result = ft_atol(cmd->args[1], &dummy) % 256;
		if (result < 0)
			result += 256;
		rl_clear_history();
		exit(result);
	}
	return (0);
}
