/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_op_c_unicode.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 02:08:30 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/05 22:45:04 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_op_c_unicode(t_list_p *list, void *params)
{
	(void)list;
	return (ft_put_op_c_unicode(va_arg(*(va_list *)params, unsigned int)));
}

int			ft_strlen_unicode(unsigned int *c)
{
	int		len;

	len = 0;
	while (*c)
	{
		len += size_bin(*c);
		c++;
	}
	return (len);
}

int			ft_put_op_c_unicode(unsigned int c)
{
	int		ret;
	int		bits;

	bits = size_bin(c);
	ret = 0;
	if (bits == 1)
		ret += write(1, &c, 1);
	else if (bits == 2)
		ret += two_oct(c);
	else if (bits == 3)
		ret += three_oct(c);
	else if (bits == 4)
		ret += four_oct(c);
	else
		return (-1);
	return (ret);
}
