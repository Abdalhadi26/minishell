/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:20 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/25 16:38:22 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_single(t_single_command command, t_shell *shell)
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
		perror("minishell");
		shell->exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		set_execution_signals_child();
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
	set_execution_signals_parent();
	waitpid(pid, &status, 0);
	if (wait_exit_state(status) == 0)
		shell->exit_status = wait_exit_code(status);
	else
	{
		if (wait_exit_state(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		shell->exit_status = 128 + wait_exit_state(status);
	}
}

char	*find_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*to_test_path;
	char	*temp;
	int		i;

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
	return (NULL);
}
