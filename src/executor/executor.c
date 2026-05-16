/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:20 by aayasrah          #+#    #+#             */
/*   Updated: 2026/04/19 14:06:21 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** executor.c
**
** The executor is the final and most complex stage. It receives the
** fully parsed and expanded command list and actually runs everything.
**
** This is where the real Unix system programming happens.
**
** What the executor does:
**
**   For a single command (no pipes):
**     1. Check if it is a builtin (echo, cd, pwd, etc.)
**        If yes, run it directly in the current process
**        If no, fork a child process and use execve() to run it
**
**   For a pipeline (multiple commands connected by |):
**     1. Create pipes between each pair of adjacent commands
**     2. Fork a child process for each command
**     3. In each child, connect the right pipe ends to stdin/stdout
**     4. Close all pipe ends that the child doesnt need
**     5. Execute the command with execve()
**     6. In the parent, close all pipe ends and wait for all children
**
** Key concepts used here:
**   fork()   - creates a copy of the current process
**   execve() - replaces the current process with a new program
**   wait()   - parent waits for child to finish and gets exit status
**
** Think of the executor as a manager who receives a list of tasks,
** hires workers (child processes) to do each task, sets up the
** communication channels between them (pipes), and waits for
** everyone to finish before reporting back.
*/
#include "../../includes/minishell.h"

void	execute_single(t_single_command	command, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		stdin_fd;
	int		stdout_fd;
	char	*path;

	if (is_builtin(command.args[0]))
	{
		stdin_fd = dup(STDIN_FILENO);
		stdout_fd = dup(STDOUT_FILENO);
		if (stdin_fd < 0 || stdout_fd < 0)
		{
		    perror("minishell");
		    shell->exit_status = 1;
		    return ;
		}
		apply_redirections(command);
		shell->exit_status = execute_builtin(&command, shell);
		dup2(stdin_fd, STDIN_FILENO);
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdin_fd);
		close(stdout_fd);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		//error handling
	}
	if (pid == 0)
	{
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
	waitpid(pid, &status, 0);
}

char    *find_path(char *cmd, t_shell *shell)
{
	char **paths;
	char *to_test_path;
	char *temp;
	int i;

	paths = ft_split(env_get(shell->env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin("/", cmd);
		to_test_path = ft_strjoin(paths[i], temp);
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
	return(NULL);
}
