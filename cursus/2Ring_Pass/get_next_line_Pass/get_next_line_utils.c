/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:14:19 by ingonzal          #+#    #+#             */
/*   Updated: 2021/06/30 17:19:23 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t	ft_strlen(char *str, char c)
{
	int	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		if (str[counter] == c)
			return (counter);
		counter++;
	}
	return (counter);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*array;
	int		counter;
	size_t	i;
	size_t	lens;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof 1);
		s1[0] = '\0';
	}
	lens = ft_strlen(s1, 0);
	array = ((char *)malloc((lens) + (ft_strlen(s2, 0) + 1) * (sizeof(char))));
	if (!array)
		return (NULL);
	counter = 0;
	while (i < lens)
		array[counter++] = s1[i++];
	i = 0;
	lens = ft_strlen(s2, 0);
	while (i < lens)
		array[counter++] = s2[i++];
	array[counter] = '\0';
	free(s1);
	return (array);
}

char	*ft_strchr(const char *s, int c)
{
	int	count;

	count = 0;
	if (!s)
		return (NULL);
	while (s[count])
	{
		if (s[count] == c)
			return ((char *)&s[count]);
		count++;
	}
	if (s[count] == '\0' && c == '\0')
		return ((char *)&s[count]);
	else
		return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*array;
	unsigned char	*src;
	size_t			dstcount;

	src = (unsigned char *) s;
	dstcount = 0;
	if (!src)
		return (NULL);
	array = ((char *)malloc((len + 1) * sizeof(char)));
	if (!array)
		return (NULL);
	if (start >= ft_strlen(s, 0))
	{
		array[0] = '\0';
		return (array);
	}
	while (dstcount < len)
		array[dstcount++] = src[start++];
	array[dstcount] = '\0';
	return (array);
}

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	char			*array;
	unsigned char	*src;
	size_t			dstcount;

	src = (unsigned char *) s;
	dstcount = 0;
	if (!src)
		return (NULL);
	array = ((char *)malloc((len + 1) * sizeof(char)));
	if (!array)
		return (NULL);
	if (start >= ft_strlen(s, 0))
	{
		free(s);
		free(array);
		return (NULL);
	}
	while (dstcount < len)
		array[dstcount++] = src[start++];
	array[dstcount] = '\0';
	free(s);
	return (array);
}
