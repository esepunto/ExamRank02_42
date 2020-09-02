/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 09:27:38 by ssacrist          #+#    #+#             */
/*   Updated: 2020/09/02 12:53:03 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static char	*ft_strjoin_no_malloc(char *s1, char *s2)
{
	char	*str_sum;
	int		i;

	i = 0;
	str_sum = s1;
	while (*s1 != '\0')
		str_sum[i++] = *s1++;
	while (*s2 != '\0')
		str_sum[i++] = *s2++;
	str_sum[i] = '\0';
	return(str_sum);
}

int			main(int argc, char **argv)
{
	int 	i;
	int 	j;
	char	*str_sum;
 
	i = 0;
	if (argc == 3)
	{
		str_sum = ft_strjoin_no_malloc(argv[1], argv[2]);
		while (str_sum[i])
		{
			j = i - 1;
			while (j >= -1)
			{
				if (str_sum[j] == str_sum[i])
				   break;
				else if (i == 0 || j == -1)
					write(1, &str_sum[i], 1);	
				j--;
			}
			i++;
		}
	}
	write(1, "\n", 1);
//	system("leaks union");
}	
