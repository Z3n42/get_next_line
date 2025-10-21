/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:33:23 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/30 20:03:58 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	get_next_line(int fd, char **line)
{
	char			*buf;
	ssize_t			res;
	static char		*a[256];
	int				end;
	int				lel;

	if (fd < 0 || fd > 999 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	res = 1;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	while (res > 0 && ft_strchr(a[fd], '\n') == NULL)
	{
		res = read(fd, buf, BUFFER_SIZE);
		buf[res] = '\0';
		a[fd] = ft_strjoin(a[fd], buf);
	}
	free(buf);
	end = ft_strlen(a[fd], '\n');
	*line = ft_substr(a[fd], 0, end);
	lel = ft_strlen(*line, 0);
	if (res != -1)
		a[fd] = ft_substr2(a[fd], (end + 1), (ft_strlen(a[fd], 0) - lel));
	if (res > 1)
		res = 1;
	return (res);
}
