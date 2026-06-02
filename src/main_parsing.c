/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:07:01 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/02 03:30:58 by ahhammad         ###   ########.fr       */
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
t_command *main_parsing(char *input, t_shell shell )
{
    t_lexer *tokens;
    t_command *cmds;
		// printf("hi");

    tokens = add_tokens(input, 0, 0);
    
	if (!tokens)
    {
        printf("NOOOOO\n");
        return (NULL);
    }
    // tokens = merge_red(tokens);
    (void)shell;
    if (pipe_red_dup(tokens))
        return(NULL);
        
    print_lexer(tokens);
    
    tokens= expand_lexer_tokens(tokens, shell);
    getchar();
    // i++;
    print_lexer(tokens);
    if (!tokens)
        return (NULL);
    
    // printf("hell\n \n");
    // free_all(tokens);
        // tokens = NULL;
    cmds = NULL;
    cmds = parsing(tokens);
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
