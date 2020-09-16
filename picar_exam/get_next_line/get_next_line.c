/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 12:53:42 by ssacrist          #+#    #+#             */
/*   Updated: 2020/09/17 00:42:48 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strjoin(char *str, char *buffer)
{
	char	*join;
	int		i;

	i = 0;
	while (str[i])
		i++;
	join = (char *)malloc(i + 2);
	i = 0;
	while (str[i] != '\0')
	{
		join[i] = str[i];
		i++;
	}
//	printf("i pre  ++: %d, join: %s\n", i, join);
	join[i++] = buffer[0];
//	printf("i post ++: %d, join: %s\n", i, join);
	join[i++] = '\0';
//	printf("i post 00: %d, join: %s\n", i, join);
	free(str);
//	exit (-1);
	return (join);
}

int		get_next_line(char **line)
{
	int			bytes_buf;
	char		*buffer;

	if (!(*line = (char *)malloc(1)) || !line || !(buffer = (char *)malloc(2)))
		return (-1);
	(*line)[0] = '\0';
	while ((bytes_buf = read(0, buffer, 1)) > 0)
	{
		buffer[1] = '\0';
		if (buffer[0] == '\n' || buffer[0] == '\0')
		{	
			break;
		}
		*line = ft_strjoin(*line, buffer);
	}
	free(buffer);
	return (bytes_buf);
}
