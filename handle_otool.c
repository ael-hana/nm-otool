/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_otool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:19:57 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/07 17:38:15 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int							*sorttab(int *tab, int len)
{
	int						i;
	int						tmp;

	i = 0;
	while (len > (i + 1))
	{
		if (tab[i] > tab[i + 1])
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			++i;
	}
	return (tab);
}

int							*gen_array(struct ranlib *rl, size_t len, char *ptr)
{
	struct ar_hdr			*ar;
	int						*arr;
	size_t					i;

	arr = malloc(sizeof(arr) * (len + 1));
	ft_bzero(arr, len + 1);
	i = 0;
	while (i < len)
	{
		ar = (void*)ptr + rl[i].ran_off;
		arr[i] = rl[i].ran_off;
		i++;
	}
	return (arr);
}

void						fat_handle(char *file, char *str)
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					i;
	int					offset;

	i = 0;
	header = (struct fat_header *)file;
	arch = (void*)&header[1];
	while (i < reverse_int(header->nfat_arch))
	{
		if (reverse_int(arch->cputype) == CPU_TYPE_X86_64
			|| reverse_int(arch->cputype) == CPU_TYPE_X86)
			offset = arch->offset;
		++i;
		++arch;
	}
	ft_otool(file + reverse_int(offset), str);
}

void						handle_otool_ar(char *file, char *filename)
{
	struct ar_hdr			*header;
	char					*str;
	int						ext_num;
	size_t					size[2];
	int						*tab;

	header = (void *)file + SARMAG;
	ext_num = ft_atoi(header->ar_name + ft_strlen(AR_EFMT1));
	str = (void*)file + sizeof(*header) + SARMAG + ext_num;
	size[0] = *((int *)str);
	size[0] /= sizeof(struct ranlib);
	tab = sorttab(gen_array((void *)str + 4, size[0], file), size[0]);
	size[1] = 0;
	while (size[1] < size[0])
	{
		if (!(size[1] != 0 && tab[size[1] - 1] == tab[size[1]]))
		{
			header = (void*)file + tab[size[1]];
			str = ft_strstr(header->ar_name, ARFMAG) + ft_strlen(ARFMAG);
			ft_printname(filename, str);
			ft_otool((void*)header + sizeof(struct ar_hdr) + ext_num, str);
		}
		size[1]++;
	}
}
