/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:38 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/07 16:41:25 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

static void	execute_child_pipeline(t_command *command, t_shell *shell,
		int **pipes, int i)
{
	char	*path;
	int temp;

	temp = 0;
	set_execution_signals_child();
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < (command->num_single_commands - 1))
		dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, command->num_single_commands - 1);
	apply_redirections(*(command->commands[i]));
	if (is_builtin(command->commands[i]->args[0]))
	{
		temp = execute_builtin(command, *(command->commands[i]), shell);
			close(0);
			close(1);
			close(2);
		exit(temp);
	}
	path = find_path(command->commands[i]->args[0], shell);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->commands[i]->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_pipes(pipes, command->num_single_commands - 1);
		free_cmds_shell(command, shell);
			close(0);
			close(1);
			close(2);
		//free_cmds(command);
		//free_2d(shell->env);
		//free(shell);
		exit(127);
	}
	execve(path, command->commands[i]->args, shell->env);
	perror("minishell");
	//herer
	free_pipes(pipes, command->num_single_commands - 1);
	free_cmds_shell(command, shell);
		close(0);
		close(1);
		close(2);
	//free_cmds(command);
	//free_2d(shell->env);
	//free(shell);
	exit(126);
}

static void	wait_pipeline(t_command command, t_shell *shell, int pid,
		int **pipes)
{
	int	last_pid;
	int	status;
	int	waitpid_return;

	last_pid = pid;
	waitpid_return = 0;
	while (1)
	{
		waitpid_return = waitpid(-1, &status, 0);
		if (waitpid_return <= 0)
			break ;
		if (waitpid_return == last_pid)
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
	}
	free_pipes(pipes, command.num_single_commands - 1);
}

static void	handle_fork_fail(t_command command, t_shell *shell, int **pipes)
{
	close_all_pipes(pipes, command.num_single_commands - 1);
	perror("minishell");
	shell->exit_status = 1;
	while (waitpid(-1, NULL, 0) > 0)
		;
	free_pipes(pipes, command.num_single_commands - 1);
}

void	execute_pipeline(t_command *command, t_shell *shell)
{
	int	i;
	int	pid;
	int	**pipes;

	if (create_pipes(*command, &pipes))
	{
		shell->exit_status = 1;
		return ;
	}
	i = 0;
	while (i < command->num_single_commands)
	{
		pid = fork();
		if (pid < 0)
		{
			handle_fork_fail(*command, shell, pipes);
			return ;
		}
		if (pid == 0)
			execute_child_pipeline(command, shell, pipes, i);
		i++;
	}
	set_execution_signals_parent();
	close_all_pipes(pipes, command->num_single_commands - 1);
	wait_pipeline(*command, shell, pid, pipes);
}
