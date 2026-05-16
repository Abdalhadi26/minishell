/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:38 by aayasrah          #+#    #+#             */
/*   Updated: 2026/04/19 14:06:39 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pipes.c
**
** This file handles the creation and management of Unix pipes.
** A pipe is a communication channel between two processes - one
** process writes into one end, another reads from the other end.
**
** What is a pipe in Unix?
**   When you run ls | grep foo, you want the OUTPUT of ls to become
**   the INPUT of grep. A pipe is how the operating system connects them.
**   The pipe() system call creates two file descriptors:
**     fd[0] - the read end  (grep reads from here)
**     fd[1] - the write end (ls writes to here)
**
** The most important and most commonly misunderstood rule about pipes:
**   You MUST close every pipe end that you dont use.
**   If the parent forgets to close the write end of a pipe, the child
**   reading from that pipe will NEVER receive EOF and will hang forever,
**   waiting for input that will never come. This is the most common bug
**   in minishell implementations.
**
** What this file handles:
**   - Creating the right number of pipes for a pipeline
**     (N commands need N-1 pipes)
**   - Connecting pipe ends to stdin and stdout using dup2()
**   - Closing all pipe ends that are no longer needed
**   - Making sure no file descriptors are leaked to child processes
**
** Think of pipes like a physical tube between two people. If you dont
** cap (close) the ends you are not using, air (data) leaks everywhere
** and nothing works correctly.
*/

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
			while (waitpid(-1, &status, 0) > 0);
			exit(1); //not perminiant, too lookup later
		}
	    if (pid == 0)
		{
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
			//free(path);
			//perror("minishell");
		}
	    i++;
	}
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
			if (WIFEXITED(status))
    			shell->exit_status = WEXITSTATUS(status);
			//for the future
			//else if (WIFSIGNALED(status))
    		//	shell->exit_status = 128 + WTERMSIG(status); 
		}
	}
}
