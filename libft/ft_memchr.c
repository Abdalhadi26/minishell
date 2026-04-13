/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 21:38:31 by ahhammad          #+#    #+#             */
/*   Updated: 2025/09/13 12:34:30 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			index;

	str = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (str[index] == (unsigned char)c)
			return (&str[index]);
		index++;
	}
	return (NULL);
}
