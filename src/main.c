/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:31:21 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/25 16:39:09 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_shell		shell;
	char		*line;
	t_command	*command;

	(void)argc;
	(void)argv;
	command = NULL;
	shell.exit_status = 0;
	if (!env_init(&shell, envp))
	{
		exit(1);
	}
	set_interactive_signals();
	while (1)
	{
		line = readline("minishell ");
		if (!line)
		{
			free_2d(shell.env);
			ft_putstr_fd("exit\n", 2);
			rl_clear_history();
			exit(shell.exit_status);
		}
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(line);
			shell.exit_status = 130;
			continue ;
		}
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		// parse
		collect_heredocs(command); // parsing inside heredoc
		// expand
		if (command->num_single_commands == 1)
			execute_single(*command->commands[0], &shell);
		else
			execute_pipeline(*command, &shell);
		set_interactive_signals();
		// clean the parsed command
		free(line);
	}
	return (0);
}
