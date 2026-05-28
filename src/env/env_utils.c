/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadi1 <hadi1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:58:45 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/27 17:11:08 by hadi1            ###   ########.fr       */
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
