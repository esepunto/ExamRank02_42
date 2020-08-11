/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:16:14 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/10 19:13:45 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This program emulates the behaviour of the "printf" function, only
**	with formats sdx and flag dot '.' (minimun witdth field and precision)
**
**	How does it?
**	1) There's only one function to print: ft_putchar (with 'write')
**	2) Uses the 's' structure to save the necessary information a lot of
**		times.
**	3) Works with convers with different states, even by similar ways.
**	4) Any conversion uses a "different" ft_ (function):
**		jotdown_dec (%d), jotdown_hexa (%x) and jotdown_string (%s)
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#define PRINTF_VALID_FORMATS	"sdx"

typedef struct	s_format
{
	char	convers;
	int		mfw;
	int		prec;
	va_list	args;
	int		len;
	int		how_many;
	int		largeflag;
	char	flagstr[1276];
}				t_format;

static void	ft_putchar(int c, t_format *s)
{
	write(1, &c, 1);
	s->how_many++;
}

static void	ft_putnbr(int nb, t_format *s)
{
	unsigned int	copy_nb;

	if (nb < 0)
	{
		ft_putchar('-', s);
		nb = (nb * (-1));
	}
	copy_nb = nb;
	if (copy_nb > 9)
		ft_putnbr(copy_nb / 10, s);
	ft_putchar(copy_nb % 10 + '0', s);
}

static void	ft_putstr(char *str, t_format *s)
{
	int		c;

	c = s->prec;
	if (!str)
		return ;
	if (c > 0)
	{
		while (*str && c-- > 0)
		{
			ft_putchar(*str, s);
			str++;
		}
	}
	else if (s->prec < 0)
	{
		while (*str)
		{
			ft_putchar(*str, s);
			str++;
		}
	}
}

static void	ft_puthex(char *str, t_format *s)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_putchar(*str, s);
		str++;
	}
}

