/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:16:14 by ssacrist          #+#    #+#             */
/*   Updated: 2020/08/10 12:27:46 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This program emulates the behaviour of the "printf" function, only
**	with formats sdx and flags .
**
**	How does it?
**	1) There's only one function to print: ft_putchar (with 'write')
**	2) Uses the 'carrier' structure to save the necessary information a lot of
**		times.
**	3) Works with convers with different states, even by similar ways.
**	4) Any conversion uses a "different" ft_ (function):
**		jotdown_dec, jotdown_hexa and jotdown_string
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define PRINTF_VALID_FORMATS	"sdx"
#define HEXALOWER	"0123456789abcdef"

typedef struct	s_format
{
	char	convers;
	int		percent;
	int		dot;
	int		pos_dot;
	int		asterisk;
	int		width;
	int		precision;
	va_list	arguments;
	int		large_arg;
	char	arg_null;
	int		code_zmpw;
	int		how_many;
	int		largeflag;
	char	flagstr[1276];
}				t_format;

int				ft_printf(const char *str, ...);

void			jotdown_c(t_format *carrier);

void			jotdown_s(t_format *carrier);
void			flag_s(char *flag, int c, t_format *carrier);
void			print_s(char *arg, t_format *carrier);
void			writespaces_s(t_format *carrier);
void			asterisks_s(t_format *carrier);
void			if_writezeros_s(t_format *carrier);
void			if_writespaces_s(t_format *carrier);
void			adjust_prec_width(t_format *carrier);

void			jotdown_d(t_format *carrier);
void			flag(char *flag, int c, t_format *carrier);
void			print_d(int arg, t_format *carrier);
void			writespaces(int c, t_format *carrier);
void			writezeros(int c, t_format *carrier);
void			print_int_min_pos(int arg, t_format *carrier);
void			print_int_min_neg(int arg, t_format *carrier);
void			aux_print_spaces(int arg, t_format *carrier);
void			if_minus_d(int arg, t_format *carrier);
void			if_nominus_noneg_d(int arg, t_format *carrier);
void			if_neg_d(int arg, t_format *carrier);

void			jotdown_x(t_format *carrier);
char			*dec_to_hexa(unsigned long arg);
void			print_x(char *arg, t_format *carrier);
void			aux_print_spaces_x(char *arg, t_format *carrier);
void			if_minus_x(char *arg, t_format *carrier);
void			if_nominus_noneg_x(char *arg, t_format *carrier);

size_t			ft_strlen(const char *str);
int				ft_isdigit(int c);
char			*ft_itoa(int n);

void			ft_putchar(int c, t_format *carrier);
void			ft_putnbr(int nb, t_format *carrier);
void			ft_putstr(char *str, t_format *carrier);
void			ft_puthex(char *str, t_format *carrier);




static void	if_minus_neg_d(int arg, t_format *carrier)
{
	if (carrier->precision >= 0)
	{
		if (carrier->precision < carrier->large_arg)
			aux_print_spaces(arg, carrier);
		else
		{
			if (arg < 0)
			{
				arg = arg * (-1);
				ft_putchar('-', carrier);
			}
			writezeros(carrier->precision - carrier->large_arg + 1, carrier);
			print_int_min_pos(arg, carrier);
			if (carrier->width > carrier->precision)
				writespaces(carrier->width - carrier->precision - 1, carrier);
		}
	}
}

static void	if_minus_precision_d(int arg, t_format *carrier)
{
	if (carrier->precision > carrier->large_arg)
	{
		writezeros(carrier->precision - carrier->large_arg, carrier);
		ft_putnbr(arg, carrier);
		if (carrier->width > carrier->precision)
			writespaces(carrier->width - carrier->precision, carrier);
	}
	else
		aux_print_spaces(arg, carrier);
}

static void	if_minus_noprecision_d(int arg, t_format *carrier)
{
	if (carrier->width > 0)
	{
		if (carrier->width >= carrier->large_arg)
			aux_print_spaces(arg, carrier);
		else
			ft_putnbr(arg, carrier);
	}
	else
		ft_putnbr(arg, carrier);
}

void		if_minus_d(int arg, t_format *carrier)
{
	if (arg < 0)
		if_minus_neg_d(arg, carrier);
	else if (carrier->precision >= 0)
		if_minus_precision_d(arg, carrier);
	else
		if_minus_noprecision_d(arg, carrier);
}

static void	if_neg_precision_d(int arg, t_format *carrier)
{
	if (carrier->precision < carrier->large_arg)
		writespaces(carrier->width - carrier->large_arg, carrier);
	else if (carrier->width > carrier->precision)
		writespaces((carrier->width - carrier->precision) - 1, carrier);
	if (arg < 0)
	{
		arg = arg * (-1);
		ft_putchar('-', carrier);
	}
	writezeros(carrier->precision - carrier->large_arg + 1, carrier);
	print_int_min_pos(arg, carrier);
}

static void	if_neg_noprecision_d(int arg, t_format *carrier)
{
		writespaces(carrier->width - carrier->large_arg, carrier);
		print_int_min_neg(arg, carrier);
}

void		if_neg_d(int arg, t_format *carrier)
{
	if (carrier->precision >= 0)
		if_neg_precision_d(arg, carrier);
	else
		if_neg_noprecision_d(arg, carrier);
}

void	if_nominus_noneg_d(int arg, t_format *carrier)
{
	if (carrier->precision >= 0)
	{
		if (carrier->precision <= carrier->large_arg)
			writespaces(carrier->width - carrier->large_arg, carrier);
		else if (carrier->width > carrier->precision)
			writespaces(carrier->width - carrier->precision, carrier);
		writezeros(carrier->precision - carrier->large_arg, carrier);
	}
	else
		writespaces(carrier->width - carrier->large_arg, carrier);
	ft_putnbr(arg, carrier);
}

static void	if_minus_precision_x(char *arg, t_format *carrier)
{
	if (carrier->precision > carrier->large_arg)
	{
		writezeros(carrier->precision - carrier->large_arg, carrier);
		ft_puthex(arg, carrier);
		if (carrier->width > carrier->precision)
			writespaces(carrier->width - carrier->precision, carrier);
	}
	else
		aux_print_spaces_x(arg, carrier);
}

static void	if_minus_noprecision_x(char *arg, t_format *carrier)
{
	if (carrier->width > 0)
	{
		if (carrier->width >= carrier->large_arg)
			aux_print_spaces_x(arg, carrier);
		else
			ft_puthex(arg, carrier);
	}
	else
		ft_puthex(arg, carrier);
}

void		if_minus_x(char *arg, t_format *carrier)
{
	if (carrier->precision >= 0)
		if_minus_precision_x(arg, carrier);
	else
		if_minus_noprecision_x(arg, carrier);
}

void		if_nominus_noneg_x(char *arg, t_format *carrier)
{
	if (carrier->precision >= 0)
	{
		if (carrier->precision <= carrier->large_arg)
			writespaces(carrier->width - carrier->large_arg, carrier);
		else if (carrier->width > carrier->precision)
			writespaces(carrier->width - carrier->precision, carrier);
		writezeros(carrier->precision - carrier->large_arg, carrier);
	}
	else
		writespaces(carrier->width - carrier->large_arg, carrier);
	ft_puthex(arg, carrier);
}

void	jotdown_d(t_format *carrier)
{
	int		arg;

	flag(carrier->flagstr, 0, carrier);
	arg = va_arg(carrier->arguments, int);
	carrier->large_arg = ft_strlen(ft_itoa(arg));
	print_d(arg, carrier);
}

void	print_d(int arg, t_format *carrier)
{
	if (carrier->precision == 0 && arg == 0)
		writespaces(carrier->width, carrier);
	else if (arg < 0)
		if_neg_d(arg, carrier);
	else
		if_nominus_noneg_d(arg, carrier);
}

void	jotdown_x(t_format *carrier)
{
	char			*arg;
	unsigned long	aux;

	flag(carrier->flagstr, 0, carrier);
	aux = va_arg(carrier->arguments, unsigned int);
	arg = dec_to_hexa(aux);
	carrier->large_arg = ft_strlen(arg);
	print_x(arg, carrier);
}

void	print_x(char *arg, t_format *carrier)
{
	if (carrier->precision == 0 && arg[0] == '0' && arg[1] == '\0')
		writespaces(carrier->width, carrier);
	else
		if_nominus_noneg_x(arg, carrier);
}

void	jotdown_s(t_format *carrier)
{
	char	*arg;

	flag(carrier->flagstr, 0, carrier);
	arg = va_arg(carrier->arguments, char *);
	if (arg == NULL)
		arg = "(null)";
	carrier->large_arg = ft_strlen(arg);
	print_s(arg, carrier);
}

void	print_s(char *arg, t_format *carrier)
{
	if (carrier->precision >= carrier->large_arg || carrier->precision < 0)
		writespaces(carrier->width - carrier->large_arg, carrier);
	else if (carrier->precision >= 0)
		writespaces(carrier->width - carrier->precision, carrier);
	ft_putstr(arg, carrier);
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

char		*dec_to_hexa(unsigned long arg)
{
	static char		result[20];
	int				i;
	unsigned long	temp;

	i = 0;
	if (arg == 0)
		return ("0\0");
	while (arg != 0)
	{
		temp = arg % 16;
		result[i] = HEXALOWER[temp];
		i++;
		arg = arg / 16;
	}
	result[i] = '\0';
	return (invert_str(result));
}

static int	flagdot(int c, t_format *carrier)
{
	char *flag;

	flag = carrier->flagstr;
	carrier->dot = 1;
	carrier->pos_dot = c;
	c++;
	carrier->precision = 0;
	if (flag[c] == '-')
		carrier->precision = -1;
	if (flag[c] == '*')
		carrier->precision = va_arg(carrier->arguments, int);
	else if (ft_isdigit(flag[c]))
	{
		while (ft_isdigit(flag[c]))
			carrier->precision = (carrier->precision * 10) + (flag[c++] - 48);
	}
	c--;
	return (c);
}

void		flag(char *flag, int c, t_format *carrier)
{
	while (flag[c])
	{
		if (flag[c] == '.')
			c = flagdot(c, carrier);
		else if (flag[c] == '*' && carrier->dot == 0)
		{
			carrier->width = va_arg(carrier->arguments, int);
			if (carrier->width < 0)
				carrier->width = carrier->width * -1;
		}
		else if (ft_isdigit(flag[c]) && carrier->dot == 0)
		{
			while (ft_isdigit(flag[c]))
				carrier->width = (carrier->width * 10) + (flag[c++] - 48);
			c--;
		}
		c++;
	}
}

void	ft_putchar(int c, t_format *carrier)
{
	write(1, &c, 1);
	carrier->how_many++;
}

void	ft_putnbr(int nb, t_format *carrier)
{
	unsigned int	copy_nb;

	if (nb < 0)
	{
		ft_putchar('-', carrier);
		nb = (nb * (-1));
	}
	copy_nb = nb;
	if (copy_nb > 9)
		ft_putnbr(copy_nb / 10, carrier);
	ft_putchar(copy_nb % 10 + '0', carrier);
}

void	ft_putnbr_u(unsigned int nb, t_format *carrier)
{
	unsigned int	copy_nb;

	copy_nb = nb;
	if (nb > 9)
		ft_putnbr_u(copy_nb / 10, carrier);
	ft_putchar(copy_nb % 10 + '0', carrier);
}

void	ft_putstr(char *str, t_format *carrier)
{
	int		c;

	c = carrier->precision;
	if (!str)
		return ;
	if (c > 0)
	{
		while (*str && c-- > 0)
		{
			ft_putchar(*str, carrier);
			str++;
		}
	}
	else if (carrier->precision < 0)
	{
		while (*str)
		{
			ft_putchar(*str, carrier);
			str++;
		}
	}
}

void	ft_puthex(char *str, t_format *carrier)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_putchar(*str, carrier);
		str++;
	}
}

int		ft_isdigit(int c)
{
	return ((unsigned char)c >= '0' && (unsigned char)c <= '9');
}

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

char	*ft_itoa(int n)
{
	long	nbr;
	size_t	len;
	char	*str;

	nbr = n;
	len = (nbr > 0) ? 0 : 1;
	nbr = (nbr > 0) ? nbr : -nbr;
	while (n)
		n = len++ ? n / 10 : n / 10;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	while (nbr > 0)
	{
		*(str + len--) = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
	return (str);
}

char	*ft_itoa_u(unsigned int n)
{
	long	nbr;
	size_t	len;
	char	*str;

	nbr = n;
	len = (nbr > 0) ? 0 : 1;
	nbr = (nbr > 0) ? nbr : -nbr;
	while (n)
		n = len++ ? n / 10 : n / 10;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	while (nbr > 0)
	{
		*(str + len--) = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
	return (str);
}

void	print_int_min_pos(int arg, t_format *carrier)
{
	if (arg != -2147483648)
		ft_putnbr(arg, carrier);
	else
	{
		write(1, "2147483648", 10);
		carrier->how_many = carrier->how_many + 10;
	}
}

void	print_int_min_neg(int arg, t_format *carrier)
{
	if (arg != -2147483648)
		ft_putnbr(arg, carrier);
	else
	{
		write(1, "-2147483648", 11);
		carrier->how_many = carrier->how_many + 11;
	}
}

void	writespaces(int c, t_format *carrier)
{
	while (c-- > 0)
		ft_putchar(' ', carrier);
}

void	aux_print_spaces(int arg, t_format *carrier)
{
	ft_putnbr(arg, carrier);
	writespaces(carrier->width - carrier->large_arg, carrier);
}

void	aux_print_spaces_x(char *arg, t_format *carrier)
{
	ft_puthex(arg, carrier);
	writespaces(carrier->width - carrier->large_arg, carrier);
}

void	writespaces_s(t_format *carrier)
{
	int c;

	if (carrier->arg_null == 'y' && carrier->width > carrier->large_arg
						&& carrier->dot == 0)
		c = carrier->width - carrier->large_arg;
	else if (carrier->precision >= 0 && carrier->dot == 1
						&& carrier->precision < carrier->large_arg)
		c = carrier->width - carrier->precision;
	else if (carrier->arg_null == 'y' && carrier->large_arg > carrier->width
						&& carrier->dot == 0)
		c = 0;
	else
		c = carrier->width - carrier->large_arg;
	while (c-- > 0)
		ft_putchar(' ', carrier);
}

void	writezeros(int c, t_format *carrier)
{
	while (c-- > 0)
		ft_putchar('0', carrier);
}


static void	flags_init(t_format *carrier)
{
	carrier->flagstr[0] = *("");
	carrier->largeflag = 0;
	carrier->large_arg = 0;
	carrier->convers = ' ';
	carrier->percent = 0;
	carrier->dot = 0;
	carrier->pos_dot = 0;
	carrier->asterisk = 0;
	carrier->width = 0;
	carrier->precision = -1;
	carrier->code_zmpw = 0;
	carrier->arg_null = ' ';
}

static void	carrier_init(t_format *carrier)
{
	carrier->how_many = 0;
	flags_init(carrier);
}

/*
**	This ft_ have a double function:
**		1) Return the type of conversion: d,s,c,x...
**		2) Save the string-flag in t_format carrier->flagstr
**
**	The program always check the flags in this new string: it never
**	checks on the original string.
*/

