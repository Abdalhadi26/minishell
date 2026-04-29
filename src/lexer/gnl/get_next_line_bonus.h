/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:33:00 by ahhammad          #+#    #+#             */
/*   Updated: 2025/11/19 16:33:00 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*free_buf(char **p);
int		ft_strlen(char *s);
char	*ft_strdup(char *str, int len);
char	*ft_strjoin(char *s1, char *s2);
int		has_nl(char *p);
char	*get_line_re(char **temp);
char	*get_next_line(int fd);
int		check_read(int read_f, char **p);
#endif
