/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthai <rthai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 20:58:13 by rthai             #+#    #+#             */
/*   Updated: 2019/10/21 22:43:48 by rthai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

unsigned long long		my_pow(int base, int power)
{
	unsigned long long result;

	power++;
	result = 1;
	if (!base)
		return (0);
	while (--power > 0)
		result *= base;
	return (result);
}

void		round_str(char *str)
{
	int i;
	char c;
	char d;
	
	i = 0;
	while (str[i])
		i++;
	if (i && str[--i] >= '5')
	{
		while (i && (str[i - 1] == '9' || str[i - 1] == '.'))
		{
			if (str[i - 1] != '.')
				str[i - 1] = '0';
			i--;
		}
		if (!i && str[i] == '0')
		{
			c = str[i];
			str[i] = '1';
			i++; 
			while(str[i])
			{
				d = str[i];
				str[i] = c;
				c = d;
				i++;
			}	
		} else
		str[i - 1] = str[i - 1] + 1;
	}
}

int			size_number(int number)
{
	long long	temp;
	int			size;

	size = 0;
	temp = 1;
	while ((number / temp))
	{
		size++;
		temp *= 10;
	}
	return (size);
}

int			size_vector(t_vector *number)
{
	return (size_number(number->array[number->size - 1])
	+ (number->size - 1) * 9);
}

void		number_zero(t_doub_float_e *number, int z)
{
	int num_zero;
	int size;

	size = size_vector(&(number->fraction_part));
	num_zero = z - size;
	number->number_zero = num_zero;
}

t_vector	my_big_pow(int a, int base)
{
	t_vector	result;
	int			five_in_13;

	five_in_13 = 1220703125;
	result.size = 1;
	result.array[0] = 1;
	if (a == 0)
	{
		result.array[0] = 0;
		return (result);
	}
	while (base > 0)
	{
		if (base >= 13)
		{
			mult_long_to_short(&result, five_in_13);
			base -= 13;
		}
		else
		{
			mult_long_to_short(&result, my_pow(a, base));
			base = 0;
		}
	}
	return (result);
}

void	initialization(t_doub_float_e *number)
{
	number->whole_part.size = 1;
	number->number_zero = MAX_ZERO;
	if (number->power < 0)
	{
		number->whole_part.array[0] = 0;
		number->fraction_part.size = 1;
		number->fraction_part = my_big_pow(5, -number->power);
		number_zero(number, -number->power);
		return ;
	}
	number->whole_part.array[0] = 1;
	number->fraction_part.size = 1;
	number->fraction_part.array[0] = 0;
}

void	convert_vector(t_vector *number, char **str, int *accuracy)
{
	int base;
	int b;
	int i;

	i = number->size;
	while (--i >= 0 && *accuracy)
	{
		b = number->array[i];
		if (i == number->size - 1)
			base = my_pow(10, size_number(b) - 1);
		else
			base = 100000000;
		while (base > 0 && *accuracy)
		{
			*(*str)++ = b / base + '0';
			b %= base;
			base /= 10;
			(*accuracy)--;
		}
	}
}

char	*convert_to_str(t_doub_float_e *number,  t_arg *arg)
{
	int		size_whole_part;
	char	*result;
	char	*ptr;

	arg->accuracy++;
	if (!(size_whole_part = size_vector(&(number->whole_part))))
		size_whole_part++;
	result = (char*)malloc(sizeof(char) * (size_whole_part + arg->accuracy + 2));
	ptr = result;
	convert_vector(&(number->whole_part), &ptr, &size_whole_part);
	if (arg->hash || arg->accuracy != 1)
		*ptr++ = '.';	
	while (number->number_zero && arg->accuracy)
	{
		*ptr++ = '0';
		number->number_zero--;
		arg->accuracy--;
	}
	convert_vector(&(number->fraction_part), &ptr, (int*)&arg->accuracy);
	arg->accuracy++;
	while (--arg->accuracy)
		*ptr++ = '0';
	*ptr = 0;
	round_str(result);
	*(--ptr) = 0;
	return (result);
}

char		*print_double(double a, t_arg *arg)
{

	t_doub_float_e	number;
	__uint128_t		*b;
	int				i;
	int				shift;

	i = 0;
	b = (__uint128_t*)&a;
	arg->sign = (*b >> 63) & 1;
	number.power =  ((*b & 0x7FF0000000000000) >> 52) - 1023;
	initialization(&number);
	*b = *b & 0x000FFFFFFFFFFFFF;
	while (i < number.power)
	{
		mult_long_to_short(&(number.whole_part), 2);
		if (51 - i >= 0)
			sum_long_to_short(&(number.whole_part), (*b >> (51 - i)) & 1);
		i++;	
	}
	i = 0;
	if (number.power > 0)
		shift = 52 - number.power;
	else
		shift = 52;
	while (--shift >= 0)
	{	
		mult_long_to_short(&(number.fraction_part), 10);
		sum_long_to_long(&(number.fraction_part), my_big_pow((int)((*b >> shift) & 1) * 5, i + 1 + (SIGN(number.power))));
		i++;
	}
	number_zero(&number, i + (SIGN(number.power)));
	return (convert_to_str(&number, arg));
}

char   *print_float(float a, t_arg *arg)
{
	t_doub_float_e	number;
	__uint64_t		*b;
	int				i;
	int				shift;

	i = 0;
	b = (__uint64_t*)&a;
	arg->sign = (*b >> 31) & 1;
	number.power =  ((*b & 0x7F800000) >> 23) - 127;
	initialization(&number);
	*b = *b & 0x007FFFFF;
	while (i < number.power)
	{
		mult_long_to_short(&(number.whole_part), 2);
		if (22 - i >= 0)
			sum_long_to_short(&(number.whole_part), (*b >> (22 - i)) & 1);
		i++;	
	}
	i = 0;
	if (number.power > 0)
		shift = 23 - number.power;
	else
		shift = 23;
	while (--shift >= 0)
	{	
		mult_long_to_short(&(number.fraction_part), 10);
		sum_long_to_long(&(number.fraction_part), my_big_pow((int)((*b >> shift) & 1) * 5, i + 1 + (SIGN(number.power))));
		i++;
	}
	number_zero(&number, i + (SIGN(number.power)));
	return (convert_to_str(&number, arg));
}

char    *print_long_double(long double a, t_arg *arg)
{
	t_doub_float_e	number;
	__uint128_t		*b;
	int				i;
	int				shift;

	i = 0;
	b = (__uint128_t*)&a;
	arg->sign = (*b >> 79) & 1;
	i = 79;
	number.power = 0;
	while (--i >= 64)
		number.power = number.power * 2 + ((*b >> i) & 1);
	number.power = number.power - 16383;
	initialization(&number);
	i = 0;
	while (i < number.power)
	{
		mult_long_to_short(&(number.whole_part), 2);
		if (62 - i >= 0)
			sum_long_to_short(&(number.whole_part), (*b >> (62 - i)) & 1);
		i++;	
	}
	i = 0;
	if (number.power > 0)
		shift = 63 - number.power;
	else
		shift = 63;
	while (--shift >= 0)
	{	
		mult_long_to_short(&(number.fraction_part), 10);
		sum_long_to_long(&(number.fraction_part), my_big_pow((int)((*b >> shift) & 1) * 5, i + 1 + (SIGN(number.power))));
		i++;
	}
	number_zero(&number, i + (SIGN(number.power)));
	return (convert_to_str(&number, arg));
}