/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:13 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/19 12:30:14 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** export.c
**
** Implements the export builtin.
** export adds new variables to the environment or updates existing ones.
**
** Two ways to use export:
**
**   export VARNAME=value
**     Adds VARNAME to the environment with the given value.
**     If VARNAME already exists, its value is updated.
**     Example: export MY_NAME=student
**
**   export with no arguments
**     Prints all currently exported environment variables in a format
**     that matches bash: declare -x VARNAME="value"
**
** Validation rules:
**   Variable names must be valid identifiers.
**   A valid identifier starts with a letter or underscore,
**   followed by any combination of letters, digits, and underscores.
**   export 1test  <- INVALID, starts with a digit
**   export _test  <- valid
**   export test1  <- valid
**   When an invalid name is given, print an error but continue
**   processing the remaining arguments.
**
** Why must export be a builtin?
**   Same reason as cd - it needs to modify the shells own environment.
**   If it ran in a child process, the changes would disappear when
**   the child exited and the shell would be unchanged.
**
** Think of export as the builtin that writes new entries into the
** shells environment dictionary.
*/
#include "../../includes/minishell.h"

static int is_valid_arg(char *key)
{
	int	i;

	if (!key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_env_entry(char *entry)
{
	char	*equal_sign;

	equal_sign = ft_strchr(entry, '=');
	if (equal_sign)
	{
		ft_putstr_fd("declare -x ", 1);
		write(1, entry, equal_sign - entry);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(equal_sign + 1, 1);
		ft_putstr_fd("\"\n", 1);
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(entry, 1);
		write(1, "\n", 1);
	}
}

static void	export_no_args(t_shell shell)
{
	int	done[4096];
	int	min_idx;
	int	printed;
	int	j;

	ft_memset(done, 0, sizeof(done));
	printed = 0;
	while (shell.env[printed])
	{
		min_idx = -1;
		j = 0;
		while (shell.env[j])
		{
			if (!done[j] && (min_idx == -1
				|| ft_strncmp(shell.env[j], shell.env[min_idx], INT_MAX) < 0))
				min_idx = j;
			j++;
		}
		print_env_entry(shell.env[min_idx]);
		done[min_idx] = 1;
		printed++;
	}
}

int	builtin_export(t_single_command	cmd,t_shell *shell)
{
	int			i;
	int			retrun_status;
	char	*equal_sign;
	char	*key;
	char	*value;

	if (cmd.num_args == 1)
	{
		export_no_args(*shell);
		return (0);
	}
	retrun_status = 0;
	i = 1;
	while (cmd.args[i])
	{
		equal_sign = ft_strchr(cmd.args[i], '=');
		if (equal_sign)
		{
			key = ft_substr(cmd.args[i], 0, equal_sign - cmd.args[i]);
			if (!key)
				return (1);
			value = equal_sign + 1;
		}
		else
		{
			key = cmd.args[i];
			value = NULL;
		}
		if (!is_valid_arg(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			retrun_status = 1;
		}
		else
			env_set(&shell->env, key, value);
		if (equal_sign)
			free(key);
		i++;
	}
	return (retrun_status);
}
