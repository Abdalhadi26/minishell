/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:35:04 by ahhammad          #+#    #+#             */
/*   Updated: 2025/09/13 15:02:47 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	j;
	char	*trim;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (len && len >= i && ft_strchr(set, s1[len]))
		len--;
	trim = malloc((len - i + 2));
	if (!trim)
		return (NULL);
	while (i <= len)
		trim[j++] = s1[i++];
	trim[j] = '\0';
	return (trim);
}
