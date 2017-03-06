/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 19:26:55 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/05 19:49:21 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		get_segment_name(struct segment_command_64 *seg, char **ptr)
{
	size_t	i;
	int		i2;
	struct section_64	*sec;

	i = 0;
	i2 = 0;
	sec = (void *)((char*)seg + sizeof(struct segment_command_64));
	while (ptr[i2])
		++i2;
	while (i < seg->nsects)
	{
		ptr[i2] = sec[i].sectname;
		++i2;
		++i;
	}
	ptr[i2] = NULL;
}

void		get_segment_name_32(struct segment_command *seg, char **ptr)
{
	size_t	i;
	int		i2;
	struct section	*sec;

	i = 0;
	i2 = 0;
	sec = (void *)((char*)seg + sizeof(struct segment_command));
	while (ptr[i2])
		++i2;
	while (i < seg->nsects)
	{
		ptr[i2] = sec[i].sectname;
		++i2;
		++i;
	}
	ptr[i2] = NULL;
}

void		*prepare_print(struct symtab_command *sym, char **buf, char *file)
{
	size_t			i;
	char			*stringtable;
	struct nlist_64	*tab;
	t_nm			*ptr;
	void			*r;

	tab = (void *)file + sym->symoff;
	stringtable = (void *)file + sym->stroff;
	i = 0;
	ptr = new_node(NULL);
	r = ptr;
	while (i < sym->nsyms)
	{
		ptr->hex = tab[i].n_value;
		ptr->type = display_symbole(tab[i].n_type, tab[i].n_value, buf[tab[i].n_sect - 1]);
		ptr->name = stringtable + tab[i].n_un.n_strx;
		ptr->type = (tab[i].n_type & N_STAB) ? '*' : ptr->type;
		++i;
		if (i >= sym->nsyms)
			return (r);
		ptr->next = new_node(ptr);
		ptr = ptr->next;
	}
	return (r);
}

void		*prepare_print_32(struct symtab_command *sym,
			char **buf, char *file)
{
	size_t			i;
	char			*stringtable;
	struct nlist	*tab;
	t_nm			*ptr;
	void			*r;

	tab = (void *)file + sym->symoff;
	stringtable = (void *)file + sym->stroff;
	i = 0;
	ptr = new_node(NULL);
	r = ptr;
	while (i < sym->nsyms)
	{
		ptr->hex = tab[i].n_value;
		ptr->type = display_symbole(tab[i].n_type, tab[i].n_value,
					buf[tab[i].n_sect - 1]);
		ptr->name = stringtable + tab[i].n_un.n_strx;
		ptr->type = (tab[i].n_type & N_STAB) ? '*' : ptr->type;
		++i;
		if (i >= sym->nsyms)
			return (r);
		ptr->next = new_node(ptr);
		ptr = ptr->next;
	}
	return (r);
}
