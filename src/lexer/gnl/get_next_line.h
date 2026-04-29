/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:51:36 by ahhammad          #+#    #+#             */
/*   Updated: 2025/11/19 14:45:53 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*free_buf(char **p);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		has_nl(char *p);
int	ft_strlen_gnl(char *s);
char	*get_line_re(char **temp);
char	*get_next_line(int fd);
int		check_read(int read_f, char **p);
#endif
