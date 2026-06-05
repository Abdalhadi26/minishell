/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:07:01 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/05 03:33:38 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/lexer/lexer.h"
#include "../src/parser/parsing.h"
void print_lexer(t_lexer *head)
{
    t_lexer *tmp;
    int i;

    tmp = head;
    i = 0;
    ft_putendl_fd("---- LEXER DUMP ----", 1);
    while (tmp)
    {
        ft_putstr_fd("Token[", 1);
        ft_putnbr_fd(i, 1);
        ft_putstr_fd("] :", 1);
        if (tmp->input)
            ft_putendl_fd(tmp->input, 1);
        else
            ft_putendl_fd("(null)", 1);
        ft_putstr_fd("  qouted: ", 1);
        ft_putnbr_fd(tmp->qouted, 1);
        ft_putendl_fd("", 1);
        tmp = tmp->next;
        i++;
    }
    ft_putendl_fd("---- END LEXER ----", 1);
}

int number_of_cmds(t_lexer *token)
{
    t_lexer *tok;
    int num_cmds;

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

t_command *main_parsing(char *input, t_shell shell )
{
    t_lexer *tokens;
    t_command *cmds;

    tokens = add_tokens(input, 0, 0);
	if (!tokens)
        return (NULL);
    if (pipe_red_dup(tokens))
        return(free_all(tokens), NULL);
    tokens= expand_lexer_tokens(tokens, shell);
    if (!tokens)
        return (NULL);
    
    // print_lexer(tokens);
    cmds = NULL;
    cmds = parsing(tokens, number_of_cmds(tokens));
    free_all(tokens);
    tokens = NULL;
    return (cmds);
}

// void print(t_command command)
// {
// 	t_redirections *temp;
// 	t_single_command *temp1;
// 	t_command cmds;
// 	int i;
// 	int j = 0;

// 	i = 0;
// 	cmds = command;
// 	while (i < cmds.num_single_commands)
// 	{
// 		j = 0;
// 		temp1 = cmds.commands[i];
// 		while(temp1->args[j])
// 		{
// 			printf("arg[%d] = %s\n", j, temp1->args[j]);
// 			j++;
// 		}
// 		printf("\n");
// 		temp = temp1->redirections;
// 		while(temp1->redirections)
// 		{
// 			printf("type = %d\n", temp->type);
// 			printf("type = %s\n", temp->file_name);
// 			printf("type = %d\n", temp->heredoc_expansion_status);
// 			printf("type = %d\n", temp->heredoc_fd);
// 			temp = temp->next;
// 		}
// 		printf("\n");
// 	}
	
// }
