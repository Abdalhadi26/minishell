/*
** env_utils.c
**
** This file contains all the utility functions for interacting with
** our environment linked list throughout the program.
**
** The four fundamental operations on our environment:
**
**   GET - find the value of a variable by name
**     We walk the linked list comparing keys until we find a match.
**     Returns the value string or NULL if not found.
**     Used constantly by the expander when it sees $VARNAME.
**
**   SET - add or update a variable
**     First check if the variable already exists.
**     If yes, update its value.
**     If no, create a new node and add it to the list.
**     Used by export and by cd when updating PWD.
**
**   DELETE - remove a variable by name
**     Find the node, unlink it from the list, free its memory.
**     Used by unset.
**
**   TO_ARRAY - convert the linked list back to char**
**     execve() needs the environment as a char** array, not a linked list.
**     We count the nodes, malloc an array, fill it with "KEY=value" strings.
**     Used by the executor every time it calls execve().
**
** Think of this file as the complete API for our environment database -
** every part of the shell that needs to read or write environment
** variables goes through the functions in this file.
*/

#include "../../includes/minishell.h"

static int exists(char **env, char *key)
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
			continue;
		}
		if (!ft_strncmp(key, env[i], (equal_sign - env[i])))
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
	int		variable_index;

	variable_index = exists(*env, key);
	printf("the i is %d before all\n",variable_index);

	if (variable_index > -1)
	{
		printf("the i is %d before join\n",variable_index);
		free(*env[variable_index]);
		*env[variable_index] = ft_strjoin_3str(key, "=", value);
		return (1);
	}
	printf("the i is %d before extend\n",variable_index);
	if (!extend_and_append(env, key, value))
		return (0);
	printf("the i is %d after extend\n",variable_index);
	return (1);
}

int	env_unset(char ***env, char *key)
{
	int	i;

	i = exists(*env, key);
	if (!i)
		return (-1);
	while (*env[i])
	{
		free(*env[i]);
		*env[i] = *env[i + 1];
		i++;
	}
	return (1);
}
