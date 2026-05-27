/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:29:59 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/19 12:30:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_target_path_old_pwd(char **target_path, char **old_pwd,
		t_single_command cmd, t_shell *shell)
{
	*target_path = NULL;
	if (cmd.num_args > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!cmd.args[1])
	{
		*target_path = env_get(shell->env, "HOME");
		if (!*target_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		*target_path = cmd.args[1];
	*old_pwd = env_get(shell->env, "PWD");
	if (*old_pwd)
		*old_pwd = ft_strdup(*old_pwd);
	return (0);
}

int	builtin_cd(t_single_command cmd, t_shell *shell)
{
	char	*target_path;
	char	*old_pwd;
	char	*new_pwd;

	if (set_target_path_old_pwd(&target_path, &old_pwd, cmd, shell))
		return (1);
	if (chdir(target_path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	else
	{
		env_set(&shell->env, "OLDPWD", old_pwd);
		free(old_pwd);
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
		{
			perror("minishell: cd");
			return (1);
		}
		env_set(&shell->env, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}
