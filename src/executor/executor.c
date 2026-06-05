/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:20 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/05 02:27:18 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_builtin_single(t_command *cmds, t_single_command command, t_shell *shell)
{
	int		stdin_fd;
	int		stdout_fd;

	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	if (stdin_fd < 0 || stdout_fd < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return ;
	}
	apply_redirections(command);
	shell->exit_status = execute_builtin(cmds, command, shell);
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
	return ;
}

static	void	execute_child_single(t_single_command command, t_shell *shell)
{
	char	*path;

	path = find_path(command.args[0], shell);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, command.args[0], ft_strlen(command.args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	apply_redirections(command);
	execve(path, command.args, shell->env);
	perror("minishell");
	exit(126);
}

static	void	handle_wait_status(int status, t_shell *shell)
{
	if (wait_exit_state(status) == 0)
		shell->exit_status = wait_exit_code(status);
	else
	{
		if (wait_exit_state(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		shell->exit_status = 128 + wait_exit_state(status);
	}
}

void	execute_single(t_command *cmds, t_single_command command, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (is_builtin(command.args[0]))
	{
		execute_builtin_single(cmds, command, shell);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		set_execution_signals_child();
		execute_child_single(command, shell);
	}
	set_execution_signals_parent();
	waitpid(pid, &status, 0);
	handle_wait_status(status, shell);
}

char	*find_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*to_test_path;
	char	*temp;
	int		i;

	if (strchr(cmd, '/'))
	{
		to_test_path = cmd;
		if (access(to_test_path, F_OK) == 0)
			return (to_test_path);
		else
			return (NULL);
	}
	paths = ft_split(env_get(shell->env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_ayasrah("/", cmd);
		to_test_path = ft_strjoin_ayasrah(paths[i], temp);
		free(temp);
		if (access(to_test_path, F_OK) == 0)
		{
			free_2d(paths);
			return (to_test_path);
		}
		else
			free(to_test_path);
		i++;
	}
	free_2d(paths);
	return (NULL);
}
