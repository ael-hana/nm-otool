/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foret_de_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 19:49:03 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/12 20:46:03 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_check_for_ft_print_op_x(unsigned long long int num, int tmp,
		t_list_p *list)
{
	if (!num && tmp < ft_len_base(num, 16))
		return (ft_write_space(list->modifi_atoi, list));
	else if (tmp < ft_len_base(num, 16))
		return (ft_write_space(list->modifi_atoi - (ft_len_base(num, 16)),
					list));
	else if (tmp > ft_len_base(num, 16))
		return (ft_write_space(list->modifi_atoi - (tmp), list));
	else if (list->prec_i)
		return (ft_write_space(list->modifi_atoi - tmp, list));
	else
		return (ft_write_space(list->modifi_atoi - ft_len_base(num, 16), list));
}

int		ft_print_op_o_great(t_list_p *list, void *params)
{
	list->modifi_l = 1;
	return (ft_print_op_o(list, params));
}

int		ft_print_op_o_nega(unsigned long long int num, t_list_p *list)
{
	int	i;
	int	tmp;

	tmp = list->prec;
	list->chr = 0;
	list->prec = 0;
	if (list->d && list->dize)
		list->modifi_atoi *= -1;
	i = ft_write_space((list->modifi_atoi - ft_len_base(num, 8)) - 1, list);
	list->chr = 1;
	i += ft_write_space((tmp - ft_len_base(num, 8)) - 1, list);
	i += write(1, "0", 1) + ft_printf_base(num, 8, 0, 0);
	list->chr = 0;
	return (i + ft_write_space((list->modifi_atoi * -1) - i, list));
}

void	ft_zebi(long long int num, t_list_p *list)
{
	if (list->modifi_atoi > 0 && !list->prec && num)
		list->modifi_atoi = list->modifi_atoi - ft_putnbr_ulong_len(num);
	else if (list->modifi_atoi > 0 && !num && list->prec_i && !list->prec)
		list->modifi_atoi = list->modifi_atoi;
	else if (list->modifi_atoi > 0 && (list->prec < ft_putnbr_ulong_len(num)))
		list->modifi_atoi -= ft_putnbr_ulong_len(num);
	else if (list->modifi_atoi > 0 && (list->prec > list->modifi_atoi))
		list->modifi_atoi = 0;
	else if (list->modifi_atoi > 0 && (list->chr || (list->modifi_atoi >
					(list->prec + ft_putnbr_ulong_len(num)))))
		list->modifi_atoi -= list->prec;
	else if (list->modifi_atoi > 0)
		list->modifi_atoi -= ft_putnbr_ulong_len(num);
}

void	ft_zebi_nega(long long int num, t_list_p *list)
{
	if (list->modifi_atoi > 0 && !list->prec)
		list->modifi_atoi = list->modifi_atoi - (ft_putnbr_ulong_len(num) - 1);
	else if (list->modifi_atoi > 0 && (list->prec < (ft_putnbr_ulong_len(num)
					+ 1)))
		list->modifi_atoi = list->modifi_atoi - 1;
	else if (list->modifi_atoi > 0 && (list->prec > list->modifi_atoi))
	{
		list->modifi_atoi = 0;
		list->chr = 1;
	}
	else if (list->modifi_atoi > 0)
		list->modifi_atoi -= (ft_putnbr_ulong_len(num) + 1);
}
