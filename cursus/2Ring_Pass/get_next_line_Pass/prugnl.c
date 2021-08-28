/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prugnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:46:43 by ingonzal          #+#    #+#             */
/*   Updated: 2021/08/26 14:44:40 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int	get_next_line(char **line)
{
	int		i;
	int		value;
	char	chr;
	char	*buff;
	buff = malloc(1024);
	if (!buff)
		return (-1);
	i = 0;
	value = read(0, &chr, 1);
	while (chr != '\n' && chr != '\0')
	{
		if (chr != '\n' && chr != '\0')
			buff[i] = chr;
		i++;
		value = read(0, &chr, 1);
	}
	buff[i] = '\0';
	*line = buff;
	return (value);
}

int main(void)
{
	int		r;
	char	*line;
	line = NULL;
	while ((r = get_next_line(&line)) > 1)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
	system("leaks a.out");
}
