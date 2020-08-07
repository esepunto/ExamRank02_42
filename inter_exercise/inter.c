/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:13:07 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/07 10:41:29 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static char	*ft_strchr(char *string_to_search, int character_to_find)
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

int			main(int argc, char **argv)
{
	int		i;
	int		c;

	i = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			c = i - 1;
			if (ft_strchr(argv[2], argv[1][i]) != 0)
			{
				while (c >= -1)
				{
					if (argv[1][i] == argv[1][c])
						break ;
					else if (c == 0 || i == 0)
						write(1, &argv[1][i], 1);
					c--;
				}
			}
			i++;
		}
	}
	write(1, "\n", 1);
}
