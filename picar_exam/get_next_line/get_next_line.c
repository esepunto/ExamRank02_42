/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 12:53:42 by ssacrist          #+#    #+#             */
/*   Updated: 2020/09/16 18:32:41 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char buffer, char *wr_nd_wipe)
{
	char	*join;
	int		i;

	i = 1;
	if (!(join = malloc(3 + sizeof(*))))
		return (NULL);
	join[0] = buffer;
	while (**line != '\0')
		join[i++] = **line++;
	join[i] = '\0';
	return (join);
}

int		get_next_line(char **line)
{
	int			bytes_buf;
	char		buffer[1];
	static char	*wr_nd_wipe;

	if (!line || read(0, buffer, 0) < 0)
		return (-1);
	*line[0] = '\0';
	while ((bytes_buf = read(0, buffer, 1)) > 0)
	{
		if (buffer[0] == '\n')
		{
			line = wr_nd_wipe;

			return (1);
		else if (buffer[0] != '\0')
			wr_nd_wipe = ft_strjoin(buffer[0], wr_nd_wipe);
	}
	free(buffer);
	return (0);
}
