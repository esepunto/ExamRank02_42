/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:16:14 by ssacrist          #+#    #+#             */
/*   Updated: 2020/09/01 17:23:44 by ssacrist         ###   ########.fr       */
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

static void		ft_printchar(int c, t_format *s)
{
	write(1, &c, 1);
	s->how_many++;
}

static void		ft_putnbr(int base, long arg, char *str_base, t_format *s)
{
	if (s->prec == 0 && s->null == 'y')
		return ;
	if (arg >= base)
		ft_putnbr(base, arg / base, str_base, s);
	ft_printchar(str_base[arg % base], s);
}

static void		ft_putstr(char *str, t_format *s)
{
	int		c;

	c = s->prec;
	if (c < 0)
		c = s->len;
	while (*str && c-- > 0)
		ft_printchar(*(str++), s);
}

static int		ft_isdigit(int c)
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

static void		spaces(int c, t_format *s)
{
	while (c-- > 0)
		ft_printchar(' ', s);
}

static void		zeros(int c, t_format *s)
{
	while (c-- > 0)
		ft_printchar('0', s);
}

static void		fill_sp_nz_neg(t_format *s)
{
	if (s->prec <= s->len && (s->null != 'y' || s->prec != 0))
		spaces(s->mfw - s->len, s);
	else
		spaces(s->mfw - s->prec, s);
	if (s->neg == 'y')
		ft_printchar('-', s);
	if (s->prec != 0)
		zeros(s->prec - s->len, s);
}

static void		idt_flags(t_format *s)
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
		s->prec = 0;
		c++;
		if (ft_isdigit(flag[c]))
			while (ft_isdigit(flag[c]))
				s->prec = (s->prec * 10) + (flag[c++] - 48);
	}
}

static int		ft_longnbr(long nbr, int base)
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

static void		fill(int base, long arg, char *str_base, t_format *s)
{
	s->len = ft_longnbr(arg, base);
	if (arg == 0)
		s->null = 'y';
	else if (arg < 0)
	{
		s->neg = 'y';
		arg *= -1;
		s->len = ft_longnbr(arg, base) + 1;
		s->prec++;
	}
	fill_sp_nz_neg(s);
	ft_putnbr(base, arg, str_base, s);
}

static void		jotdown_d(t_format *s)
{
	long		arg;

	arg = va_arg(s->args, int);
	fill(10, arg, "0123456789", s);
}

static void		jotdown_x(t_format *s)
{
	unsigned long	arg;

	arg = va_arg(s->args, unsigned int);
	fill(16, arg, "0123456789abcdef", s);
}

static void		jotdown_s(t_format *s)
{
	char	*arg;

	arg = va_arg(s->args, char *);
	if (arg == NULL)
		arg = "(null)";
	s->len = ft_strlen(arg);
	if (s->len > s->prec && s->prec >= 0)
		spaces(s->mfw - s->prec, s);
	else
		spaces(s->mfw - s->len, s);
	ft_putstr(arg, s);
}

static void		init_flags(t_format *s)
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

static void		init_struct(t_format *s)
{
	s->how_many = 0;
	init_flags(s);
}

/*
**	This ft_ have a double function:
**		1) Return str[i]: this is the type of conversion: %d, %x,%s.
**		2) Save the string-flag in var t_format s->flagstr. The program
**			will check the flags in this new string: it never
**			checks on the original string.
*/

static char		ft_look4conversion(const char *str, t_format *s)
{
	int		i;
	int		j;

	while (*str)
	{
		s->largeflag++;
		i = s->largeflag;
		j = 0;
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

static void		is_percent(const char **str, t_format *s)
{
	init_flags(s);
	s->convers = ft_look4conversion(*str, s);
	idt_flags(s);
	if (s->convers == 's')
		jotdown_s(s);
	else if (s->convers == 'd')
		jotdown_d(s);
	else if (s->convers == 'x')
		jotdown_x(s);
	*str = *str + s->largeflag;
}

int				ft_printf(const char *str, ...)
{
	t_format	s;

	va_start(s.args, str);
	init_struct(&s);
	while (*str != '\0')
	{
		if (*str == '%')
			is_percent(&str, &s);
		else
			ft_printchar(*str, &s);
		str++;
	}
	va_end(s.args);
	return (s.how_many);
}
