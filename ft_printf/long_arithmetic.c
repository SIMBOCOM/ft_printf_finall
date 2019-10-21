#include "header.h"


void	sum_long_to_long(t_vector *a, t_vector b)
{
	int i;
	int carry;
	int base;

	carry = 0;
	if (!a->size)
	{
		a->size = 1;
		a->array[0] = 0;
	}
	base = 1000 * 1000 * 1000;
	i = 0;
	while (i < (MAX(a->size, b.size)) || carry)
	{
		if (a->size == i)
		{
			a->size++;
			a->array[i] = 0;
		}
		a->array[i] += (b.size > i ? b.array[i] : 0) + carry;
		carry = a->array[i] >= base;
		if (carry)
			a->array[i] -= base;
		i++;
	}
}

void	sum_long_to_short(t_vector *a, int b)
{
	int i;
	int carry;
	int base;

	if (!a->size)
	{
		a->size = 1;
		a->array[0] = 0;
	}
	base = 1000 * 1000 * 1000;
	i = 1;
	a->array[0] += b;
	carry = a->array[0] >= base;
	if (carry)
		a->array[i] -= base;
	while (carry)
	{
		if (a->size == i)
		{
			a->size++;
			a->array[i] = 0;
		}
		a->array[i] += carry;
		carry = a->array[i] >= base;
		if (carry)
			a->array[i] -= base;
		i++;
	}
}

void	mult_long_to_short(t_vector *a, int b)
{
	int			carry;
	int			i;
	long long	cur;
	long long			base;

	base = 1000 * 1000 * 1000;
	carry = 0;
	i = 0;
	if (!a->size)
	{
		a->size = 1;
		a->array[0] = 0;
	}
	while (i < a->size || carry)
	{
		if (i == a->size)
		{
			a->size++;
			a->array[i] = 0;
		}
		cur = carry + (long long)a->array[i] * (long long)b;
		a->array[i] = (int)(cur % base);
		carry = (int)(cur / base);
		i++;
	}
	while (a->size > 1 && a->array[a->size - 1] == 0)
		a->size--;
}
