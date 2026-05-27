/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:31:21 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/28 01:46:15 by ahhammad         ###   ########.fr       */
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
#include "../src/parser/parsing.h"

void printaa(t_command *command);
t_shell *init_shell()
{
	t_shell *shell;
	
	shell = malloc(sizeof(t_shell));
	shell->exit_status = 0;
	shell->env = NULL;
	return (shell);
}
int	main(int argc, char *argv[], char **envp)
{
	t_shell *shell;
	char	*line;
	t_command *command;

	(void)argc;
	(void)argv;
	command = NULL;	
	// g_signal = 1;
	shell = init_shell();
	if (!env_init(shell, envp))
	{
		exit(1);
	}
	// set_interactive_signals();
	while (1)
	{
		line = readline("minishell$ ");
		// printf("%s\n", line);
	
		// if (!line)
		// {
		// 	free_2d(shell.env);
		// 	ft_putstr_fd("exit\n", 2);
		// 	rl_clear_history();
		// 	exit(shell.exit_status);
		// }
		// if (g_signal == SIGINT)
		// {
		// 	g_signal = 0;
		// 	free(line);
		// 	shell.exit_status = 130;
		// 	continue;
		// }
		// if (!line[0])
		// {
		// 	free(line);
		// 	continue;
		// }
		add_history(line);
		//parse
		// printf("hi\n");
		command = main_parsing(line, *shell);
		// printf("%d", command->num_single_commands);
		printaa(command);
		// (void )command;
		if (command)
		{
			free_cmds(command);
			return (0);
		}
		collect_heredocs(command, *shell); //parsing inside heredoc
		//expand
		
		// if (command->num_single_commands == 1)
		// 	execute_single(*command->commands[0], &shell);
		// else
		// 	execute_pipeline(*command, &shell);
		// set_interactive_signals();
		// //clean the parsed command
		free(line);
	}
	return (0);
}

void printaa(t_command *command)
{
	t_redirections *temp;
	t_single_command *temp1;
	t_command *cmds;
	int i;
	int j = 0;

	i = 0;
	if (!command)
		return ;
	cmds = command;
	while (i < cmds->num_single_commands)
	{
		j = 0;
		temp1 = cmds->commands[i];i++;
		while(temp1->args && temp1->args[j])
		{
			printf("arg[%d] = %s\n", j, temp1->args[j]);
			j++;
		}
		printf("\n");
		temp = temp1->redirections;
		while(temp)
		{
			printf("type = %d\n", temp->type);
			printf("file = %s\n", temp->file_name);
			printf("status = %d\n", temp->heredoc_expansion_status);
			printf("fd = %d\n", temp->heredoc_fd);
			temp = temp->next;
		}
		
		printf("\n");
	}
	
}



