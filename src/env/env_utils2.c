/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:11:12 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/05 20:46:03 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_3str(const char *key, const char *eq, const char *value)
{
	char	*str;
	size_t	len;

	if (!eq)
		return (ft_strdup(key));
	len = ft_strlen(key) + ft_strlen(eq) + ft_strlen(value) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, key, len);
	ft_strlcat(str, eq, len);
	ft_strlcat(str, value, len);
	return (str);
}

int	extend_and_append(char ***env, char *key, char *eq, char *value)
{
	char	**new_env;
	int		i;

	new_env = malloc((array_2d_len(*env) + 2) * sizeof(char *));
	if (!new_env)
		return (0);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		if (!new_env[i])
		{
			free_2d(new_env);
			return (0);
		}
		i++;
	}
	new_env[i++] = ft_strjoin_3str(key, eq, value);
	new_env[i] = NULL;
	free_2d(*env);
	*env = new_env;
	return (1);
}
