/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:38:01 by flogan            #+#    #+#             */
/*   Updated: 2019/10/16 20:49:28 by flogan           ###   ########.fr       */
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
	while (!arg->minus && arg->width > 1 &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
	ft_putchar(va_arg(args, unsigned int));
	++(arg->counter);
	while (arg->minus && arg->width > 1 &&
			arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
}

void	print_string(t_arg *arg)
{
	unsigned int size;

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
