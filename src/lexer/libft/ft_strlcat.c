/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:11:21 by ahhammad          #+#    #+#             */
/*   Updated: 2025/09/11 17:01:50 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	len_dest = ft_strlen(dst);
	if (size == 0)
		return (src_len);
	if (size <= len_dest)
		return (size + src_len);
	while (src[i] && (len_dest + i) < size - 1)
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	return (len_dest + src_len);
}
