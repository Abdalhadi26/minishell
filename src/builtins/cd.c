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

/*
** cd.c
**
** Implements the cd (change directory) builtin.
** cd changes the current working directory of the shell.
**
** Why MUST cd be a builtin and not an external program?
**   This is a fundamental Unix concept worth understanding deeply.
**   Every process has its own current directory. If cd were an
**   external program, it would fork a child process, change the
**   directory in THAT child process, and then the child would exit.
**   The parent shell process would be completely unaffected.
**   cd MUST run inside the shell process itself to actually change
**   the shells working directory. This is true of all builtins that
**   need to affect the shells own state.
**
** What cd does:
**   1. Calls chdir() to actually change the directory
**   2. Updates the PWD environment variable to the new directory
**   3. Updates the OLDPWD environment variable to the previous directory
**      (this is what lets you do cd - to go back)
**
** Error cases to handle:
**   cd with no path: go to $HOME
**   cd with too many arguments: error message, exit status 1
**   cd to a non-existent directory: error message, exit status 1
**   cd to a directory without permission: error message, exit status 1
**
** Think of cd as the builtin that moves the shell itself around
** the filesystem, rather than running a separate program to do it.
*/
#include "../../includes/minishell.h"

int	builtin_cd(t_single_command	cmd,t_shell *shell)
{
	char	*target_path;
	char	*old_pwd;
	char	*new_pwd;

	target_path = NULL;
	if (cmd.num_args > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!cmd.args[1])
	{
		target_path = env_get(shell->env, "HOME");
		if (!target_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n" ,2);
			return (1);
		}
	}
	else
		target_path = cmd.args[1];
	old_pwd = env_get(shell->env, "PWD");
	if (old_pwd)
		old_pwd = ft_strdup(old_pwd);
	if(chdir(target_path) == -1)
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
