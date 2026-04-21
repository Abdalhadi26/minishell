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

void	execute_pipeline(t_command command)
{
	int		i;
	int		status;
	int		pid;
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
			path = find_path(command.commands[i]->args[0]);
			if (!path)
			{
				write(2, "minishell: ", 11);
        		write(2, command.commands[i]->args[0], ft_strlen(command.commands[i]->args[0]));
        		write(2, ": command not found\n", 20);
        		exit(127);
			}
			if (execv(path, command.commands[i]->args) == -1)
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
	while (waitpid(-1, &status, 0) > 0);
}

int	main(void)
{
	t_single_command	cmd1;
	t_single_command	cmd2;
	t_single_command	cmd3;
	t_single_command	*cmds[3];
	t_command			command;

	// ls | wc -l
	char	*args1[] = {"ls", NULL};
	char	*args2[] = {"grep", "src", NULL};
	char	*args3[] = {"wc", "-l", NULL};

	cmd1.args = args1;
	cmd1.num_args = 1;
	cmd1.redirections = NULL;

	cmd2.args = args2;
	cmd2.num_args = 2;
	cmd2.redirections = NULL;

	cmd3.args = args3;
	cmd3.num_args = 2;
	cmd3.redirections = NULL;

	cmds[0] = &cmd1;
	cmds[1] = &cmd2;
	cmds[2] = &cmd3;

	command.num_single_commands = 3;
	command.commands = cmds;

	execute_pipeline(command);
	return (0);
}
