/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_otool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:32:50 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/07 17:37:43 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			reverse_int(int x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);
}

void		ft_putnbr_base(unsigned long long int num, int base)
{
	char	*str;

	str = "0123456789abcdef";
	if (num / base)
		ft_putnbr_base(num / base, base);
	write(1, str + (num % base), 1);
}

void		h_z(unsigned long long int num)
{
	write(1, "0", 1);
	ft_putnbr_base(num & 0xff, 16);
}
