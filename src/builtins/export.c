/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadi1 <hadi1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:30:13 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/27 16:21:08 by hadi1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			if (!done[j] && (min_idx == -1 || ft_strncmp(shell.env[j],
						shell.env[min_idx], INT_MAX) < 0))
				min_idx = j;
			j++;
		}
		print_env_entry(shell.env[min_idx]);
		done[min_idx] = 1;
		printed++;
	}
}

static int	set_key_value_export(char **key, char **value, char *arg,
		char **equal_sign)
{
	*equal_sign = ft_strchr(arg, '=');
	if (*equal_sign)
	{
		*key = ft_substr(arg, 0, *equal_sign - arg);
		if (!*key)
			return (1);
		*value = *equal_sign + 1;
	}
	else
	{
		*key = arg;
		*value = NULL;
	}
	return (0);
}

static int	add_var_export(char *key, char *value, t_shell *shell)
{
	if (!is_valid_arg(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else
		env_set(&shell->env, key, value);
	return (0);
}

int	builtin_export(t_single_command cmd, t_shell *shell)
{
	int		i;
	int		return_status;
	char	*equal_sign;
	char	*key;
	char	*value;

	if (cmd.num_args == 1)
	{
		export_no_args(*shell);
		return (0);
	}
	return_status = 0;
	i = 1;
	while (cmd.args[i])
	{
		if (set_key_value_export(&key, &value, cmd.args[i], &equal_sign))
			return (1);
		return_status = add_var_export(key, value, shell);
		if (equal_sign)
			free(key);
		i++;
	}
	return (return_status);
}
