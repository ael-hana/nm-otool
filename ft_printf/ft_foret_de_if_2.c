/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foret_de_if_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:06:35 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/13 01:39:40 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long int		ft_foret_de_if_2_ft_print_num_d(t_list_p *list,
							void *params)
{
	unsigned long long int	num;

	if (list && list->modifi_l == 1)
		num = va_arg(*((va_list *)params), long int);
	else if (list && list->modifi_l == 2)
		num = va_arg(*((va_list *)params), long long int);
	else if (list && list->modifi_h == 1)
		num = (short)va_arg(*((va_list *)params), int);
	else if (list && list->modifi_h == 2)
		num = (char)va_arg(*((va_list *)params), int);
	else if (list && list->modifi_j == 1)
		num = va_arg(*((va_list *)params), long int);
	else if (list && list->modifi_z == 1)
		num = va_arg(*((va_list *)params), size_t);
	else
		num = va_arg(*((va_list *)params), int);
	return (num);
}

int							ft_foret_de_if_2_ft_print_num_d_nega(unsigned long
		long int num, t_list_p *list)
{
	int						i;
	int						tmp2;

	tmp2 = list->modifi_atoi;
	i = 0;
	num *= -1;
	ft_zebi_nega(num, list);
	i += list->chr ? write(1, "-", 1) : 0;
	if (list->modifi_atoi > 0)
		i += ft_write_space(list->modifi_atoi -
				(ft_putnbr_ulong_len(num) - list->p), list);
	i += list->chr ? ft_putnbr_ulong(num, list) : write(1, "-", 1) +
		ft_putnbr_ulong(num, list);
	return (i + ft_write_space((tmp2 + i) * -1, list));
}

void						ft_error(void)
{
	exit(EXIT_FAILURE);
}

t_tab_f						**ft_init_tab_func(void)
{
	t_tab_f					**oklm;

	if (!(oklm = malloc(sizeof(t_tab_f**) * 15)))
		ft_error();
	oklm[0] = &ft_putstr_ret_len;
	oklm[1] = &ft_printf_op_s_unicode;
	oklm[2] = &ft_printf_p;
	oklm[3] = &ft_print_num_d;
	oklm[4] = &ft_print_num_d_height_long;
	oklm[5] = &ft_print_num_d;
	oklm[6] = &ft_print_op_o;
	oklm[7] = &ft_print_op_o_great;
	oklm[8] = &ft_print_num_d_height_u_int;
	oklm[9] = &ft_print_num_d_height_u_long;
	oklm[10] = &ft_print_op_x;
	oklm[11] = &ft_print_op_x_great;
	oklm[12] = &ft_print_chr;
	oklm[13] = &ft_printf_op_c_unicode;
	oklm[14] = &ft_printf_poucent;
	return (oklm);
}