static int	ft_isdigit(int c)
{
	return ((unsigned char)c >= '0' && (unsigned char)c <= '9');
}

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_itoa(int n)
{
	long	nbr;
	size_t	len = 1;
	char	*str;

	nbr = n;
	if (nbr > 0)
		len = 0;
	else
		nbr = -nbr;
	while (n)
	{
		if (len++)
			n = n / 10;
		else n = n / 10;
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	while (nbr > 0)
	{
		*(str + len--) = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (len == 0)
	{
		if (*(str) == '-')
			*(str) = '-';
		else
			*(str) = '0';
	}
	return (str);
}

static void	print_int_min_pos(int arg, t_format *s)
{
	if (arg != -2147483648)
		ft_putnbr(arg, s);
	else
	{
//		ft_putstr("2147483648", s);
		write(1, "2147483648", 10);
		s->how_many = s->how_many + 10;
	}
}

static void	print_int_min_neg(int arg, t_format *s)
{
	if (arg != -2147483648)
		ft_putnbr(arg, s);
	else
		ft_putstr("-2147483648",s);
}

static void	spaces(int c, t_format *s)
{
	while (c-- > 0)
		ft_putchar(' ', s);
}

static void	zeros(int c, t_format *s)
{
	while (c-- > 0)
		ft_putchar('0', s);
}

static void	if_neg_precision_d(int arg, t_format *s)
{
	if (s->prec < s->len)
		spaces(s->mfw - s->len, s);
	else if (s->mfw > s->prec)
		spaces((s->mfw - s->prec) - 1, s);
	if (arg < 0)
	{
		arg = arg * (-1);
		ft_putchar('-', s);
	}
	zeros(s->prec - s->len + 1, s);
	print_int_min_pos(arg, s);
}

static void	if_neg_d(int arg, t_format *s)
{
	if (s->prec >= 0)
		if_neg_precision_d(arg, s);
	else
	{
		spaces(s->mfw - s->len, s);
		print_int_min_neg(arg, s);
	}
}

static void	if_pos(t_format *s)
{
	if (s->prec >= 0)
	{
		if (s->prec <= s->len)
			spaces(s->mfw - s->len, s);
		else if (s->mfw > s->prec)
			spaces(s->mfw - s->prec, s);
		zeros(s->prec - s->len, s);
	}
	else
		spaces(s->mfw - s->len, s);
}

static void	print_d(int arg, t_format *s)
{
	if (s->prec == 0 && arg == 0)
		spaces(s->mfw, s);
	else if (arg < 0)
		if_neg_d(arg, s);
	else
	{
		if_pos(s);
		ft_putnbr(arg, s);
	}
}

static void	print_x(char *arg, t_format *s)
{
	if (s->prec == 0 && arg[0] == '0' && arg[1] == '\0')
		spaces(s->mfw, s);
	else
	{
		if_pos(s);
		ft_puthex(arg, s);
	}
}

static void	print_s(char *arg, t_format *s)
{
	if (s->prec >= s->len || s->prec < 0)
		spaces(s->mfw - s->len, s);
	else if (s->prec >= 0)
		spaces(s->mfw - s->prec, s);
	ft_putstr(arg, s);
}

static void	flag(char *flag, int c, t_format *s)
{
	if (ft_isdigit(flag[c]))
	{
		while (ft_isdigit(flag[c]))
			s->mfw = (s->mfw * 10) + (flag[c++] - 48);
	}
	if (flag[c] == '.')
	{
		c++;
		s->prec = 0;
		if (ft_isdigit(flag[c]))
		{
			while (ft_isdigit(flag[c]))
				s->prec = (s->prec * 10) + (flag[c++] - 48);
		}
	}
}

static char	*invert_str(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i <= j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

static char	*dec_to_hexa(unsigned long arg)
{
	static char		result[20];
	int				i;
	unsigned long	temp;
	char			*hexalower;

	hexalower = "0123456789abcdef";
	i = 0;
	if (arg == 0)
		return ("0\0");
	while (arg != 0)
	{
		temp = arg % 16;
		result[i] = hexalower[temp];
		i++;
		arg = arg / 16;
	}
	result[i] = '\0';
	return (invert_str(result));
}

static void	jotdown_d(t_format *s)
{
	int		arg;

	arg = va_arg(s->args, int);
	s->len = ft_strlen(ft_itoa(arg));
	print_d(arg, s);
}

static void	jotdown_x(t_format *s)
{
	char			*arg;
	unsigned long	aux;

	aux = va_arg(s->args, unsigned int);
	arg = dec_to_hexa(aux);
	s->len = ft_strlen(arg);
	print_x(arg, s);
}

static void	jotdown_s(t_format *s)
{
	char	*arg;

	arg = va_arg(s->args, char *);
	if (arg == NULL)
		arg = "(null)";
	s->len = ft_strlen(arg);
	print_s(arg, s);
}

static void	flags_init(t_format *s)
{
	s->flagstr[0] = *("");
	s->largeflag = 0;
	s->len = 0;
	s->convers = ' ';
	s->mfw = 0;
	s->prec = -1;
}

static void	s_init(t_format *s)
{
	s->how_many = 0;
	flags_init(s);
}

/*
**	This ft_ have a double function:
**		1) Return the type of conversion: d,s,c,x...
**		2) Save the string-flag in t_format s->flagstr
**
**	The program always check the flags in this new string: it never
**	checks on the original string.
*/

static char	ft_look4conversion(const char *str, t_format *s)
{
	int		i;
	int		j;

	while (*str)
	{
		j = 0;
		s->largeflag++;
		i = s->largeflag;
		while (j <= 1)
		{
			if (str[i] != PRINTF_VALID_FORMATS[j])
				if (j++ == 1)
					s->flagstr[i - 1] = str[i];
			if (str[i] == PRINTF_VALID_FORMATS[j])
			{
				s->flagstr[i - 1] = '\0';
				return (str[i]);
			}
		}
	}
	return (str[i]);
}

static void	is_percent(const char **str, t_format *s)
{
	flags_init(s);
	s->convers = ft_look4conversion(*str, s);
	flag(s->flagstr, 0, s);
	if (s->convers == 's')
		jotdown_s(s);
	else if (s->convers == 'd')
		jotdown_d(s);
	else if (s->convers == 'x')
		jotdown_x(s);
	*str = *str + s->largeflag;
}

int			ft_printf(const char *str, ...)
{
	t_format	s;

	if (!str || !*str)
		return (0);
	va_start(s.args, str);
	s_init(&s);
	while (*str != '\0')
	{
		if (*str == '%')
			is_percent(&str, &s);
		else
			ft_putchar(*str, &s);
		str++;
	}
	va_end(s.args);
	return (s.how_many);
}
