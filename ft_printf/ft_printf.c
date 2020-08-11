/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:16:14 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/11 20:59:29 by ssacrist         ###   ########.fr       */
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

#define FT_PRINTF_VALID_FORMATS	"sdx"

typedef struct	s_format
{
	char	convers;
	int		mfw;
	int		prec;
	va_list	args;
	int		len;
	int		how_many;
	char	arg_null;
	int		largeflag;
	char	flagstr[1276];
}				t_format;

static void	ft_putchar(int c, t_format *s)
{
	write(1, &c, 1);
	s->how_many++;
}

static void	ft_putnbr(long nb, t_format *s)
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
	if (c < 0)
		c = s->len;
	if (c != 0)
	{
		while (*str && c-- > 0)
			ft_putchar(*(str++), s);
	}
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
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
	if (s->prec == 0 && s->arg_null == 'y')
		spaces(s->mfw, s);
	else if (s->prec >= 0)
	{
		if (s->prec <= s->len)
			spaces(s->mfw - s->len, s);
		else
			spaces(s->mfw - s->prec, s);
		zeros(s->prec - s->len, s);
	}
	else
		spaces(s->mfw - s->len, s);
}

static void	print_d(long arg, t_format *s)
{
	fill(s);
	if (s->prec != 0 || s->arg_null != 'y')
		ft_putnbr(arg, s);
}

static void	print_x(char *arg, t_format *s)
{
	fill(s);
	if (s->prec != 0 || s->arg_null != 'y')
		ft_puthex(arg, s);
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

static int	ft_longnbr(long nbr, int base)
{
	int i;

	i = 1;
	while (nbr >= base)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

static void	jotdown_d(t_format *s)
{
	long		arg;
	long		nbr;

	arg = va_arg(s->args, int);
	if (arg == 0)
		s->arg_null = 'y';
	nbr = arg;
	if (arg >= 0)
		s->len = ft_longnbr(arg, 10);
	else
	{
		nbr *= -1;
		s->len = (ft_longnbr(nbr, 10)) + 1;
	}
	print_d(arg, s);
}

static void	jotdown_x(t_format *s)
{
	char			*arg;
	unsigned long	aux;

	aux = va_arg(s->args, unsigned int);
	if (aux == 0)
		s->arg_null= 'y';
	arg = dec_to_hexa(aux);
	s->len = ft_longnbr(aux, 16);
//	s->len = ft_strlen(arg);
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
	s->arg_null = ' ';
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
		while (j <= 2)
		{
			if (str[i] != FT_PRINTF_VALID_FORMATS[j])
				s->flagstr[i - 1] = str[i];
			else
			{
				s->flagstr[i - 1] = '\0';
				return (str[i]);
			}
			j++;
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
