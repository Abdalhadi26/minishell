/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:31:21 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/10 10:09:26 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

int		g_signal;

static void	execute(t_command_list *command, t_shell *shell)
{
	if (command->num_single_commands == 1)
		execute_single(command, *command->commands[0], shell);
	else
		execute_pipeline(command, shell);
}

static void	handle_eof(t_shell *shell)
{
	int	result;

	free_2d(shell->env);
	result = shell->exit_status;
	free(shell);
	ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	exit(result);
}

static void	process_line(char *line, t_shell *shell)
{
	t_command_list	*command;
	int				hd;

	add_history(line);
	command = main_parsing(line, shell);
	if (!command)
		return ;
	hd = collect_heredocs(command, shell);
	if (hd == 2)
	{
		g_signal = 0;
		shell->exit_status = 130;
		clean_cmds(command);
		set_interactive_signals();
		return ;
	}
	execute(command, shell);
	set_interactive_signals();
	clean_cmds(command);
}

static int	handle_main_argc(void)
{
	ft_putstr_fd("Usage: ./minishell\n", 2);
	return (1);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;
	char	*line;

	if (argc > 1)
		return (handle_main_argc());
	(void)argv;
	shell = init_shell();
	if (!shell)
		return (0);
	if (env_init(shell, envp))
		exit(1);
	set_interactive_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			handle_eof(shell);
		check_sigint_status(shell);
		if (line[0])
			process_line(line, shell);
		free(line);
	}
	return (0);
}
