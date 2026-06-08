/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:07:01 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/08 03:11:37 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parsing.h"
#include "../includes/minishell.h"

int	number_of_cmds(t_lexer *token)
{
	t_lexer	*tok;
	int		num_cmds;

	if (!token)
		return (0);
	tok = token;
	num_cmds = 1;
	while (tok)
	{
		if (tok->input[0] == '|' && !tok->qouted)
			num_cmds++;
		tok = tok->next;
	}
	return (num_cmds);
}
void	aheredocs(t_redirections	*red, t_shell shell) //int fun
{
	int				pipe_fd[2];

	while (red)
	{
		
		if (red->type == redir_heredoc)
		{
			if (pipe(pipe_fd) == -1)
				return ;
			if (read_heredoc(shell, red, pipe_fd))
				return ;
			close(pipe_fd[1]);
			red->heredoc_fd = pipe_fd[0];
		}
		red = red->next;
	
	}
}

t_command	*main_parsing(char *input, t_shell shell)
{
	t_lexer		*tokens;
	t_command	*cmds;
	t_redirections *red;
	int flag;

	tokens = add_tokens(input, 0, 0);
	if (!tokens)
		return (NULL);
	tokens = expand_lexer_tokens(tokens, shell);
	if (pipe_red_dupaa(tokens, &red)  != -1 )
	{
		aheredocs(red, shell);
	}
	free_redirections (red);

	if (pipe_red_dup(tokens))
		return (free_all(tokens), NULL);
	if (!tokens)
		return (NULL);
	cmds = NULL;
	cmds = parsing(tokens, number_of_cmds(tokens));
	if (cmds)
		cmds->commands[number_of_cmds(tokens)] = 0;
	free_all(tokens);
	tokens = NULL;
	return (cmds);
}
