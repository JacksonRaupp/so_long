/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:52:20 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/13 19:39:30 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

size_t	ft_strlen(const char *str);
void	error(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

void	error(char *str)
{
	int	x;

	x = 0;
	while (*str)
		x += (int)write(1, str++, 1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if ((nmemb * size != 0) && ((nmemb * size) / size != nmemb))
		return (NULL);
	mem = (void *) malloc (nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	char			*str;

	str = (char *) s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return ((void *)str);
}
