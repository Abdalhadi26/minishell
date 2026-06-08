/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:20 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/07 17:53:07 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

static void	execute_builtin_single(t_command *cmds, t_single_command command,
		t_shell *shell)
{
	int	stdin_fd;
	int	stdout_fd;

	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	if (stdin_fd < 0 || stdout_fd < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return ;
	}
	apply_redirections(command);
	if (!ft_strncmp(command.args[0], "exit", 5))
	{
		dup2(stdin_fd, STDIN_FILENO);
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdin_fd);
		close(stdout_fd);
	}
	shell->exit_status = execute_builtin(cmds, command, shell);
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
	return ;
}

static void	execute_child_single(t_command *cmds, t_single_command command, t_shell *shell)
{
	char	*path;

	path = find_path(command.args[0], shell);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, command.args[0], ft_strlen(command.args[0]));
		write(2, ": command not found\n", 20);
		free_cmds_shell(cmds, shell);
			close(0);
			close(1);
			close(2);
		exit(127);
	}
	apply_redirections(command);
	execve(path, command.args, shell->env);
	perror("minishell");
	free_cmds_shell(cmds, shell);
		close(0);
		close(1);
		close(2);
	exit(126);
}

static void	handle_wait_status(int status, t_shell *shell)
{
	if (wait_exit_state(status) == 0)
		shell->exit_status = wait_exit_code(status);
	else
	{
		if (wait_exit_state(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (wait_exit_state(status) == SIGINT)
			ft_putstr_fd("\n", 2);
		shell->exit_status = 128 + wait_exit_state(status);
	}
}

static	int	handle_no_args_n_bulitins(t_command *cmds, t_single_command command,
		t_shell *shell)
{
	int		stdin_fd;
	int		stdout_fd;

	if (!command.args)
	{
		stdin_fd = dup(STDIN_FILENO);
		stdout_fd = dup(STDOUT_FILENO);
		if (stdin_fd < 0 || stdout_fd < 0)
		{
			perror("minishell");
			shell->exit_status = 1;
			return (1);
		}
		apply_redirections(command);
		shell->exit_status = 0;
		dup2(stdin_fd, STDIN_FILENO);
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdin_fd);
		close(stdout_fd);
	}
	else if (is_builtin(command.args[0]))
		execute_builtin_single(cmds, command, shell);
	else
		return (0);
	return (1);
}

void	execute_single(t_command *cmds, t_single_command command,
		t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (handle_no_args_n_bulitins(cmds, command, shell))
		return ;
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
		execute_child_single(cmds, command, shell);
	}
	set_execution_signals_parent();
	waitpid(pid, &status, 0);
	handle_wait_status(status, shell);
}
