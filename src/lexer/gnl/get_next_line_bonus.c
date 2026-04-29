/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:33:16 by ahhammad          #+#    #+#             */
/*   Updated: 2025/11/19 16:33:16 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*free_buf(char **p)
{
	free (*p);
	*p = NULL;
	return (NULL);
}

int	check_read(int read_f, char **p)
{
	if (read_f < 0 && p)
	{
		free_buf(p);
		return (0);
	}
	if (!*p)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char		*re_data[1024];
	char			*buffer;
	char			*temp;
	int				read_f;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_buf(&re_data[fd]));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_f = 1;
	while (!has_nl(re_data[fd]))
	{
		read_f = read(fd, buffer, BUFFER_SIZE);
		if (read_f <= 0)
			break ;
		buffer[read_f] = '\0';
		re_data[fd] = ft_strjoin(re_data[fd], buffer);
	}
	free_buf(&buffer);
	temp = get_line_re(&re_data[fd]);
	if (!check_read(read_f, &temp))
		free_buf(&re_data[fd]);
	return (temp);
}
