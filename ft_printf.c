/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:38:01 by flogan            #+#    #+#             */
/*   Updated: 2019/10/16 18:38:29 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parser(char **format, t_arg *arg, va_list args, int *j)
{
	int i;

	i = 0;
	parser_width(format, arg, args, j);
	if (arg->type)
	{
		if (ft_strchr("diouxXp", arg->type))
			print_numbers(arg);
		else if (ft_strchr("s", arg->type))
			print_string(arg);
	}
	else if (!arg->s && (*format)[*j] && (arg->malloc = 1))
	{
		while ((*format)[*j + i] && (*format)[*j + i] != '%')
			i++;
		if (i)
			arg->s = ft_strsub(*format, *j, i);
		else if ((*format)[*j] == '%' && (++(*format)))
			arg->s = ft_strdup("%");
		print_numbers(arg);
		(*format) += i;
	}
	(*format) += *j;
	*j = 0;
}

void	print_char(t_arg *arg, va_list args)
{
	while (!arg->minus && arg->zero && (!arg->acc_flag && !arg->accuracy)
			&& arg->width > 1 && (--(arg->width)) && (++(arg->counter)))
		ft_putchar('0');
	while (!arg->minus && arg->width >= 0 && arg->width > 1 &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
	ft_putchar(va_arg(args, unsigned int));
	++(arg->counter);
	while (arg->minus && arg->width >= 0 && arg->width > 1 &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
}

void	print_string(t_arg *arg)
{
	int size;

	if (arg->s == NULL && (arg->malloc = 1))
		arg->s = ft_strdup("(null)");
	size = (arg->acc_flag && arg->accuracy < ft_strlen(arg->s)) ?
		arg->accuracy : ft_strlen(arg->s);
	while (!arg->minus && arg->zero && (!arg->acc_flag && !arg->accuracy)
			&& arg->width > size && (--(arg->width)) && (++(arg->counter)))
		ft_putchar('0');
	while (!arg->minus && arg->width > size &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
	write(1, arg->s, size);
	arg->counter += size;
	while (arg->minus && arg->width > size &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
}

int		ft_printf(char *str, ...)
{
	int			j;
	long long	counter;
	va_list		args;
	t_arg		array;

	if (!ft_strcmp(str, "%"))
		return (0);
	j = 0;
	counter = 0;
	ft_bzero((void*)&array, sizeof(array));
	va_start(args, str);
	while (str[j])
	{
		ft_bzero((void*)&array, sizeof(array));
		(str[j] && str[j] == '%' && str[j + 1] != '%' && str[j + 1] != '\0') ?
			parser(&str, &array, args, &j) : parse_string(&str, &j, &array);
		counter += array.counter;
		if (array.malloc)
			ft_strdel(&array.s);
	}
	va_end(args);
	return (counter);
}

int main(void)
{
	int			i = 2147483647;
	long		l = 2147483647;
	long long	ll = 9223372036854775807;
	char		c = 0;
	intmax_t	im = 9223372036854775807;

		ft_printf("\n");
		ft_printf("%%\n");
		ft_printf("%d\n", 42);
		ft_printf("%d%d\n", 42, 41);
		ft_printf("%d%d%d\n", 42, 43, 44);
		ft_printf("%ld\n", l);
		ft_printf("%lld\n", ll);
		ft_printf("%x %X %p %20.15d\n", 505, 505, &ll, 54321);
		ft_printf("%-10d % d %+d %010d %hhd\n", 3, 3, 3, 1, c);
		ft_printf("%jd %zd %u %o %#08x\n", im, (size_t)i, i, 40, 42);
		ft_printf("%x %#X %S %s%s\n", 1000, 1000, L"ݗݜशব", "test", "test2");
		ft_printf("%s%s%s\n", "test", "test", "test");
		ft_printf("%C\n", 15000);

//    printf("%d", printf("%hhld", 128));
//    printf("\n");
//    printf("%d", ft_printf("%hhld", 128));
//    printf("\n\n");
//
//    printf("%d", printf("%zhd", 4294967296));
//    printf("\n");
//    printf("%d", ft_printf("%zhd", 4294967296));
//    printf("\n\n");
//
//    printf("%d", printf("%hu", 4294967296));
//    printf("\n");
//    printf("%d", ft_printf("%hu", 4294967296));
//    printf("\n\n");
//
//    printf("%d", printf("%D", -4294967295));
//    printf("\n");
//    printf("%d", ft_printf("%D", -4294967295));
//    printf("\n\n");
//
//    printf("%d", printf("%05c", 42));
//    printf("\n");
//    printf("%d", ft_printf("%05c", 42));
//    printf("\n\n");
//
//    printf("%d", printf("%010s is a string", "this"));
//    printf("\n");
//    printf("%d", ft_printf("%010s is a string", "this"));
//    printf("\n\n");
//
//    printf("%d", printf("%ll#x", 9223372036854775807));
//    printf("\n");
//    printf("%d", ft_printf("%ll#x", 9223372036854775807));
//    printf("\n\n");
//
//    printf("%d", printf("%"));
//    printf("\n");
//    printf("%d", ft_printf("%"));
//    printf("\n\n");
//
//    printf("%d", printf("% hZ%"));
//    printf("\n");
//    printf("%d", ft_printf("% hZ%"));
//    printf("\n\n");
//
//    printf("%d", printf("%Z"));
//    printf("\n");
//    printf("%d", ft_printf("%Z"));
//    printf("\n\n");
    //printf("%C\n", 15000);
//    //int c = (int)a.hash;
//    printf("%p\n", (&c)++));
    //printf("%d\n", b);
    //printf("%d\n", c >> 1);
//    int a = 6;
//    int *b = &a;
//
//    printf("%llx\n", (long long)&b);
//    printf("%p", &b);
//    printf("%#X",17);
//
//        printf("qwerty%%%\n%2.19d%d\n", 4588,13);
//        ft_printf("qwerty%%%\n%2.19d%d", 4588, 13);
//
//	ft_printf("%X", 1352804640);
//	printf("\n%X\n", 1352804640);
//	printf("%d\n", 4294967297);
//    printf("dddd%rt2.19d%d\n", 4588, 13);
//    ft_printf("dddd%tr2.19d%d", 4588, 13);


//	printf("%.0p, %.p\n", 0, 0);
//	printf("%d",ft_printf("%.0p, %.p", 0, 0));
//	printf("\n\n");
//
//	printf("%p\n", 0);
//	printf("%d",ft_printf("%p", 0));
//	printf("\n\n");
//
//	char j = 123;
//	printf("%p\n", &j);
//	printf("%d",ft_printf("%p", &j));
//	printf("\n\n");
//
//	printf("%#x\n", 42);
//	printf("%d",ft_printf("%#x", 42));
//	printf("\n\n");
//
//	char *i = "qwerty";
//	printf("%p\n", &i);
//	printf("%d",ft_printf("%p", &i));
//	printf("\n\n");
//
//	printf("%.4s\n", "42");
//	printf("%d",ft_printf("%.4s", "42"));
//	printf("\n\n");
//
//	printf("%s %d %% %x\n", "bonjour ", 42, 42);
//	printf("%d",ft_printf("%s %d %% %x", "bonjour ", 42, 42));
//	printf("\n\n");
//
//	printf("{% 03d}\n", 0);
//	printf("%d",ft_printf("{% 03d}", 0));
//	printf("\n\n");
//
//	printf("%\n");
//	printf("%d",ft_printf("%"));
//	printf("\n\n");
//
//	printf("%#5c\n", 42);
//	printf("%d",ft_printf("%#5c", 42));
//	printf("\n\n");
//
//	printf("%-5c\n", 42);
//	printf("%d",ft_printf("%-5c", 42));
//	printf("\n\n");
//
//    printf("%+u\n", 42);
//
//	printf("%s %s\n", NULL, "string");
//	printf("%d",ft_printf("%s %s", NULL, "string"));
//	printf("\n\n");
//
//	printf("@moulitest: %s\n", NULL);
//	printf("%d",ft_printf("@moulitest: %s", NULL));
//	printf("\n\n");
//
//	printf("%-10s is a string\n", "this");
//	printf("%d",ft_printf("%-10s is a string", "this"));
//	printf("\n\n");
//
//	printf("%-5%\n");
//	printf("%d",ft_printf("%-5%"));
//	printf("\n\n");
//
//	printf("%-.2s Js a string\n", "");
//	printf("%d",ft_printf("%-.2s Js a string", ""));
//	printf("\n\n");
//
//	printf("%-5.2s is a string\n", "this");
//	printf("%d",ft_printf("%-5.2s is a string", "this"));
//	printf("\n\n");
//
//	printf("%-.2s IS a string\n", "this");
//	printf("%d",ft_printf("%-.2s IS a string", "this"));
//	printf("\n\n");
//
//	printf("%5.2s is a string\n", "");
//	printf("%d",ft_printf("%5.2s is a string", ""));
//	printf("\n\n");
//
//	printf("%.2s is a string\n", "");
//	printf("%d",ft_printf("%.2s is a string", ""));
//	printf("\n\n");
//
//	printf("%10s is a string\n", "this");
//	printf("%d",ft_printf("%10s is a string", "this"));
//	printf("\n\n");
//
//	printf("%5.2s is a string\n", "this");
//	printf("%d",ft_printf("%5.2s is a string", "this"));
//	printf("\n\n");
//
//	printf("%.2s is a string\n", "this");
//	printf("%d",ft_printf("%.2s is a string", "this"));
//	printf("\n\n");
//
//	printf("%s\n", "abc");
//	printf("%d",ft_printf("%s", "abc"));
//	printf("\n\n");
//
//	printf("% c\n", 0);
//	printf("%d",ft_printf("% c", 0));
//	printf("\n\n");
//
//	printf("%2c\n", 0);
//	printf("%d",ft_printf("%2c", 0));
//	printf("\n\n");
//
//	printf("%.2c\n", NULL);
//	printf("%d",ft_printf("%.2c", NULL));
//	printf("\n\n");
//
//	printf("%c\n", 42);
//	printf("%d",ft_printf("%c", 42));
//	printf("\n\n");
//
//	printf("@moulitest: %5.o %5.0o\n", 0, 0);
//	printf("%d",ft_printf("@moulitest: %5.o %5.0o", 0, 0));
//	printf("\n\n");
//
//    printf("%d",printf("@moulitesT: %5.d %5.0d", 0, 0));
//    printf("\n");
//	printf("%d",ft_printf("@moulitest: %5.d %5.0d", 0, 0));
//	printf("\n\n");
//
//    printf("%d",printf("@moulitest: %.d %.0d", 0, 0));
//    printf("\n");
//	printf("%d",ft_printf("@moulitest: %.d %.0d", 0, 0));
//	printf("\n\n");
//
//    printf("%d",printf("%05d", -42));
//    printf("\n");
//	printf("%d",ft_printf("%05d", -42));
//	printf("\n\n");
//
//    printf("%d",printf("%0+5d", 42));
//    printf("\n");
//	printf("%d",ft_printf("%0+5d", 42));
//	printf("\n\n");
//
//    printf("%d",printf("% d", 42));
//    printf("\n");
//	printf("%d",ft_printf("% d", 42));
//	printf("\n\n");
////______________________________________________________________________
//
//	printf("@moulitest: %.o %.0o\n", 0, 0);
//	printf("%d",ft_printf("@moulitest: %.o %.0o", 0, 0));
//	printf("\n\n");
//
//	printf("@moulitest: %#.o %#.0o\n", 0, 0);
//	printf("%d",ft_printf("@moulitest: %#.o %#.0o", 0, 0));
//	printf("\n\n");
//
//	printf("%#6o\n", 2500);
//	printf("%d",ft_printf("%#6o", 2500));
//	printf("\n\n");
//
//	printf("%o\n", 40);
//	printf("%d",ft_printf("%o", 40));
//	printf("\n\n");
//
//	printf("@moulitest: %5.x %5.0x\n", 0, 0);
//	printf("%d",ft_printf("@moulitest: %5.x %5.0x", 0, 0));
//	printf("\n\n");
//
//	printf("%#-08x\n", 42);
//	printf("%d",ft_printf("%#-08x", 42));
//	printf("\n\n");
//
//	printf("%x\n", 0);
//	printf("%d",ft_printf("%x", 0));
//	printf("\n\n");
//
//	printf("@moulitest: %#.x %#.0x\n", 0, 0);
//	printf("%d",ft_printf("@moulitest: %#.x %#.0x", 0, 0));
//	printf("\n\n");
//
//	printf("%#-08x\n", 42);
//	printf("%d",ft_printf("%#-08x", 42));
//	printf("\n\n");
//
//	printf("%#x\n", 0);
//	printf("%d",ft_printf("%#x", 0));
//	printf("\n\n");
//
//	printf("%010x\n", 542);
//	printf("%d",ft_printf("%010x", 542));
//	printf("\n\n");
//
//	printf("%#x\n", 42);
//	printf("%d",ft_printf("%#x", 42));
//	printf("\n\n");
//
//	printf("%#llx\n", 9223372036854775807);
//	printf("%d",ft_printf("%#llx", 9223372036854775807));
//	printf("\n\n");
//
//	printf("%-5%\n");
//	printf("%d",ft_printf("%-5%"));
//	printf("\n\n");
//
//	printf("%   %\n", "test");
//	printf("%d",ft_printf("%   %", "test"));
//	printf("\n\n");
//
//	printf("%-10x\n", 42);
//	printf("%d",ft_printf("%-10x", 42));
//	printf("\n\n");
//
//	printf("%-15x\n", 542);
//	printf("%d",ft_printf("%-15x", 542));
//	printf("\n\n");
//
//
//    printf("%d\n", 4588,13);
//    ft_printf("%d", 4588);
//    printf("\n");
//    printf("%32.19d%d\n", -4588,13);
//    ft_printf("%32.19d%d", -4588, 13);
//    printf("\n");
//    printf("%32.4d%d\n", -4588,13);
//    ft_printf("%32.4d%d", -4588, 13);
//    printf("\n");
//    printf("%32.4d%d\n", 4588,13);
//    ft_printf("%32.4d%d", 4588, 13);
//    printf("\n");
//    printf("%1.4d%d\n", 4588,13);
//    ft_printf("%1.4d%d", 4588, 13);
//    printf("\n");
//
//    printf("%2.19u%d\n", 4588,13);
//    ft_printf("%2.19u%d", 4588, 13);
//    printf("\n");
//    printf("%32.19u%d\n", 4588,13);
//    ft_printf("%32.19u%d", 4588, 13);
//    printf("\n");
//    printf("%32.19u%d\n", -4588,13);
//    ft_printf("%32.19u%d", -4588, 13);
//    printf("\n");
//    printf("%32.4u%d\n", -4588,13);
//    ft_printf("%32.4u%d", -4588, 13);
//    printf("\n");
//    printf("%32.4u%d\n", 4588,13);
//    ft_printf("%32.4u%d", 4588, 13);
//    printf("\n");
//    printf("%1.4u%d\n", 4588,13);
//    ft_printf("%1.4u%d", 4588, 13);
//    printf("\n");
//
//    printf("%2.19i%d\n", 4588,13);
//    ft_printf("%2.19i%d", 4588, 13);
//    printf("\n");
//    printf("%32.19i%d\n", 4588,13);
//    ft_printf("%32.19i%d", 4588, 13);
//    printf("\n");
//    printf("%32.19i%d\n", -4588,13);
//    ft_printf("%32.19i%d", -4588, 13);
//    printf("\n");
//    printf("%32.4i%d\n", -4588,13);
//    ft_printf("%32.4i%d", -4588, 13);
//    printf("\n");
//    printf("%32.4i%d\n", 4588,13);
//    ft_printf("%32.4i%d", 4588, 13);
//    printf("\n");
//    printf("%1.4i%d\n", 4588,13);
//    ft_printf("%1.4i%d", 4588, 13);
//    printf("\n");
//
//    printf("%2.19x%d\n", 4588,13);
//    ft_printf("%2.19x%d", 4588, 13);
//    printf("\n");
//    printf("%32.19x%d\n", 4588,13);
//    ft_printf("%32.19x%d", 4588, 13);
//    printf("\n");
//    printf("%32.19x%d\n", -4588,13);
//    ft_printf("%32.19x%d", -4588, 13);
//    printf("\n");
//    printf("%32.4x%d\n", -4588,13);
//    ft_printf("%32.4x%d", -4588, 13);
//    printf("\n");
//    printf("%32.4x%d\n", 4588,13);
//    ft_printf("%32.4x%d", 4588, 13);
//    printf("\n");
//    printf("%1.4x%d\n", 4588,13);
//    ft_printf("%1.4x%d", 4588, 13);
//    printf("\n");
//
//    printf("%+2.19i%d\n", 4588,13);
//    ft_printf("%+2.19i%d", 4588, 13);
//    printf("\n");
//    printf("%+32.19i%d\n", 4588,13);
//    ft_printf("%+32.19i%d", 4588, 13);
//    printf("\n");
//    printf("%+32.19i%d\n", -4588,13);
//    ft_printf("%+32.19i%d", -4588, 13);
//    printf("\n");
//    printf("%+32.4i%d\n", -4588,13);
//    ft_printf("%+32.4i%d", -4588, 13);
//    printf("\n");
//    printf("%+32.4i%d\n", 4588,13);
//    ft_printf("%+32.4i%d", 4588, 13);
//    printf("\n");
//    printf("%+1.4i%d\n", 4588,13);
//    ft_printf("%+1.4i%d", 4588, 13);
//    printf("\n");
//
//    printf("% 2.19i%d\n", 4588,13);
//    ft_printf("% 2.19i%d", 4588, 13);
//    printf("\n");
//    printf("% 32.19i%d\n", 4588,13);
//    ft_printf("% 32.19i%d", 4588, 13);
//    printf("\n");
//    printf("% 32.19i%d\n", -4588,13);
//    ft_printf("% 32.19i%d", -4588, 13);
//    printf("\n");
//    printf("% 32.4i%d\n", -4588,13);
//    ft_printf("% 32.4i%d", -4588, 13);
//    printf("\n");
//    printf("% 32.4i%d\n", 4588,13);
//    ft_printf("% 32.4i%d", 4588, 13);
//    printf("\n");
//    printf("% 1.4i%d\n", 4588,13);
//    ft_printf("% 1.4i%d", 4588, 13);
//    printf("\n");
//
//    printf("%-2.19i%d\n", 4588,13);
//    ft_printf("%-2.19i%d", 4588, 13);
//    printf("\n");
//    printf("%-32.19i%d\n", 4588,13);
//    ft_printf("%-32.19i%d", 4588, 13);
//    printf("\n");
//    printf("%-32.19i%d\n", -4588,13);
//    ft_printf("%-32.19i%d", -4588, 13);
//    printf("\n");
//    printf("%-32.4i%d\n", -4588,13);
//    ft_printf("%-32.4i%d", -4588, 13);
//    printf("\n");
//    printf("%-32.4i%d\n", 4588,13);
//    ft_printf("%-32.4i%d", 4588, 13);
//    printf("\n");
//    printf("%-1.4i%d\n", 4588,13);
//    ft_printf("%-1.4i%d", 4588, 13);
//    printf("\n");
//
//    printf("%#2.19x%d\n", 4588,13);
//    ft_printf("%#2.19x%d", 4588, 13);
//    printf("\n");
//    printf("%#32.19x%d\n", 4588,13);
//    ft_printf("%#32.19x%d", 4588, 13);
//    printf("\n");
//    printf("%#32.19x%d\n", -4588,13);
//    ft_printf("%#32.19x%d", -4588, 13);
//    printf("\n");
//    printf("%#32.4x%d\n", -4588,13);
//    ft_printf("%#32.4x%d", -4588, 13);
//    printf("\n");
//    printf("%#32.4x%d\n", 4588,13);
//    ft_printf("%#32.4x%d", 4588, 13);
//    printf("\n");
//    printf("%#1.4x%d\n", 4588,13);
//    ft_printf("%#1.4x%d", 4588, 13);
//    printf("\n");
//
//    printf("%02.19i%d\n", 4588,13);
//    ft_printf("%02.19i%d", 4588, 13);
//    printf("\n");
//    printf("%032.19i%d\n", 4588,13);
//    ft_printf("%032.19i%d", 4588, 13);
//    printf("\n");
//    printf("%032.19i%d\n", -4588,13);
//    ft_printf("%032.19i%d", -4588, 13);
//    printf("\n");
//    printf("%032.4i%d\n", -4588,13);
//    ft_printf("%032.4i%d", -4588, 13);
//    printf("\n");
//    printf("%032.4i%d\n", 4588,13);
//    ft_printf("%032.4i%d", 4588, 13);
//    printf("\n");
//    printf("%01.4i%d\n", 4588,13);
//    ft_printf("%01.4i%d", 4588, 13);
//    printf("\n");
//
//    printf("%+-2.19i%d\n", 4588,13);
//    ft_printf("%+-2.19i%d", 4588, 13);
//    printf("\n");
//    printf("%+-32.19i%d\n", 4588,13);
//    ft_printf("%+-32.19i%d", 4588, 13);
//    printf("\n");
//    printf("%+-32.19i%d\n", -4588,13);
//    ft_printf("%+-32.19i%d", -4588, 13);
//    printf("\n");
//    printf("%+-32.4i%d\n", -4588,13);
//    ft_printf("%+-32.4i%d", -4588, 13);
//    printf("\n");
//    printf("%+-32.4i%d\n", 4588,13);
//    ft_printf("%+-32.4i%d", 4588, 13);
//    printf("\n");
//    printf("%+-1.4i%d\n", 4588,13);
//    ft_printf("%+-1.4i%d", 4588, 13);
//    printf("\n");
//
//    printf("% -2.19i%d\n", 4588,13);
//    ft_printf("% -2.19i%d", 4588, 13);
//    printf("\n");
//    printf("% -32.19i%d\n", 4588,13);
//    ft_printf("% -32.19i%d", 4588, 13);
//    printf("\n");
//    printf("% -32.19i%d\n", -4588,13);
//    ft_printf("% -32.19i%d", -4588, 13);
//    printf("\n");
//    printf("% -32.4i%d\n", -4588,13);
//    ft_printf("% -32.4i%d", -4588, 13);
//    printf("\n");
//    printf("% -32.4i%d\n", 4588,13);
//    ft_printf("% -32.4i%d", 4588, 13);
//    printf("\n");
//    printf("% -1.4i%d\n", 4588,13);
//    ft_printf("% -1.4i%d", 4588, 13);
//    printf("\n");
//
//    printf("%+02.19i%d\n", 4588,13);
//    ft_printf("%+02.19i%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19i%d\n", 4588,13);
//    ft_printf("%+032.19i%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19i%d\n", -4588,13);
//    ft_printf("%+032.19i%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4i%d\n", -4588,13);
//    ft_printf("%+032.4i%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4i%d\n", 4588,13);
//    ft_printf("%+032.4i%d", 4588, 13);
//    printf("\n");
//    printf("%+01.4i%d\n", 4588,13);
//    ft_printf("%+01.4i%d", 4588, 13);
//    printf("\n");
//
//    printf("%0#2.19x%d\n", 4588,13);
//    ft_printf("%0#2.19x%d", 4588, 13);
//    printf("\n");
//    printf("%0#32.19x%d\n", 4588,13);
//    ft_printf("%0#32.19x%d", 4588, 13);
//    printf("\n");
//    printf("%0#32.19x%d\n", -4588,13);
//    ft_printf("%0#32.19x%d", -4588, 13);
//    printf("\n");
//    printf("%0#32.4x%d\n", -4588,13);
//    ft_printf("%0#32.4x%d", -4588, 13);
//    printf("\n");
//    printf("%0#32.4x%d\n", 4588,13);
//    ft_printf("%0#32.4x%d", 4588, 13);
//    printf("\n");
//    printf("%0#1.4x%d\n", 4588,13);
//    ft_printf("%0#1.4x%d", 4588, 13);
//    printf("\n");
//
//    printf("%+02.19ld%d\n", 4588,13);
//    ft_printf("%+02.19ld%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19ld%d\n", 4588,13);
//    ft_printf("%+032.19ld%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19ld%d\n", -4588,13);
//    ft_printf("%+032.19ld%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4ld%d\n", -4588,13);
//    ft_printf("%+032.4ld%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4ld%d\n", 4588,13);
//    ft_printf("%+032.4ld%d", 4588, 13);
//    printf("\n");
//    printf("%+01.4ld%d\n", 4588,13);
//    ft_printf("%+01.4ld%d", 4588, 13);
//    printf("\n");
//
//    printf("%+02.19hhd%d\n", 4588,13);
//    ft_printf("%+02.19hhd%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19hhd%d\n", 4588,13);
//    ft_printf("%+032.19hhd%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19hhd%d\n", -4588,13);
//    ft_printf("%+032.19hhd%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4hhd%d\n", -4588,13);
//    ft_printf("%+032.4hhd%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4hhd%d\n", 4588,13);
//    ft_printf("%+032.4hhd%d", 4588, 13);
//    printf("\n");
//    printf("%+01.4hhd%d\n", 4588,13);
//    ft_printf("%+01.4hhd%d", 4588, 13);
//    printf("\n");
//
//    printf("%+02.19hd%d\n", 4588,13);
//    ft_printf("%+02.19hd%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19hd%d\n", 4588,13);
//    ft_printf("%+032.19hd%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19hd%d\n", -4588,13);
//    ft_printf("%+032.19hd%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4hd%d\n", -4588,13);
//    ft_printf("%+032.4hd%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4hd%d\n", 4588,13);
//    ft_printf("%+032.4hd%d", 4588, 13);
//    printf("\n");
//    printf("%+01.4hd%d\n", 4588,13);
//    ft_printf("%+01.4hd%d", 4588, 13);
//    printf("\n");
//
//    printf("%+02.19lld%d\n", 4588,13);
//    ft_printf("%+02.19lld%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19lld%d\n", 4588,13);
//    ft_printf("%+032.19lld%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19lld%d\n", -4588,13);
//    ft_printf("%+032.19lld%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4lld%d\n", -4588,13);
//    ft_printf("%+032.4lld%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4lld%d\n", 4588,13);
//    ft_printf("%+032.4lld%d", 4588, 13);
//    printf("\n");
//    printf("%+01.4lld%d\n", 4588,13);
//    ft_printf("%+01.4lld%d", 4588, 13);
//    printf("\n");
//
//    printf("%+02.19jd%d\n", 4588,13);
//    ft_printf("%+02.19jd%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19jd%d\n", 4588,13);
//    ft_printf("%+032.19jd%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19jd%d\n", -4588,13);
//    ft_printf("%+032.19jd%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4jd%d\n", -4588,13);
//    ft_printf("%+032.4jd%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4jd%d\n", 4588,13);
//    ft_printf("%+032.4jd%d", 4588, 13);
//    printf("\n");
//    printf("%+01.4jd%d\n", 4588,13);
//    ft_printf("%+01.4jd%d", 4588, 13);
//    printf("\n");
//
//    printf("%+02.19zd%d\n", 4588,13);
//    ft_printf("%+02.19zd%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19zd%d\n", 4588,13);
//    ft_printf("%+032.19zd%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19zd%d\n", -4588,13);
//    ft_printf("%+032.19zd%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4zd%d\n", -4588,13);
//    ft_printf("%+032.4zd%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4zd%d\n", 4588,13);
//    ft_printf("%+032.4zd%d", 4588, 13);
//    printf("\n");
//    printf("%+01.4zd%d\n", 4588,13);
//    ft_printf("%+01.4zd%d", 4588, 13);
//    printf("\n");
//
//    printf("%+02.19td%d\n", 4588,13);
//    ft_printf("%+02.19td%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19td%d\n", 4588,13);
//    ft_printf("%+032.19td%d", 4588, 13);
//    printf("\n");
//    printf("%+032.19td%d\n", -4588,13);
//    ft_printf("%+032.19td%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4td%d\n", -4588,13);
//    ft_printf("%+032.4td%d", -4588, 13);
//    printf("\n");
//    printf("%+032.4td%d\n", 4588,13);
//    ft_printf("%+032.4td%d", 4588, 13);
//    printf("\n");
//    printf("%+01.4td%d\n", 4588,13);
//    ft_printf("%+01.4td%d", 4588, 13);
//    printf("\n");
//
//    printf("%+ -#02.19td%d\n", 4588,13);
//    ft_printf("%+ -#02.19td%d", 4588, 13);
//    printf("\n");
//    printf("%+ -#032.19td%d\n", 4588,13);
//    ft_printf("%+ -#032.19td%d", 4588, 13);
//    printf("\n");
//    printf("%+ -#032.19td%d\n", -4588,13);
//    ft_printf("%+ -#032.19td%d", -4588, 13);
//    printf("\n");
//    printf("%+ -#032.4td%d\n", -4588,13);
//    ft_printf("%+ -#032.4td%d", -4588, 13);
//    printf("\n");
//    printf("%+ -#032.4td%d\n", 4588,13);
//    ft_printf("%+ -#032.4td%d", 4588, 13);
//    printf("\n");
//    printf("%+ -#01.4td%d\n", 4588,13);
//    ft_printf("%+ -#01.4td%d", 4588, 13);
//    printf("\n\n");
//
//    printf("%+d", 0);
//    printf("\n");
//    ft_printf("%+d", 0);
//    printf("\n\n");
//
//    printf("%-5d", 42);
//    printf("\n");
//    ft_printf("%-5d", 42);
//    printf("\n\n");
//
//    printf("%-05d", 42);
//    printf("\n");
//    ft_printf("%-05d", 42);
//    printf("\n\n");
//
//    printf("%-5d", -42);
//    printf("\n");
//    ft_printf("%-5d", -42);
//    printf("\n\n");
//
//    printf("%d",printf("%4.15d", 42));
//    printf("\n");
//    printf("%d",ft_printf("%4.15d", 42));
//    printf("\n\n");
//
//    printf("%d",printf("%.10d", 4242));
//    printf("\n");
//    printf("%d",ft_printf("%.10d", 4242));
//    printf("\n\n");
//
//    printf("%d",printf("%03.2d", 0));
//    printf("\n");
//    printf("%d",ft_printf("%03.2d", 0));
//    printf("\n\n");
//
//    printf("%d",printf("%#6o", 2500));
//    printf("\n");
//    printf("%d",ft_printf("%#6o", 2500));
//    printf("\n\n");
//
//    printf("%d",printf("%-#6o", 2500));
//    printf("\n");
//    printf("%d",ft_printf("%-#6o", 2500));
//    printf("\n\n");
//
//    printf("%d",printf("% u", 4294967295));
//    printf("\n");
//    printf("%d",ft_printf("% u", 4294967295));
//    printf("\n\n");
//
//    printf("%d",printf("%#x", 42));
//    printf("\n");
//    printf("%d",ft_printf("%#x", 42));
//    printf("\n\n");
//
//    printf("%d",printf("%#x", 0));
//    printf("\n");
//    printf("%d",ft_printf("%#x", 0));
//    printf("\n\n");
//
//    printf("%d",printf("%#x", 0));
//    printf("\n");
//    printf("%d",ft_printf("%#x", 0));
//    printf("\n\n");
//
//    printf("%d",printf("%.0%"));
//    printf("\n");
//    printf("%d",ft_printf("%.0%"));
//    printf("\n\n");
//
//    printf("%d",printf("%p", 0));
//    printf("\n");
//    printf("%d",ft_printf("%p", 0));
//    printf("\n\n");
//
//    printf("%d",printf("%#o", 0));
//    printf("\n");
//    printf("%d",ft_printf("%#o", 0));
//    printf("\n\n");
//
//    printf("%d",printf("@moulitest: %#.o %#.o", 0, 0));
//    printf("\n");
//    printf("%d",ft_printf("@moulitest: %#.o %#.0o", 0, 0));
//    printf("\n\n");
//
//    printf("%d",printf("%#o", 0));
//    printf("\n");
//    printf("%d",ft_printf("%#o", 0));
//    printf("\n\n");
//
//    printf("%d",printf("% d", 42));
//    printf("\n");
//    printf("%d",ft_printf("% d", 42));
//    printf("\n\n");
//
//    printf("%d",printf("{% 03d}", 0));
//    printf("\n");
//    printf("%d",ft_printf("{% 03d}", 0));
//    printf("\n\n");
//
//    printf("%d",printf("% 10.5d", 4242));
//    printf("\n");
//    printf("%d",ft_printf("% 10.5d", 4242));
//    printf("\n\n");
//
//    printf("%d",printf("%#.3o", 1));
//    printf("\n");
//    printf("%d",ft_printf("%#.3o", 1));
//    printf("\n\n");
//
//    printf("%d",printf("%*.*d", 0, 3, 0));
//    printf("\n");
//    printf("%d",ft_printf("%*.*d", 0, 3, 0));
//    printf("\n\n");
//
//    printf("%d",printf("{%*3d}", 5, 0));
//    printf("\n");
//    printf("%d",ft_printf("{%*3d}", 5, 0));
//    printf("\n\n");
//
//    printf("%d",printf("%   %", "test"));
//    printf("\n");
//    printf("%d",ft_printf("%   %", "test"));
//    printf("\n\n");
//
//
//    printf("%d",printf("%   %", "test"));
//    printf("\n");
//    printf("%d",ft_printf("%   %", "test"));
//    printf("\n\n");
    return (0);
}
