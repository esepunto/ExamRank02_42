/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 10:17:04 by ssacrist          #+#    #+#             */
/*   Updated: 2020/09/10 19:15:16 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static char	ft_find(char *str, int chr2find)
{
	while (*str)
	{
		if (*str++ == chr2find)
			return (1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	int	i;
	int	j;
	
	i = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			if (ft_find(argv[2], argv[1][i]) != 0)
			{
				j = i - 1;
				while (j >= -1)
				{
					if (argv[1][i] == argv[1][j])
						break;
					else if (i == 0 || j == -1)
						write(1, &argv[1][i], 1);
					j--;
				}		
			}
			i++;
		}
	}
	write(1, "\n", 1);
}

