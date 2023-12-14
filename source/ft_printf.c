/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:47:36 by jackson           #+#    #+#             */
/*   Updated: 2023/12/14 05:22:19 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	checkf(va_list args, const char flag)
{
	if (flag == 'c' || flag == 's')
		return (is_txt(args, flag));
	else if (flag == 'u' || flag == 'd' || flag == 'i')
		return (is_num(args, flag));
	else if (flag == 'p' || flag == 'x' || flag == 'X')
		return (is_hex(args, flag));
	else if (flag == '%')
		return (put_chr('%'));
	return (0);
}

static int	findf(va_list args, const char *str)
{
	int		qty;

	qty = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			while (*str == ' ')
				str++;
			qty += checkf(args, *str);
		}
		else
			qty += put_chr(*str);
		str++;
	}
	return (qty);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		qty;

	if (!str)
		return (-1);
	va_start(args, str);
	qty = findf(args, str);
	va_end(args);
	return (qty);
}
