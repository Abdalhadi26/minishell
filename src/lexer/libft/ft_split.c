/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:36:28 by ahhammad          #+#    #+#             */
/*   Updated: 2025/09/13 14:52:16 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (words);
}

static int	get_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	*create_spl(const char *s, char c)
{
	int		len;
	int		i;
	char	*str;

	len = get_len(s, c);
	str = malloc(len + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (s[i] && i < len && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

static void	*free_split(char **list, int elements)
{
	int	i;

	i = 0;
	while (i < elements)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		l;

	if (!s)
		return (NULL);
	list = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	l = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			list[l++] = create_spl(s, c);
			if (!list[l - 1])
				return (free_split(list, l));
			while (*s && *s != c)
				s++;
		}
	}
	list[l] = NULL;
	return (list);
}
