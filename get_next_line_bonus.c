/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:21:56 by hvayon            #+#    #+#             */
/*   Updated: 2021/11/15 20:09:21 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_to_remainder(int fd, char *remainder)
{
	char	*buf;
	int		byte_was_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byte_was_read = 1;
	while (!(ft_strchr(remainder, '\n')) && byte_was_read != 0)
	{
		byte_was_read = read(fd, buf, BUFFER_SIZE);
		if (byte_was_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[byte_was_read] = '\0';
		remainder = ft_strjoin(remainder, buf);
	}
	free(buf);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (0);
	remainder[fd] = ft_read_to_remainder(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = ft_get_line(remainder[fd]);
	remainder[fd] = ft_new_remainder(remainder[fd]);
	return (line);
}
