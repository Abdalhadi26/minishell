/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:49:34 by aayasrah          #+#    #+#             */
/*   Updated: 2026/04/29 18:14:58 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	array_2d_len(char **arr)
{
	int i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	env_init(t_shell *shell, char **envp)
{
	char	**my_env;
	int		i;

	my_env = malloc((array_2d_len(envp) + 1) * sizeof(char *));
	if (!my_env)
		return (0);
	i = 0;
	while (envp[i])
	{
		my_env[i] = ft_strdup(envp[i]);
		if (!my_env[i])
		{
			free_2d(my_env);
			return (0);
		}
		i++;
	}
	my_env[i] = NULL;
	shell->env = my_env;
	return (1);
}
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

	t_shell myshell;

	env_init(&myshell, envp);
	env_set(&myshell.env, "TERM_PROGRAMa", "hadi");

    int i = 0;
    while (myshell.env[i] != NULL)
    {
        printf("envp[%d] = %s\n", i, myshell.env[i]);
        i++;
    }

	free_2d(myshell.env);
    return 0;
}