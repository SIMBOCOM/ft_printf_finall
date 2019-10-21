/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flogan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:55:03 by flogan            #+#    #+#             */
/*   Updated: 2019/10/16 20:26:25 by flogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# define DI(x, y) (!x) ? (int)y : LM(x, y)
# define OUX(x, y) (!x) ? (unsigned int)y : ULM(x, y)
# define LM(x, y) (x == 'l') ? (long)y : HH(x,y)
# define HH(x, y) (x == *(short*)"hh") ? (char)y : H(x,y)
# define H(x, y) (x == 'h') ? (short)y : LL(x,y)
# define LL(x, y) (x == *(short*)"ll") ? (long long)y : J(x,y)
# define J(x, y) (x == 'j') ? (intmax_t)y : Z(x, y)
# define Z(x, y) (x == 'z') ? (size_t)y : L(x, y)
# define L(x, y) (x == 'L') ? (__int32_t)y : T(x,y)
# define ULM(x, y) (x == 'l') ? (unsigned long)y : UHH(x,y)
# define UHH(x, y) (x == *(short*)"hh") ? (unsigned char)y : UH(x,y)
# define UH(x, y) (x == 'h') ? (unsigned short)y : ULL(x,y)
# define ULL(x, y) (x == *(short*)"ll") ? (unsigned long long)y : UJ(x,y)
# define UJ(x, y) (x == 'j') ? (intmax_t)y : UL(x, y)
# define UL(x, y) (x == 'L') ? (uint32_t)y : T(x,y)

# define T(x, y) (x == 't') ? (ptrdiff_t)y : y

typedef struct			s_arg
{
	unsigned			plus: 1;
	unsigned			space: 1;
	unsigned			minus: 1;
	unsigned			hash: 1;
	unsigned			zero: 1;
	unsigned			acc_flag: 1;
	char				*s;
	unsigned int		width;
	unsigned int		accuracy;
	unsigned long long	counter;
	unsigned			spec: 16;
	unsigned			type: 8;
	unsigned			sign: 1;
	unsigned			malloc: 1;
}						t_arg;
char					*ft_itoa_bases(unsigned long long uvalue,
		long long value, t_arg *arg);
void					parser(char **format, t_arg *arg, va_list args, int *j);
void					parse_string(char **str, int *j, t_arg *arg);
void					print_numbers(t_arg *arg);
void					print_string(t_arg *arg);
void					print_char(t_arg *arg, va_list args);
void					parser_width(char **format, t_arg *arg, va_list args,
		int *j);
#endif
