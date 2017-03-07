/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 05:22:35 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/13 01:38:12 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf_poucent(t_list_p *list, void *params)
{
	int			i;
	int			tmp;

	(void)params;
	tmp = list->modifi_atoi;
	if ((!list->prec_i && !list->prec) || list->modifi_atoi)
	{
		i = ft_write_space(list->modifi_atoi - 1, list);
		i += write(1, "%", 1);
	}
	else
	{
		i = ft_write_space(list->modifi_atoi - 1, list);
		i += write(1, "%", 1);
	}
	i += ft_write_space(((tmp * -1) - i), list);
	return (i);
}

int				ft_chrstr_po(char chr, char *search)
{
	int			i;

	i = 0;
	while (search[i])
	{
		if (search[i] == chr)
			return (i);
		i++;
	}
	return (-1);
}

int				ft_printf_print(char **format, int len, t_list_p *list)
{
	if (**format)
	{
		ft_putchar(**format);
		if (list)
			len += ft_write_space(((list->modifi_atoi * -1) - 1), list);
		*format += 1;
		len++;
	}
	return (len);
}

void			ft_init_var(int *len, t_list_p **list, t_tab_f ***oklm, int op)
{
	if (op)
	{
		*oklm = ft_init_tab_func();
		*len = 0;
		*list = NULL;
	}
	else
	{
		if (*list)
			free(*list);
		free(*oklm);
	}
}

int				ft_printf(const char *format, ...)
{
	int			i;
	t_list_p	*list;
	int			len;
	va_list		ap;
	t_tab_f		**oklm;

	ft_init_var(&len, &list, &oklm, 1);
	va_start(ap, format);
	while (*format)
	{
		while (*format == '%')
		{
			list = ft_fill_list((char **)&format, list);
			if (-1 != (i = ft_chrstr_po(*format, "sSpdDioOuUxXcC%")))
				len += oklm[i](list, &ap) + (list->modifi_atoi = 0);
			else if (list->modifi_atoi > 0)
				len += ft_write_space(*format ? list->modifi_atoi - 1 :
						list->modifi_atoi, list);
			*format && i != -1 ? format++ : 0;
		}
		len = ft_printf_print((char **)&format, len, list);
	}
	va_end(ap);
	ft_init_var(&len, &list, &oklm, 0);
	return (len);
}
