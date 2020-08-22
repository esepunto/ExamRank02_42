/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:16:14 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/22 20:55:01 by ssacrist         ###   ########.fr       */
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
**		jotdown_dec (%d), jotdown_hexa (%x) and jotdown_string (%s).
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#define FT_PRINTF_VALID_FORMATS	"sdx"

typedef struct	s_format
{
	char	convers;
	int		mfw;
	int		prec;
	va_list	args;
	int		len;
	int		how_many;
	char	null;
	char	neg;
	int		largeflag;
	char	flagstr[1];
}				t_format;

static void	ft_putchar(int c, t_format *s)
{
	write(1, &c, 1);
	s->how_many++;
}

static void	ft_putnbr(long nb, t_format *s)
{
	if (nb > 9)
		ft_putnbr(nb / 10, s);
	ft_putchar(nb % 10 + '0', s);
}

static void	ft_putstr(char *str, t_format *s)
{
	int		c;

	c = s->prec;
	if (c < 0)
		c = s->len;
	while (*str && c-- > 0)
		ft_putchar(*(str++), s);
}

static void	ft_puthex(char *str, t_format *s)
{
	while (*str)
		ft_putchar(*(str++), s);
}

static int	ft_isdigit(int c)
{
	return ((unsigned char)c >= '0' && (unsigned char)c <= '9');
}

static size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	while (str[c])
		c++;
	return (c);
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

static void	fill(t_format *s)
{
	if (s->prec == 0 && s->null == 'y')
		spaces(s->mfw, s);
	else if (s->prec >= 0)
	{
		if (s->prec <= s->len)
			spaces(s->mfw - s->len, s);
		else
			spaces(s->mfw - s->prec, s);
		if (s->neg == 'y')
			ft_putchar('-', s);
		zeros(s->prec - s->len, s);
	}
	else
	{
		spaces(s->mfw - s->len, s);
		if (s->neg == 'y')
			ft_putchar('-', s);
	}
}

static void	print_s(char *arg, t_format *s)
{
	if (s->prec >= s->len || s->prec < 0)
		spaces(s->mfw - s->len, s);
	else
		spaces(s->mfw - s->prec, s);
	ft_putstr(arg, s);
}

static void	flag(t_format *s)
{
	int		c;
	char	*flag;

	c = 0;
	flag = s->flagstr;
	if (ft_isdigit(flag[c]))
		while (ft_isdigit(flag[c]))
			s->mfw = (s->mfw * 10) + (flag[c++] - 48);
	if (flag[c] == '.')
	{
		c++;
		s->prec = 0;
		if (ft_isdigit(flag[c]))
			while (ft_isdigit(flag[c]))
				s->prec = (s->prec * 10) + (flag[c++] - 48);
	}
}

static int	ft_longnbr(long nbr, int base)
{
	int c;

	c = 1;
	while (nbr >= base)
	{
		nbr /= base;
		c++;
	}
	return (c);
}

static char	*dec_to_hexa(unsigned long arg, t_format *s)
{
	static char		result[20];
	int				i;
	unsigned long	temp;
	char			*hexalower;

	hexalower = "0123456789abcdef";
	i = s->len -1;
	if (arg == 0)
		return ("0\0");
	while (arg)
	{
		temp = arg % 16;
		result[i--] = hexalower[temp];
		arg = arg / 16;
	}
	result[s->len] = '\0';
	return (result);
}

static void	jotdown_d(t_format *s)
{
	long		arg;

	arg = va_arg(s->args, int);
	s->len = ft_longnbr(arg, 10);
	if (arg == 0)
		s->null = 'y';
	if (arg < 0)
	{
		s->neg = 'y';
		arg *= -1;
		s->len = ft_longnbr(arg, 10) + 1;
		if (s->prec)
			s->prec++;
	}
	fill(s);
	if (s->prec != 0 || s->null != 'y')
		ft_putnbr(arg, s);
}

static void	jotdown_x(t_format *s)
{
	char			*arg;
	unsigned long	aux;

	aux = va_arg(s->args, unsigned int);
	if (aux == 0)
		s->null= 'y';
	s->len = ft_longnbr(aux, 16);
	arg = dec_to_hexa(aux, s);
	fill(s);
	if (s->prec != 0 || s->null != 'y')
		ft_puthex(arg, s);
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
	s->null = ' ';
	s->neg = ' ';
}

static void	s_init(t_format *s)
{
	s->how_many = 0;
	flags_init(s);
}

/*
**	This ft_ have a double function:
**		1) Return str[i]: this is the type of conversion: d,s,c.
**		2) Save the string-flag in var t_format s->flagstr. The program 
**			will check the flags in this new string: it never
**			checks on the original string.
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
		while (j <= 2)
		{
			if (str[i] == FT_PRINTF_VALID_FORMATS[j++])
			{
				s->flagstr[i - 1] = '\0';
				return (str[i]);
			}
		}
		s->flagstr[i - 1] = str[i];
	}
	return (str[i]);
}

static void	is_percent(const char **str, t_format *s)
{
	flags_init(s);
	s->convers = ft_look4conversion(*str, s);
	flag(s);
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