static char	ft_look4format(const char *str, t_format *carrier)
{
	int		i;
	int		j;

	while (*str)
	{
		j = 0;
		carrier->largeflag++;
		i = carrier->largeflag;
		while (j <= 1)
		{
			if (str[i] != PRINTF_VALID_FORMATS[j])
				if (j++ == 1)
					carrier->flagstr[i - 1] = str[i];
			if (str[i] == PRINTF_VALID_FORMATS[j])
			{
				carrier->flagstr[i - 1] = '\0';
				return (str[i]);
			}
		}
	}
	return (str[i]);
}

static void	is_percent(const char **str, t_format *carrier)
{
	flags_init(carrier);
	carrier->convers = ft_look4format(*str, carrier);
	if (carrier->convers == 's')
		jotdown_s(carrier);
	else if (carrier->convers == 'd')
		jotdown_d(carrier);
	else if (carrier->convers == 'x')
		jotdown_x(carrier);
	*str = *str + carrier->largeflag;
}

int			ft_printf(const char *str, ...)
{
	t_format	carrier;

	if (!str || !*str)
		return (0);
	va_start(carrier.arguments, str);
	carrier_init(&carrier);
	while (*str != '\0')
	{
		if (*str == '%')
			is_percent(&str, &carrier);
		else
			ft_putchar(*str, &carrier);
		str++;
	}
	va_end(carrier.arguments);
	return (carrier.how_many);
}
