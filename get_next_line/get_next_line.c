/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:29:49 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/25 17:16:22 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	while (str[c])
		c++;
	return (c);
}

char	*ft_strdup(const char *str)
{
	char	*twin;
	int		i;

	if (!(twin = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	i = 0;
	while (*str != '\0')
		twin[i++] = *((char *)str++);
	twin[i] = '\0';
	return (twin);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;

	i = 0;
	if (!(dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *str_whr_srch, int char2find)
{
	while (*str_whr_srch)
	{
		if (*str_whr_srch == char2find)
			return ((char*)str_whr_srch);
		str_whr_srch++;
	}
	if (char2find == '\0')
		return ((char*)str_whr_srch);
	return (0);
}

void	ft_memdel(void **a)
{
	if (!a || !*a)
		return ;
	free(*a);
	*a = NULL;
}

char	*ft_extract_b4eol(char *wr_nd_wipe)
{
	int		i;
	char	*b4eol;

	i = 0;
	if (!(b4eol = malloc(ft_strlen(wr_nd_wipe) + 1)))
		return (NULL);
	while (*wr_nd_wipe != '\n')
		b4eol[i++] = *wr_nd_wipe++;
	b4eol[i] = '\0';
	return (b4eol);
}

int		ft_chop(char **wr_nd_wipe, char **line)
{
	char	*aftr_eol;

	if (*wr_nd_wipe && ft_strchr(*wr_nd_wipe, '\n') > 0)
	{
		aftr_eol = ft_strchr(*wr_nd_wipe, '\n') + 1;
		aftr_eol = ft_strdup(aftr_eol);
		*line = ft_extract_b4eol(*wr_nd_wipe);
		ft_memdel((void **)wr_nd_wipe);
		*wr_nd_wipe = aftr_eol;
		return (1);
	}
	else if (*wr_nd_wipe != 0)
		*line = ft_strdup(*wr_nd_wipe);
	else
		*line = ft_strdup("");
	ft_memdel((void **)wr_nd_wipe);
	return (0);
}

int		get_next_line(char **line)
{
	int			bytes_buf;
	char		*buffer;
	static char	*wr_nd_wipe;
	char		*aux;

	if (!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) || !line
						|| BUFFER_SIZE < 1 || read(0, buffer, 0) < 0)
		return (-1);
	while ((bytes_buf = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_buf] = '\0';
		if (!wr_nd_wipe)
			wr_nd_wipe = ft_strdup(buffer);
		else
		{
			aux = ft_strjoin(wr_nd_wipe, buffer);
			ft_memdel((void **)&wr_nd_wipe);
			wr_nd_wipe = aux;
		}
		if (ft_strchr(wr_nd_wipe, '\n'))
			break ;
	}
	ft_memdel((void **)&buffer);
	return (ft_chop(&wr_nd_wipe, line));
}
