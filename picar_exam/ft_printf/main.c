#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

int
	ft_printf(char const *format, ...);

#ifndef REAL
# define F	r += ft_printf
#else
# define F	r += printf
#endif

int
	main(void)
{
	int	r;

	r = 0;
	F("Simple test\n");
	F("");
	F("--Format---");
	F("|line%d|\n",__LINE__);
	F("%d|line%d|", (int)NULL,__LINE__);
	F("%d|line%d|", 0,__LINE__);
	F("%d|line%d|", 42,__LINE__);
	F("%d|line%d|", 1,__LINE__);
	F("%d|line%d|", 5454,__LINE__);
	F("%d|line%d|", INT_MAX,__LINE__);
	F("%d|line%d|", INT_MIN,__LINE__);
	F("%d|line%d|", (int)2147483647,__LINE__);
	F("%d|line%d|", (int)2147483648,__LINE__);
	F("%d|line%d|", (int)-2147483648,__LINE__);
	F("%d|line%d|", (int)-2147483649,__LINE__);
	F("|line%d|\n",__LINE__);
	F("%x|line%d|", (unsigned int)NULL,__LINE__);
	F("%x|line%d|", 0,__LINE__);
	F("%x|line%d|", 42,__LINE__);
	F("%x|line%d|", 1,__LINE__);
	F("%x|line%d|", 5454,__LINE__);
	F("%x|line%d|", (int)2147483647,__LINE__);
	F("%x|line%d|", (int)2147483648,__LINE__);
	F("%x|line%d|", (int)-2147483648,__LINE__);
	F("%x|line%d|", (int)-2147483649,__LINE__);
	F("%s|line%d|", "",__LINE__);
	F("%s|line%d|", "toto",__LINE__);
	F("%s|line%d|", "wiurwuyrhwrywuier",__LINE__);
	F("%s|line%d|", NULL,__LINE__);
	F("-%s-%s-%s-%s-|line%d|\n", "", "toto", "wiurwuyrhwrywuier", NULL,__LINE__);
	F("\n--Mixed---|line%d|\n",__LINE__);
	F("%d%x%d%x%d%x%d%x|line%d|\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648,__LINE__);
	F("-%d-%x-%d-%x-%d-%x-%d-%x-|line%d|\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648,__LINE__);
	F("|line%d|\n",__LINE__);
	F("%s%s%s%s|line%d|\n", "", "toto", "wiurwuyrhwrywuier", NULL,__LINE__);
	F("-%s-%s-%s-%s-|line%d|\n", "", "toto", "wiurwuyrhwrywuier", NULL,__LINE__);
	F("--1 Flag--\n");
	F("d0w %0d %0d %0d %0d %0d %0d %0d %0d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d0w %0d %0d %0d %0d %0d %0d %0d %0d|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d4w %4d %4d %4d %4d %4d %4d %4d %4d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d4w %4d %4d %4d %4d %4d %4d %4d %4d|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d10w %10d %10d %10d %10d %10d %10d %10d %10d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d10w %10d %10d %10d %10d %10d %10d %10d %10d|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x0w %0x %0x %0x %0x %0x %0x %0x %0x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x0w %0x %0x %0x %0x %0x %0x %0x %0x|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x4w %4x %4x %4x %4x %4x %4x %4x %4x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x4w %4x %4x %4x %4x %4x %4x %4x %4x|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x10w %10x %10x %10x %10x %10x %10x %10x %10x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x10w %10x %10x %10x %10x %10x %10x %10x %10x|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("--2 Flags--\n");
	F("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("--Precision--\n");
	F("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("--Width--\n");
	F("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d|line%d|\n", 0, -42, -1, -4554, -2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("--Width and Precision--\n");
	F("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d|line%d|\n", 0, -20, -210, -4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d|line%d|\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x|line%d|\n", 0, -42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x|line%d|\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x|line%d|\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649,__LINE__);
	F("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`|line%d|\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL,__LINE__);
	F("jaja [%30.10d]|line%d|\n", -303030,__LINE__);
	F("jaja[%30.10s] [%.3s] [%.30s] [%20s] [%30.10d] [%30d %.10d] [%30.10d] |line%d|", "jaime que", "jaime", "jaime", "jaime", 30, 30 , 303030, -303030,__LINE__);
	F("jaja[%30.10s] [%.3s] [%.30s] [%20s] [%30.10d] [%30d %.10d] [%30.10d] [%5.0d] [%30.10x] [%30x] [%.10x] [%30.10x] [%5.0x] |line%d|", "jaime que", "jaime", "jaime", "jaime", 30, 30 , 303030, -303030, 0, 30, 30 , 303030, -303030, 0,__LINE__);
	F("[%6d], [%10.3s] |line%d|", (int)-2147483648, "",__LINE__);
	printf("written: %d\n", r);
//	system("leaks ft_printf");
}