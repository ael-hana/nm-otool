/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_wise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:05:32 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/12 18:07:19 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						two_oct(unsigned int a)
{
	unsigned int		tmp;

	tmp = ((a >> 6) + 192);
	write(1, &tmp, 1);
	tmp = (a ^ ((tmp - 192) << 6)) + 128;
	write(1, &tmp, 1);
	return (2);
}

int						three_oct(unsigned int a)
{
	unsigned int		tmp;

	tmp = (a >> 12) + 224;
	ft_putchar(tmp);
	a = a ^ ((tmp - 224) << 12);
	tmp = (a >> 6) + 128;
	write(1, &tmp, 1);
	tmp = (a ^ ((tmp - 128) << 6)) + 128;
	write(1, &tmp, 1);
	return (3);
}

int						four_oct(unsigned int a)
{
	unsigned int		tmp;

	tmp = (a >> 18) + 240;
	ft_putchar(tmp);
	a = a ^ ((tmp - 240) << 18);
	tmp = (a >> 12) + 128;
	ft_putchar(tmp);
	a = a ^ ((tmp - 128) << 12);
	tmp = (a >> 6) + 128;
	write(1, &tmp, 1);
	tmp = (a ^ ((tmp - 128) << 6)) + 128;
	write(1, &tmp, 1);
	return (4);
}

int						size_bin(unsigned int chr)
{
	int					i;

	i = 0;
	while (chr)
	{
		chr = chr >> 1;
		i++;
	}
	if (i <= 7)
		return (1);
	else if (i <= 11)
		return (2);
	else if (i > 11 && i <= 16)
		return (3);
	else if (i > 16 && i <= 21)
		return (4);
	return (0);
}
