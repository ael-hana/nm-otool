/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_handle_otool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:22:11 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/07 17:37:27 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		display_section(long long int addres, int size, char *ptr)
{
	int		i;

	i = 0;
	ft_putstr("(__TEXT,__text) section");
	while (i < size)
	{
		if (!(i % 16))
		{
			ft_printf(addres > 0 ? "\n%016lx " : "\n%015lx ", addres);
			addres += 16;
		}
		(ptr[i] & 0xff) > 15 ? ft_putnbr_base(ptr[i] & 0xff, 16) : h_z(ptr[i]);
		ft_putchar(' ');
		i++;
	}
}

void		get_seg_64(struct segment_command_64 *seg, struct mach_header_64 *h)
{
	size_t				i;
	struct section_64	*sec;

	i = 0;
	sec = (struct section_64 *)((char *)seg +
			sizeof(struct segment_command_64));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec[i].segname, SEG_TEXT) &&
				!ft_strcmp(sec[i].sectname, SECT_TEXT))
			display_section(sec[i].addr,
					sec[i].size, (char *)h + sec[i].offset);
		++i;
	}
}

void		get_seg(struct segment_command *seg, struct mach_header *h)
{
	size_t				i;
	struct section		*sec;

	i = 0;
	sec = (struct section *)((char *)seg +
			sizeof(struct segment_command));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec[i].segname, SEG_TEXT) &&
				!ft_strcmp(sec[i].sectname, SECT_TEXT))
		{
			display_section(sec[i].addr, sec[i].size,
					(char *)h + sec[i].offset);
		}
		++i;
	}
}

void		ft_printname(char *str, char *str2)
{
	ft_putstr(str);
	ft_putstr("(");
	ft_putstr(str2);
	ft_putstr("):\n");
}
