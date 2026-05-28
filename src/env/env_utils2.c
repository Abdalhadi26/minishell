/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadi1 <hadi1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:11:12 by hadi1             #+#    #+#             */
/*   Updated: 2026/05/27 17:12:13 by hadi1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_3str(const char *s1, const char *s2, const char *s3)
{
	char	*str;
	size_t	len;

	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len);
	ft_strlcat(str, s2, len);
	ft_strlcat(str, s3, len);
	return (str);
}

int	extend_and_append(char ***env, char *key, char *value)
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
	new_env[i++] = ft_strjoin_3str(key, "=", value);
	new_env[i] = NULL;
	free_2d(*env);
	*env = new_env;
	return (1);
}
