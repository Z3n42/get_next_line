/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:20:11 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/29 20:22:19 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	char	*line;
	int		bytes;
	int		fd;
	int		i;

	fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	i = 1;
	while ((bytes = get_next_line(fd, &line)))
	{
		printf("\n\n---------- MAIN OUTPUT ----------\n");
		printf("line %d: [%s]\nreturn: %d\n", i++, line, bytes);
		printf("\n");
		free(line);
		if (bytes == -1)
			break ;
	}
	printf("----- Final Values -----\n");
	printf("line=[%s]\n", line);
	printf("r=%d\n", bytes);
	free(line);
	i = 1;
	close(fd);
	return (0);
}
