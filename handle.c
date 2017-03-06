/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 19:15:53 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/05 20:31:41 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_64(char *file)
{
	size_t					i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	char					*segment_name[4096];
	t_nm					*tmp;

	segment_name[0] = NULL;
	header = (struct mach_header_64 *)file;
	i = 0;
	lc = (void *)file + sizeof(struct mach_header_64);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			tmp = sort_list(prepare_print((struct symtab_command *)lc, segment_name, file));
		if (lc->cmd == LC_SEGMENT_64)
			get_segment_name((void *)lc, segment_name);
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	display_list(tmp);
}

void		handle(char *file)
{
	size_t					i;
	struct mach_header		*header;
	struct load_command		*lc;
	char					*segment_name[4096];
	t_nm					*tmp;

	segment_name[0] = NULL;
	header = (struct mach_header *)file;
	i = 0;
	lc = (void *)file + sizeof(struct mach_header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			tmp = sort_list(prepare_print_32((struct symtab_command *)lc, segment_name, file));
		else if (lc->cmd == LC_SEGMENT)
			get_segment_name_32((void *)lc, segment_name);
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	display_list(tmp);
}

void		handle_ar(char *file, char *filename)
{
	struct ar_hdr	*header;
	struct ranlib	*rl;
	char			*str;
	int				ext_num;
	int				size;
	int					i;

	header = (void *)file + SARMAG;
	ext_num = ft_atoi(header->ar_name + ft_strlen(AR_EFMT1));
	str = (void*)file + sizeof(struct ar_hdr) + SARMAG + ext_num;
	rl = (void*)str + 4;
	size = *((int *)str);
	size /= sizeof(struct ranlib);
	i = 0;
	while (i < size)
	{
		header = (void*)file + rl[i].ran_off;
		str = ft_strstr(header->ar_name, ARFMAG) + ft_strlen(ARFMAG);
		ft_printName(filename, str);
		ft_nm((void*)header + sizeof(struct ar_hdr) + ext_num, str);
		i++;
	}
}

char		use_buf(char *str)
{
	if (!ft_strcmp(str, SECT_TEXT))
		return ('T');
	if (!ft_strcmp(str, SECT_DATA))
		return ('D');
	if (!ft_strcmp(str, SECT_BSS))
		return ('B');
	return ('S');
}

char		display_symbole(size_t n_type, int value, char *buf)
{
	size_t	tmp;
	char	r;

	tmp = n_type;
	r = 0;
	n_type = n_type & N_TYPE;
	if (n_type == N_UNDF || n_type == N_PBUD)
	{
		if (value)
			r = 'C';
		else
			r = 'U';
	}
	else if (n_type == N_ABS)
		r = 'A';
	else if (n_type == N_INDR)
		r = 'I';
	else if (n_type == N_SECT)
		r = use_buf(buf);
	if (!(tmp & N_EXT) && r)
		r += 32;
	return (r);
}