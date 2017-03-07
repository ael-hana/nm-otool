/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 19:15:53 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/06 21:26:42 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void						handle_64(char *file)
{
	unsigned int			i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	char					*segment_name[4096];
	struct symtab_command	*sym;

	ft_bzero(segment_name, 4096);
	header = (struct mach_header_64 *)file;
	i = 0;
	lc = (void *)file + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			sym = (struct symtab_command *)lc;
		if (lc->cmd == LC_SEGMENT_64)
			get_segment_name((struct segment_command_64 *)lc, segment_name);
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	display_list(sort_list(prepare_print(sym, segment_name, file)));
}

void						handle(char *file)
{
	size_t					i;
	struct mach_header		*header;
	struct load_command		*lc;
	char					*segment_name[4096];
	struct symtab_command	*sym;

	ft_bzero(segment_name, 4096);
	header = (struct mach_header *)file;
	i = 0;
	lc = (void *)file + sizeof(struct mach_header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			sym = (struct symtab_command *)lc;
		else if (lc->cmd == LC_SEGMENT)
			get_segment_name_32((void *)lc, segment_name);
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	display_list(sort_list(prepare_print_32(sym, segment_name, file)));
}

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

void						handle_ar(char *file, char *filename)
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
			ft_nm((void*)header + sizeof(struct ar_hdr) + ext_num, str);
		}
		size[1]++;
	}
}
