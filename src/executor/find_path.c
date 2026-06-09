/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:15:13 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/09 19:48:33 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_absolute_path_command(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	else
		return (NULL);
}

static char	*free_n_return(char **paths, char *to_test_path)
{
	free_2d(paths);
	return (to_test_path);
}

char	*find_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*to_test_path;
	char	*temp;
	int		i;

	if (strchr(cmd, '/'))
		return (check_absolute_path_command(cmd));
	paths = ft_split(env_get(shell->env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_no_free("/", cmd);
		to_test_path = ft_strjoin_no_free(paths[i], temp);
		free(temp);
		if (access(to_test_path, F_OK) == 0)
			return (free_n_return(paths, to_test_path));
		else
			free(to_test_path);
		i++;
	}
	free_2d(paths);
	return (NULL);
}
