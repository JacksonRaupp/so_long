/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:40:35 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 05:24:28 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	put_str(const char *str)
{
	int		qty;

	qty = -1;
	while (qty++, *str)
		put_chr(*str++);
	return (qty);
}

int	put_chr(const char chr)
{
	return (write(1, &chr, 1));
}

int	is_txt(va_list args, const char flag)
{
	char	*str;
	char	chr;

	if (flag == 'c')
	{
		chr = va_arg(args, int);
		return (put_chr(chr));
	}
	str = va_arg(args, char *);
	if (!str)
		return (put_str("(null)"));
	return (put_str(str));
}
