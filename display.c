/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 19:08:06 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/06 17:28:08 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		display_list(t_nm *ptr)
{
	while (ptr && ptr->type != '*')
	{
		//display_value(ptr->hex);
		ft_putstr(ptr->hex);
		ft_putstr(" ");
		ft_putchar(ptr->type);
		ft_putstr(" ");
		ft_putstr(ptr->name);
		ft_putstr("\n");
		ptr = ptr->next;
	}
}

int			reverse_int(int x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);
}

void		ft_printName(char *str, char *str2)
{
	ft_putstr("\n");
	ft_putstr(str);
	ft_putstr("(");
	ft_putstr(str2);
	ft_putstr(")\n");
}

void		ft_putnbr_base(unsigned long long int num, int base)
{
	char	*str;

	str = "0123456789abcdef";
	if (num / base)
		ft_putnbr_base(num / base, base);
	write(1, str + (num % base), 1);
}


void		display_value(size_t value)
{
	if (value > 0)
	{
		ft_putstr("0000000");
		ft_putnbr_base(value, 16);
	}
	else
		ft_putstr("                ");
	ft_putchar(' ');
}
