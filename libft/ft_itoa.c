/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:55:19 by ahhammad          #+#    #+#             */
/*   Updated: 2025/09/13 12:33:27 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	return_string(char *str, long num, int len)
{
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	if (num == 0)
		str[0] = '0';
	while (num)
	{
		len--;
		str[len] = 48 + (num % 10);
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;

	num = n;
	if (num <= 0)
		len = 1;
	else
		len = 0;
	while (num)
	{
		num /= 10;
		len++;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	return_string(str, n, len);
	str[len] = '\0';
	return (str);
}
