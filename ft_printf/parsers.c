/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:03:42 by flogan            #+#    #+#             */
/*   Updated: 2019/10/21 22:45:24 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    print_zero(long len, char chr)
{
    long i;

    i = 0;
    char *ptr;
    ptr = malloc(sizeof(char) * (len + 1));
    while (i < len)
        ptr[i++] = chr;
    write (1, ptr, len);
    free(ptr);
}

void	apendix_print_numbers(t_arg *arg, unsigned int *size, char *sign,
		int *hash)
{
    long len;

    len = ft_strlen(arg->s);
	if (arg->sign && (++(*size)))
		*sign = '-';
	else if (!arg->sign && arg->plus && arg->type && ft_strchr("difFeEgG", arg->type)  && !(arg->acc_flag && !ft_strcmp(arg->s, "0") && arg->accuracy == 0 && arg->type != 'f') && (++(*size)))
		*sign = '+';
	if (arg->type == 'p')
	    *hash = 1;
	*size += *hash += (*hash && arg->hash && ft_strchr("xXp", arg->type));
    if (!*sign && arg->type == 'f' && arg->space)
    {
        ft_putchar(' ');
        arg->width--;
    }
	if (*sign && arg->type == 'f' && arg->zero)
	{
		ft_putchar(*sign);
		arg->sign = 1;
		*sign = 0;
	}
	if (arg->type == 'o' && *hash && arg->accuracy > len)
    {
        arg->counter--;
        arg->width++;
    }
	//____________________________________________
//	while (!arg->minus && arg->zero && arg->type == 'f' && arg->width > ft_strlen(arg->s) + arg->sign && (--(arg->width)) && (++(arg->counter)))
//		ft_putchar('0');
    if (!arg->minus && arg->zero && arg->type == 'f' && arg->width > len + arg->sign)
    {
        print_zero(arg->width - (len + arg->sign), '0');
        arg->width -= (len + arg->sign);
        arg->counter += (len + arg->sign);
    }
    //__________________________________________-
	arg->counter += *size += (arg->acc_flag && arg->accuracy > len) ? arg->accuracy : len;
	if ((arg->space && arg->type && ft_strchr("dieEgG", arg->type) && *sign == 0 && (!arg->width || arg->width > len|| ft_strchr("di", arg->type)) && (++(arg->counter)) && (*size)++))
		ft_putchar(' ');
	//_______________________
	while ((arg->type != 'f' || (!arg->zero && arg->type == 'f')) && !arg->minus && (!arg->zero || (arg->width > arg->accuracy && arg->acc_flag)) && arg->width > *size && arg->width-- && (++(arg->counter)))
		ft_putchar(' ');
//    if ((arg->type != 'f' || (!arg->zero && arg->type == 'f')) && !arg->minus && (!arg->zero || (arg->width > arg->accuracy && arg->acc_flag)) && arg->width > *size)
//    {
//        print_zero(arg->width - *size, ' ');
//        arg->width -= *size;
//        arg->counter += *size;
//    }
	//_____________________________
	if (*hash && arg->type == 'o' && (!arg->accuracy || arg->accuracy-- ))
		ft_putchar('0');
    else if (*hash && ((arg->type == 'x' && ft_strcmp(arg->s, "0")) || arg->type == 'p'))
        ft_putstr("0x");
    else if (*hash && arg->type == 'X' && ft_strcmp(arg->s, "0"))
        ft_putstr("0X");
    else if (*hash)
        arg->counter -= (arg->type == 'o') ? 1 : 2;
}

void	print_numbers(t_arg *arg)
{
	unsigned int		size;
	char				sign;
    int hash;
    long len;

	size = 0;
	sign = 0;
	len = ft_strlen(arg->s);
    hash = (arg->hash && ft_strchr("oxXp", arg->type) && ft_strcmp(arg->s, "0"));
	apendix_print_numbers(arg, &size, &sign, &hash);
	if (sign)
		ft_putchar(sign);
	while (!arg->minus && arg->zero && (!arg->acc_flag && !arg->accuracy)
		&& arg->width > size && (--(arg->width)) && (++(arg->counter)))
		ft_putchar('0');
	while (arg->accuracy > len && (--(arg->accuracy)))
		ft_putchar('0');
	if (arg->acc_flag && !ft_strcmp(arg->s, "0") && arg->accuracy == 0 && arg->type != 'f')
	{
        if (arg->plus)
            ft_putchar('+');
        else if (arg->type == 'o' && arg->hash)
            ft_putchar('0');
		else if (arg->width)
			ft_putchar(' ');
		else
			--(arg->counter);
	}
	else
		write(1, arg->s, len);
	while (arg->minus && arg->width > size && arg->width-- && (++arg->counter))
		ft_putchar(' ');
}

void	parse_string(char **str, int *j, t_arg *arg)
{
	if (*(*str + *j) == '%' && *(*str + 1 + *j) == '%'
			&& (*j += 2) && (++(arg->counter)))
		ft_putchar(*((*str += *j) - 1));
	else if (*(*str + *j) == '%' && *(*str + 1 + *j) == '\0' && (*j += 1))
		*str += *j;
	else
	{
		ft_putchar(*(*str)++);
		arg->counter++;
	}
	*j = 0;
}

void	pre(unsigned long long *uvalue, long long value, t_arg *arg, int *base)
{
	if (value != 0)
	{
		if (value < 0 && *base == 10 && (*uvalue = -value))
			arg->sign = 1;
		else
			*uvalue = value;
	}
}

char	*ft_itoa_bases(unsigned long long uvalue, long long value, t_arg *arg)
{
	char					*str;
	int						size;
	char					*tab[2];
	int						base;
	unsigned long long		tmp;

	base = (arg->type == 'x' || arg->type == 'X' || arg->type == 'p') ? 16 : 10;
	(arg->type == 'o') ? base = 8 : 0;
	size = 0;
	tab[0] = "0123456789abcdef";
	tab[1] = "0123456789ABCDEF";
	pre(&uvalue, value, arg, &base);
	tmp = uvalue;
	while (tmp /= base)
		size++;
	str = (char*)malloc(sizeof(char) * ++size + 1);
	str[size] = '\0';
	arg->malloc = 1;
	while (size > 0)
	{
		str[--size] = (arg->type == 'x' || arg->type == 'p') ?
			tab[0][uvalue % base] : tab[1][uvalue % base];
		uvalue /= base;
	}
	return (str);
}
