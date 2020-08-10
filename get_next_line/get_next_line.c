/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:29:49 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/10 09:59:45 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str);

char	*ft_strdup(const char *s1)
{
		char	*tab;
		int		i;

		tab = malloc(sizeof(char) * (ft_strlen(s1) + 1));
		if (!tab)
			return (NULL);
		i = 0;
		while (*s1 != '\0')
		{
			tab[i] = *((char *)s1);
			i++;
			s1++;
		}
		tab[i] = '\0';
		return (tab);
}

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
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

char	*ft_strchr(const char *string_to_search, int character_to_find)
{
	while (*string_to_search)
	{
		if (*string_to_search == character_to_find)
			return ((char*)string_to_search);
		string_to_search++;
	}
	if (character_to_find == '\0')
		return ((char*)string_to_search);
	return (0);
}

void	ft_memdel(void **a)
{
	if (!a || !*a)
		return ;
	free(*a);
	*a = NULL;
}

char	*ft_extract(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	if (!(temp = malloc(ft_strlen(str) + 1)))
		return (NULL);
	while (*str != '\n')
		temp[i++] = *str++;
	temp[i] = '\0';
	return (temp);
}

int		ft_chop(char **str, char **line)
{
	char	*temp;

	if (*str && ft_strchr(*str, '\n') > 0)
	{
		temp = ft_strchr(*str, '\n') + 1;
		temp = ft_strdup(temp);
		*line = ft_extract(*str);
		ft_memdel((void **)str);
		*str = temp;
		return (1);
	}
	if (*str != 0)
		*line = ft_strdup(*str);
	else
		*line = ft_strdup("");
	ft_memdel((void **)str);
	return (0);
}

int		get_next_line(char **line)
{
	int			bytes_buf;
	char		*buffer;
	static char	*dest;
	char		*aux;

	if (!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) || !line || BUFFER_SIZE < 1 || read(0, buffer, 0) < 0)
		return (-1);
	while ((bytes_buf = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_buf] = '\0';
		if (!dest)
			dest = ft_strdup(buffer);
		else
		{
			aux = ft_strjoin(dest, buffer);
			ft_memdel((void **)&dest);
			dest = aux;
		}
		if (ft_strchr(dest, '\n'))
			break ;
	}
	ft_memdel((void **)&buffer);
	return (ft_chop(&dest, line));
}
