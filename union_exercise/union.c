/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:09:47 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/06 21:48:55 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static char	*ft_strjoin_no_malloc(char *s1, char *s2)
{
	char	*dest;
	int		i;

	i = 0;
	dest = s1;
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}

int			main(int argc, char **argv)
{
	int		i;
	int		c;
	char	*str_add;

	if (argc == 3)
	{
		str_add = ft_strjoin_no_malloc(argv[1], argv[2]);
		i = 0;
		while (str_add[i])
		{
			c = i - 1;
			while (c >= -1)
			{
				if (str_add[i] == str_add[c])
					break ;
				else if (c == 0 || i == 0)
					write(1, &str_add[i], 1);
				c--;
			}
			i++;
		}
	}
	write(1, "\n", 1);
}
