/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:31:21 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/20 16:13:22 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** main.c
**
** This is the entry point of the entire minishell program.
** Everything starts and ends here.
**
** What happens here:
**   1. We receive the environment variables from the operating system
**      through the envp parameter in main() and copy them into our
**      own data structure so we can modify them freely.
**
**   2. We set up signal handlers so the shell reacts correctly to
**      ctrl-C, ctrl-D and ctrl-\ from the very start.
**
**   3. We run the main loop - this is the heartbeat of the shell:
**        - readline() waits for the user to type something and press enter
**        - we send that input through the lexer, parser, expander, executor
**        - we free the memory used by that command
**        - we loop back and wait for the next input
**
**   4. When the user exits (ctrl-D or the exit builtin), we clean up
**      all allocated memory and exit gracefully.
**
** Think of main.c as the conductor of an orchestra - it doesnt play
** any instrument itself, but it coordinates everything else.
*/

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_shell shell;
	char	*line;
	t_command *command;

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
			continue;
		}
		if (!line[0])
		{
			free(line);
			continue;
		}
		add_history(line);
		//parse
		
		collect_heredocs(command); //parsing inside heredoc
		//expand
		if (command->num_single_commands == 1)
			execute_single(*command->commands[0], &shell);
		else
			execute_pipeline(*command, &shell);
		set_interactive_signals();
		//clean the parsed command
		free(line);
	}
	return (0);
}
