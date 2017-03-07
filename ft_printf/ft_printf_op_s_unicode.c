/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_op_s_unicode.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 01:23:45 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/12 18:49:28 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_printf_op_s_unicode(t_list_p *list, void *params)
{
	unsigned int	*str;
	int				i;
	int				tmp;

	if (!(str = (unsigned int *)va_arg(*(va_list *)params, unsigned int *)))
		return (write(1, "(null)", 6));
	tmp = 0;
	if (!(i = 0) && list->modifi_atoi > 0 && list->prec_i)
	{
		while ((list->prec - (i + size_bin(*(str + tmp)))) >= 0)
		{
			i += size_bin(*(str + tmp));
			list->modifi_atoi -= size_bin(*(str + tmp++));
		}
		i = ft_write_space(list->modifi_atoi, list);
	}
	i += ft_write_space(list->modifi_atoi - ft_strlen_unicode(str), list);
	tmp = 0;
	while (*str && ((list->prec > tmp) || (!list->prec_i && !list->prec)))
	{
		tmp += size_bin(*str);
		if (tmp <= list->prec || !list->prec)
			i += ft_put_op_c_unicode(*(str++));
	}
	return (i + ft_write_space((list->modifi_atoi * -1) - i, list));
}
