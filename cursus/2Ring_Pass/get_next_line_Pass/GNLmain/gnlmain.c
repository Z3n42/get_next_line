/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnlmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:11:46 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/29 15:17:26 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int	fd;
	(void)argc;
	(void)argv;
	char	*tab;
	int		i;
	int		out;
	
	out = 0;
	i = 0;
//	tab = (char **)malloc(sizeof(char *) * 10);
	fd = open("gnlTester/files/41_with_nl", O_RDONLY);
//	printf("hsdf");
	get_next_line(fd, &tab);
	get_next_line(fd, &tab);
	get_next_line(fd, &tab);
	get_next_line(fd, &tab);
//	get_next_line(fd, &tab);
//	get_next_line(fd, &tab);
//	printf("%s\n", tab);
//	while (get_next_line(fd, &tab))
//	{
//		printf("\nCALL");
	//	printf("\nOUT_: %s \nMEMORY_DIR: %p", tab[i], tab[i]);
//		i++;
//		if (fd == -1)
//			break ;
//		printf("\n----------------------------END------------------------\n\n-");
//	}
}
