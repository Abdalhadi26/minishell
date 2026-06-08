/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:31:21 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/06 19:30:51 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

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

void	printaa(t_command *command)
{
	t_redirections		*temp;
	t_single_command	*temp1;
	t_command			*cmds;
	int					i;
	int					j;

	j = 0;
	i = 0;
	if (!command)
		return ;
	cmds = command;
	while (i < cmds->num_single_commands)
	{
		j = 0;
		temp1 = cmds->commands[i];
		i++;
		while (temp1->args && temp1->args[j])
		{
			printf("arg[%d] = %s  2\n", j, temp1->args[j]);
			j++;
		}
		printf("\n");
		temp = temp1->redirections;
		while (temp)
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

int	main(int argc, char *argv[], char **envp)
{
	t_shell		*shell;
	char		*line;
	int			result;
	t_command	*command;
	int			hd;

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
		hd = collect_heredocs(command, shell);
		if (hd == 2)
		{
			g_signal = 0;
			shell->exit_status = 130;
			free_cmds(command);
			free(line);
			set_interactive_signals();
			continue;
		}
		execute(command, shell);
		set_interactive_signals();
		//printaa(command);
		free_cmds(command);
		free(line);
	}
	free_2d(shell->env);
	free(shell);
	return (0);
}
