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

void	execute(t_command *command, t_shell *shell)
{
	if (command->num_single_commands == 1)
		execute_single(command , *command->commands[0], shell);
	else
		execute_pipeline(command, shell);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell *shell;
	char	*line;
	int result;
	t_command *command;

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
			free(line);
			shell->exit_status = 130;
			continue;
		}
		if (!line[0])
		{
			free(line);
			continue;
		}
		add_history(line);
		command = main_parsing(line, *shell);
		// printaa(command);
		if (!command)
		{
			free(line);
			continue;
		}
		collect_heredocs(command, *shell);
		execute(command, shell);
		/*
			if (strchr(cmd, '/'))// in find_path fun u used built in fun
			ft_strjoin("/", cmd); in same fun (my ft_strjoin makes free for first arg) and u used it in diff places
			so I created new fun to this one but with making free, u must allow me to do that :) ft_strjoin_ayasrah
		
			if command not found ?? makes leaks
			*/
		set_interactive_signals();
		free_cmds(command);
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



