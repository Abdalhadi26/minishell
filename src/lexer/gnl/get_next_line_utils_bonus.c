/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:33:26 by ahhammad          #+#    #+#             */
/*   Updated: 2025/11/19 16:33:26 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(char *str, int len)
{
	char	*array;
	int		i;

	if (!str || !len)
		return (NULL);
	i = 0;
	array = (char *)malloc((len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	while (i < len)
	{
		array[i] = str[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	int		len;
	char	*array;

	i = 0;
	len = ft_strlen(s2);
	if (!s1)
		return (ft_strdup(s2, len));
	len = len + ft_strlen(s1);
	array = (char *)malloc(sizeof(char) * (len + 1));
	if (!array)
		return (free_buf(&s1));
	len = 0;
	while (s1[i])
		array[len++] = s1[i++];
	i = 0;
	while (s2[i])
		array[len++] = s2[i++];
	array[len] = '\0';
	free(s1);
	return (array);
}

int	has_nl(char *p)
{
	int		i;

	if (!p)
		return (0);
	i = 0;
	while (p[i] != '\n' && p[i])
		i++;
	if (p[i] == '\n')
		return (1);
	return (0);
}

char	*get_line_re(char **temp)
{
	int		i;
	char	*line;
	char	*str;

	if (!*temp)
		return (NULL);
	str = *temp;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_strdup(str, i);
	*temp = ft_strdup(str + i, ft_strlen(str + i));
	if (str)
		free(str);
	str = NULL;
	return (line);
}
