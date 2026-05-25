/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:38 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/25 16:43:20 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void close_all_pipes(int pipes[][2], int num_pipes)
{
	int i;
	
	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	execute_pipeline(t_command command, t_shell *shell)
{
	int		i;
	int		status;
	int		pid;
	int		last_pid;
	int		waitpid_return;
	int		pipes[command.num_single_commands - 1][2];
	char	*path;

	i = 0;
	while (i < (command.num_single_commands - 1))
	{
		if (pipe(pipes[i]) < 0)
		{
			close_all_pipes(pipes, i + 1);
			perror("minishell");
			exit(127);
		}
		i++;
	}
	i = 0;
	while (i < command.num_single_commands)
	{
	    pid = fork();
		if (pid < 0)
		{
			close_all_pipes(pipes, command.num_single_commands - 1);
			perror("minishell");
			shell->exit_status = 1;
			while (waitpid(-1, &status, 0) > 0);
			return ;
		}
	    if (pid == 0)
		{
			set_execution_signals_child();
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < (command.num_single_commands - 1))
				dup2(pipes[i][1], STDOUT_FILENO);
			close_all_pipes(pipes, command.num_single_commands - 1);
			apply_redirections(*command.commands[i]);
    		if (is_builtin(command.commands[i]->args[0]))
    		    exit(execute_builtin(command.commands[i], shell));// check norm error, two on one line
			path = find_path(command.commands[i]->args[0], shell);
			if (!path)
			{
				write(2, "minishell: ", 11);
        		write(2, command.commands[i]->args[0], ft_strlen(command.commands[i]->args[0]));
        		write(2, ": command not found\n", 20);
        		exit(127);
			}
			if (execve(path, command.commands[i]->args, shell->env) == -1)
			{
				free(path);
				perror("minishell");
				exit(126);
			}
		}
	    i++;
	}
	set_execution_signals_parent();
	close_all_pipes(pipes, command.num_single_commands - 1);
	last_pid = pid;
	waitpid_return = 0;
	while (1)
	{
		waitpid_return = waitpid(-1, &status, 0);
		if (waitpid_return <= 0)
			break;
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
}
