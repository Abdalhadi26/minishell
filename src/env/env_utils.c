/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:58:45 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/07 15:58:46 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	key_compare(const char *key, const char *var, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || key == var)
		return (0);
	while ((i < n) && (key[i] || var[i]))
	{
		if (key[i] != var[i])
			return ((unsigned char)key[i] - (unsigned char)var[i]);
		i++;
	}
	if (key[i] == 0 && var[i] == '=')
		return (0);
	return ((unsigned char)key[i] - (unsigned char)var[i]);
}

static int	exists(char **env, char *key)
{
	char	*equal_sign;
	int		i;

	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (!equal_sign)
		{
			i++;
			continue ;
		}
		if (!key_compare(key, env[i], (equal_sign - env[i])))
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_strjoin_3str(const char *s1, const char *s2, const char *s3)
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

static int	extend_and_append(char ***env, char *key, char *value)
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

char	*env_get(char **env, char *key)
{
	char	*equal_sign;
	int		i;

	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (!ft_strncmp(key, env[i], (equal_sign - env[i])))
			return (equal_sign + 1);
		i++;
	}
	return (NULL);
}

int	env_set(char ***env, char *key, char *value)
{
	int	variable_index;

	variable_index = exists(*env, key);
	if (variable_index > -1)
	{
		free((*env)[variable_index]);
		(*env)[variable_index] = ft_strjoin_3str(key, "=", value);
		return (1);
	}
	if (!extend_and_append(env, key, value))
		return (0);
	return (1);
}

int	env_unset(char ***env, char *key)
{
	int		i;
	char	*c;

	i = exists(*env, key);
	if (i == -1)
		return (0);
	c = (*env)[i];
	while ((*env)[i])
	{
		(*env)[i] = NULL;
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	free(c);
	return (1);
}
