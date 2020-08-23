/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:13:07 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/23 11:14:27 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static char	*ft_strchr(char *str_whr_srch, int char2find)
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
			if (ft_strchr(argv[2], argv[1][i]) != 0)
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
