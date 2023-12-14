/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:28:08 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 05:18:40 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	is_neg(int *num)
{
	int	qty;

	qty = put_chr('-');
	*num *= -1;
	return (qty);
}

static int	cont_dig(const unsigned long num, const unsigned int base)
{
	unsigned long	n;
	int				i;

	n = num;
	i = -1;
	while (++i, n > 0)
		n /= base;
	return (i);
}

static int	put_num(const unsigned long num, const unsigned int base, char ref)
{
	unsigned long	nbr;
	char			str[21];
	int				len;
	int				res;

	nbr = num;
	len = cont_dig(nbr, base);
	str[len] = '\0';
	while (len--, len >= 0)
	{
		if (base == 10)
			str[len] = (nbr % 10) + '0';
		else
		{
			res = nbr % 16;
			if (res < 10)
				str[len] = res + '0';
			else
				str[len] = ref + res - 10;
		}
		nbr /= base;
	}
	return (put_str(str));
}

int	is_num(va_list args, const char flag)
{
	unsigned int	unu;
	int				num;
	int				qty;

	unu = 0;
	qty = 0;
	num = 0;
	if (flag == 'u')
		unu = va_arg(args, unsigned long);
	else
		num = va_arg(args, int);
	if (!unu && !num)
		return (put_chr('0'));
	if (num == -2147483648)
		return (qty += put_str("-2147483648"));
	if (num < 0)
		qty += is_neg(&num);
	if (num)
		unu = num;
	qty += put_num(unu, 10, 0);
	return (qty);
}

int	is_hex(va_list args, const char flag)
{
	unsigned long	num;
	int				qty;

	if (flag == 'x' || flag == 'X')
		num = va_arg(args, unsigned int);
	else
		num = va_arg(args, unsigned long);
	if (!num && flag == 'p')
		return (put_str("(nil)"));
	if (!num)
		return (put_chr('0'));
	if (flag == 'x')
		return (put_num(num, 16, 'a'));
	if (flag == 'X')
		return (put_num(num, 16, 'A'));
	qty = put_str("0x");
	qty += put_num(num, 16, 'a');
	return (qty);
}
