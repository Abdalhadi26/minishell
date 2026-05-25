/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:10 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/19 17:59:10 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exit.c
**
** Implements the exit builtin.
** exit terminates the shell, optionally with a specific exit code.
**
** Usage:
**   exit        exits with the last commands exit status
**   exit 42     exits with code 42
**   exit -1     exits with code 255 (wraps around like bash)
**
** The exit code math:
**   Exit codes in Unix are stored as unsigned 8-bit values (0-255).
**   Any value you give is taken modulo 256.
**   So exit 256 exits with 0, exit 257 exits with 1, exit -1 exits with 255.
**
** Error cases to handle carefully:
**   exit abc        <- not a number, print error, exit with code 2
**   exit 1 2        <- too many arguments, print error, do NOT exit
**   exit 99999999999999999 <- overflow, print error, exit with code 2
**   The overflow check is important - use long long and check bounds.
**
** Why must exit be a builtin?
**   Because it needs to terminate the shell process itself. If it
**   ran in a child process, only the child would exit and the shell
**   would keep running unchanged.
**
** Important cleanup:
**   Before exiting, free ALL allocated memory - env list, any remaining
**   command structs, everything. Valgrind will check this.
**
** Think of exit as the off switch for the shell, with some careful
** math to handle the exit code correctly.
*/
#include "../../includes/minishell.h"

static long long ft_atol(const char *str, int *overflow)
{
	int				i;
	int				sign;
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

static int is_valid_number(char	*arg)
{
	int i;
	int overflow;

	overflow = 0;
	i = 0;
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

int	builtin_exit(t_single_command	cmd,t_shell *shell)
{
	long	result;
	int	dummy;

	ft_putstr_fd("exit\n", 2);
	if (cmd.num_args == 1)
	{
		rl_clear_history();
		exit(shell->exit_status);
	}
	else if (cmd.num_args > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (cmd.num_args == 2)
	{
		if (!is_valid_number(cmd.args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd.args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			//clean up
			rl_clear_history();
			exit(2);
		}
		//cleanup
		result = ft_atol(cmd.args[1], &dummy) % 256;
		if (result < 0)
    		result += 256;
		rl_clear_history();
		exit(result);
	}
	return (0);
}
