/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:31:21 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/05 22:39:03 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../src/parser/parsing.h"

int		g_signal;

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->exit_status = 0;
	shell->env = NULL;
	return (shell);
}

void	execute(t_command *command, t_shell *shell)
{
	if (command->num_single_commands == 1)
		execute_single(command, *command->commands[0], shell);
	else
		execute_pipeline(command, shell);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell		*shell;
	char		*line;
	int			result;
	t_command	*command;

	(void)argc;
	(void)argv;
	shell = init_shell();
	if (!shell)
		return (0);
	shell->exit_status = 0;
	if (!env_init(shell, envp))
		exit(1);
	set_interactive_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			free_2d(shell->env);
			result = shell->exit_status;
			free(shell);
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			exit(result);
		}
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			shell->exit_status = 130;
		}
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		command = main_parsing(line, *shell);
		if (!command)
		{
			free(line);
			continue ;
		}
		collect_heredocs(command, *shell);
		execute(command, shell);
		set_interactive_signals();
		free_cmds(command);
		free(line);
	}
	free_2d(shell->env);
	free(shell);
	return (0);
}
