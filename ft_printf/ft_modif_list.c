/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 04:33:33 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/13 01:17:54 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list_p		*ft_init_list(t_list_p *list)
{
	list->modifi_atoi = 0;
	list->modifi_l = 0;
	list->modifi_h = 0;
	list->modifi_j = 0;
	list->modifi_z = 0;
	list->chr = 0;
	list->dize = 0;
	list->d = 0;
	list->p = 0;
	list->space = 0;
	list->prec = 0;
	list->prec_i = 0;
	return (list);
}

void			ft_prec(char **str, t_list_p *ptr, char op)
{
	if (!op && **str == '.' && (ptr->prec_i = 1))
	{
		ptr->prec = ft_atoi(++*str);
		while (ft_isdigit(**str))
			(*str)++;
	}
	if (op && (ft_isdigit(**str) || (*(*str - ptr->d) == '-' &&
				ft_isdigit(*(*str - ptr->d) + 1))))
	{
		if (*(*str - ptr->d) == '-' && ft_isdigit(*((*str - ptr->d) + 1)))
			*str = (*str - ptr->d);
		while (**str == '0')
		{
			ptr->chr++;
			(*str)++;
		}
		if (!ptr->p && (ptr->p = **str == '+' ? 1 : 0))
			*str += ptr->p;
		ptr->modifi_atoi = ft_atoi(*str);
		if (!ft_strchr("sSpdDioOuUxXcC%", **str))
			*str += ptr->modifi_atoi < 0 ?
			(ft_putnbr_ulong_len(ptr->modifi_atoi * -1) + 1) :
			ft_putnbr_ulong_len(ptr->modifi_atoi);
		ptr->chr = ptr->modifi_atoi < 0 ? 0 : ptr->chr;
	}
}

t_list_p		*ft_check_op(char **str, t_list_p *ptr)
{
	while (**str == ' ' || **str == '-' || **str == '#' || **str == '+')
	{
		ptr->dize += **str == '#' ? 1 : 0;
		ptr->d += **str == '-' ? 1 : 0;
		ptr->p += **str == '+' ? 1 : 0;
		ptr->space += **str == ' ' ? 1 : 0;
		(*str)++;
	}
	return (ptr);
}

void			ft_zebiduzebi(char **str, t_list_p *ptr)
{
	while (**str == 'l' || **str == 'L')
	{
		ptr->modifi_l++;
		(*str)++;
	}
	while (**str == 'h')
	{
		ptr->modifi_h++;
		(*str)++;
	}
	while (**str == 'j')
	{
		ptr->modifi_j++;
		(*str)++;
	}
	while (**str == 'z')
	{
		ptr->modifi_z++;
		(*str)++;
	}
}

t_list_p		*ft_fill_list(char **str, t_list_p *list)
{
	t_list_p	*ptr;

	if (list)
		free(list);
	if (!(ptr = (t_list_p *)malloc(sizeof(t_list_p))))
		ft_error();
	ptr = ft_init_list(ptr);
	(*str)++;
	ptr = ft_check_op(str, ptr);
	ft_prec(str, ptr, 0);
	ft_prec(str, ptr, 1);
	if (!ptr->modifi_atoi && ft_isdigit(**str))
	{
		ptr->modifi_atoi = ft_atoi(*str);
		if (!ft_strchr("sSpdDioOuUxXcC%", **str))
			*str += ptr->modifi_atoi < 0 ?
				(ft_putnbr_ulong_len(ptr->modifi_atoi * -1) + 1) :
				ft_putnbr_ulong_len(ptr->modifi_atoi);
	}
	if (!ft_strchr("sSpdDioOuUxXcC%", **str))
		ptr = ft_check_op(str, ptr);
	ft_prec(str, ptr, 0);
	ft_zebiduzebi(str, ptr);
	return (ptr);
}
