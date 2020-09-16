/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 12:53:42 by ssacrist          #+#    #+#             */
/*   Updated: 2020/09/17 01:20:35 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *line, char *buffer)
{
	char	*join;
	int		i;

	i = 0;
	while (line[i])
		i++;
	join = malloc(i + 2);
	i = 0;
	while (line[i] != '\0')
	{
		join[i] = line[i];
		i++;
	}
	free(line);
	join[i++] = buffer[0];
	join[i++] = buffer[1];
	return (join);
}

int		get_next_line(char **line)
{
	int			bytes_buf;
	char		buffer[2];

	if (!(*line = malloc(1)) || !line)
		return (-1);
	(*line)[0] = '\0';
	while ((bytes_buf = read(0, buffer, 1)) > 0)
	{
		buffer[1] = '\0';
		if (buffer[0] == '\0' || buffer[0] == '\n')
			break;
		*line = ft_strjoin(*line, buffer);
	}
	return (bytes_buf);
}
