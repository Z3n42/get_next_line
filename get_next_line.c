/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:16:24 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/07 13:31:31 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{	
	char			*buf;
	ssize_t			res;
	static char		*array;
	int				end;
	int				lel;

	if (fd < 0 || fd > 999 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	res = 1;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	while (res > 0 && ft_strchr(array, '\n') == NULL)
	{
		res = read(fd, buf, BUFFER_SIZE);
		buf[res] = '\0';
		array = ft_strjoin(array, buf);
	}
	free(buf);
	end = ft_strlen(array, '\n');
	*line = ft_substr(array, 0, end);
	lel = ft_strlen(*line, 0);
	if (res != -1)
		array = ft_substr2(array, (end + 1), (ft_strlen(array, 0) - lel));
	if (res > 1)
		res = 1;
	return (res);
}
