/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:31:21 by aayasrah          #+#    #+#             */
// <<<<<<< Updated upstream
/*   Updated: 2026/05/28 14:13:55 by aayasrah         ###   ########.fr       */
// =======
/*   Updated: 2026/05/28 14:44:09 by ahhammad         ###   ########.fr       */
// >>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../src/parser/parsing.h"
int 	g_signal;

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
int i =0;
	//set_interactive_signals();
	while (i<3)
	{
		i++;
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
		// 	shell->exit_status = 130;
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
		// (void )command;
		if (command)
		{
			printaa(command);
			// free_cmds(command);
			collect_heredocs(command, *shell); //parsing inside heredoc
			free_cmds(command);

		}
		//expand
		
		// if (command->num_single_commands == 1)
		// 	execute_single(*command->commands[0], &shell);
		// else
		// 	execute_pipeline(*command, &shell);
		// set_interactive_signals();
		// //clean the parsed command
		free(line);
	}
	free_2d(shell->env);
	free(shell);
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
			printf("arg[%d] = %s  2\n", j, temp1->args[j]);
			j++;
		}
		printf("\n");
		temp = temp1->redirections;
		while(temp)
		{
			printf("type = %d\n", temp->type);
			printf("file = %s  2\n", temp->file_name);
			printf("status = %d\n", temp->heredoc_expansion_status);
			printf("fd = %d\n", temp->heredoc_fd);
			temp = temp->next;
		}
		
		printf("\n");
	}
	
}



