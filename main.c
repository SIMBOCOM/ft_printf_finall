#include "include/header.h"
#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>


int main()
{
	t_arg arg;

	arg.accuracy = 20;

	// double d = 2345.23452345;
	// long double ld = LDBL_MAX;
	// float f = -37.0777779;
	printf("% 05.0f\n", 7.3);
	ft_printf("% 05.0f\n\n", 7.3);
    printf("%05.1f\n", 7.3);
    ft_printf("%05.1f\n\n", 7.3);
    printf("%5.0f\n", 7.3);
    ft_printf("%5.0f\n\n", 7.3);
    printf("% 5.0f\n", 7.3);
    ft_printf("% 5.0f\n\n", 7.3);
    printf("%+5.0d\n", 0);
    ft_printf("%+5.0d\n\n", 0);
    printf("%#3x\n", 0);
    ft_printf("%#3x\n\n", 0);
    printf("%#.5o\n", 21);
    ft_printf("%#.5o\n\n", 21);
    printf("%#.5o\n", 21);
    ft_printf("%#.5o\n\n", 21);
    printf("%d",printf("{%.*d}", -5, 42));
    printf("\n");
    printf("%d",ft_printf("{%.*d}", -5, 42));
    printf("\n");
    printf("%d",printf("{%.*s}", -5, "42"));
    printf("\n");
    printf("%d",ft_printf("{%.*s}", -5, "42"));
    printf("\n");
    printf("%d",printf("{%*d}", -5, 42));
    printf("\n");
    printf("%d",ft_printf("{%*d}", -5, 42));
    printf("\n");
    printf("%d",printf("{%*c}", -15, 0));
    printf("\n");
    printf("%d",ft_printf("{%*c}", -15, 0));
    printf("\n");
    printf("%d",printf("{%05.*d}", -15, 42));
    printf("\n");
    printf("%d",ft_printf("{%05.*d}", -15, 42));

	// ft_printf("%40.20f\n", f);
	// printf("%40.20lf\n", d);
	// ft_printf("%40.20lf\n", d);
	// printf("%40.20Lf\n", ld);
	// ft_printf("%40.20Lf\n", ld);
	// printf("%f\n", 1444565444646.6465424242242);
	// printf("{%f}{%lf}{%Lf}\n", 1444565444646.6465424242242, 1444565444646.6465424242242, 1444565444646.6465424242242);
	// ft_printf("{%f}{%lf}{%Lf}\n", 1444565444646.6465424242242, 1444565444646.6465424242242, 1444565444646.6465424242242);
}
