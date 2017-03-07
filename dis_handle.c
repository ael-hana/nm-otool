/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 19:26:55 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/06 17:29:44 by ael-hana         ###   ########.fr       */
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

static void		init(char **str, int len)
{
	int i;

	i = 0;
	*str = malloc(sizeof(char) * (len + 1));
	while (i < (len + 1))
	{
		(*str)[i++] = '0';
	}
	(*str)[i] = '\0';
}

static int		gen_hexa(unsigned long n, char **str, int i)
{
	unsigned int			a;
	unsigned int			u;
	char					*val;

	val = "0123456789abcdef";
	u = 0;
	a = n % 16;
	n = n / 16;
	if (n > 0)
		u = u + gen_hexa(n, str, (i - 1));
	(*str)[i] = val[a];
	u++;
	return (u);
}

int				ft_hexa(unsigned long n, char **str, int i)
{
	init(str, i);
	return (gen_hexa(n, str, i));
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
		if (tab[i].n_value || (tab[i].n_type & N_TYPE) == N_SECT)
			ft_hexa(tab[i].n_value, &ptr->hex, 15);
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
		if (tab[i].n_value || (tab[i].n_type & N_TYPE) == N_SECT)
			ft_hexa(tab[i].n_value, &ptr->hex, 15);
		//ptr->hex = tab[i].n_value;
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
