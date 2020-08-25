/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:13:07 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/25 21:52:45 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static char	ft_strsrch(char *str_whr_srch, char char2find)
{
	while (*str_whr_srch)
	{
		if (*str_whr_srch++ == char2find)
			return (1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			j = i - 1;
			if (ft_strsrch(argv[2], argv[1][i]) == 1)
			{
				while (j >= -1)
				{
					if (argv[1][i] == argv[1][j])
						break ;
					else if (j == 0 || i == 0)
						write(1, &argv[1][i], 1);
					j--;
				}
			}
			i++;
		}
	}
	write(1, "\n", 1);
//	system("leaks inter");
}
