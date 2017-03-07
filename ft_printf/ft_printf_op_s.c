/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_op_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 16:40:28 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/12 19:59:29 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_putstr_len(char *str, int len)
{
	int				i;

	i = 0;
	while (str[i] && (len > i || !len))
		write(1, str + i++, 1);
	return (i);
}

int					ft_putstr_ret_len_null(t_list_p *list)
{
	if (list->chr && (list->modifi_atoi > 0))
		return (ft_write_space(list->modifi_atoi, list));
	else
		return (ft_write_space(list->modifi_atoi, list) + write(1,
					"(null)", 6));
}

int					ft_putstr_ret_len(t_list_p *list, void *params)
{
	int				i;
	int				tmp;
	void			*ptr;

	if (list && list->modifi_l == 1)
		return (ft_printf_op_s_unicode(list, params));
	if (!(ptr = va_arg(*(va_list *)params, char *)))
		return (ft_putstr_ret_len_null(list));
	if (list->prec_i && ft_strlen(ptr) > (size_t)list->prec)
		i = ft_write_space(list->modifi_atoi - (list->prec), list);
	else
	{
		tmp = list->prec;
		list->prec = 0;
		i = ft_write_space(list->modifi_atoi - (ft_strlen(ptr)), list);
		list->prec = tmp;
	}
	if (list->prec_i && (!list->prec))
		return (i);
	i = i + ft_putstr_len(ptr, list->prec);
	return (i + ft_write_space((list->modifi_atoi + i) * -1, list));
}

int					ft_print_chr(t_list_p *list, void *params)
{
	va_list			*oklm;
	int				n;

	oklm = params;
	if (list && list->modifi_l == 1)
		return (ft_put_op_c_unicode(va_arg(*oklm, unsigned int)));
	n = ft_write_space(list->modifi_atoi - 1, list);
	ft_putchar((char)va_arg(*oklm, int));
	n += ft_write_space((list->modifi_atoi * -1) - 1, list);
	return (1 + n);
}
