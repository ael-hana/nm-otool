/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 23:02:33 by ael-hana          #+#    #+#             */
/*   Updated: 2017/02/21 18:23:50 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "nm.h"

void		ft_putnbr_base(unsigned long long int num, int base)
{
	char	*str;

	str = "0123456789abcdef";
	if (num / base)
		ft_putnbr_base(num / base, base);
	write(1, str + (num % base), 1);
}


void		display_value(size_t value)
{
	if (value > 0)
	{
		ft_putstr("0000000");
		ft_putnbr_base(value, 16);
	}
	else
		ft_putstr("                ");
	ft_putchar(' ');
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

t_nm		*new_node(void *prev)
{
	t_nm	*ptr;

	ptr = malloc(sizeof(t_nm));
	if (!ptr)
		return (NULL);
	ptr->prev = prev;
	return (ptr);
}

void		*prepare_print(struct symtab_command *sym, char **buf, char *file)
{
	int				i;
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
		++i;
		if (i < sym->nsyms)
		{
			ptr->next = new_node(ptr);
			ptr = ptr->next;
		}
	}
	return (r);
}

void		*prepare_print_32(struct symtab_command *sym, char **buf, char *file)
{
	int				i;
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
		ptr->type = display_symbole(tab[i].n_type, tab[i].n_value, buf[tab[i].n_sect - 1]);
		ptr->name = stringtable + tab[i].n_un.n_strx;
		++i;
		if (i < sym->nsyms)
		{
			ptr->next = new_node(ptr);
			ptr = ptr->next;
		}
	}
	return (r);
}


void		get_segment_name(struct segment_command_64 *seg, char **ptr)
{
	int		i;
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
	int		i;
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

t_nm		*reset_list(t_nm *ptr)
{
	while (ptr->prev)
		ptr = ptr->prev;
	return (ptr);
}

int			sorted(t_nm *ptr)
{
	while (ptr->prev)
		ptr = ptr->prev;
	while (ptr->next)
	{
		if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

t_nm		*sort_list(t_nm *ptr)
{
	t_nm	*tmp;

	while (!sorted(ptr))
	{
		ptr = reset_list(ptr);
		while (ptr->next)
		{
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			{
				tmp = ptr;
				ptr = ptr->next;
				ptr->prev = tmp->prev;
				if (tmp->prev)
					tmp->prev->next = ptr;
				tmp->prev = ptr;
				tmp->next = ptr->next;
				if (tmp->next)
					tmp->next->prev = tmp;
				ptr->next = tmp;
			}
			ptr = ptr->next;
		}
	}
	return (reset_list(ptr));
}

void		display_list(t_nm *ptr)
{
	while (ptr)
	{
		display_value(ptr->hex);
		ft_putchar(ptr->type);
		ft_putstr(" ");
		ft_putstr(ptr->name);
		ft_putstr("\n");
		ptr = ptr->next;
	}
}

void		handle_64(char *file)
{
	int						i;
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
	int						i;
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

int			reverse_int(int x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);
}

void		fat_handle(char *file, char *str)
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
	ft_nm(file + reverse_int(offset), str);
}

void		ft_printName(char *str, char *str2)
{
	ft_putstr("\n");
	ft_putstr(str);
	ft_putstr("(");
	ft_putstr(str2);
	ft_putstr(")\n");
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

void		ft_nm(char *file, char *filename)
{
	int		magic_number;

	magic_number = *(int *)file;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(file);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle(file);
	else if (magic_number == FAT_CIGAM || magic_number == FAT_CIGAM)
	{
		fat_handle(file, filename);
	}
	else
	{
		if (!ft_strncmp(file, ARMAG, SARMAG))
			handle_ar(file, filename);
		else
			ft_putstr("Here");
	}
}

int			main(int ac, char **av)
{
	int		fd;
	char	*ptr;
	struct stat	buf;

	if (ac != 2)
	{
		ft_putstr_fd("Missing ARG\n", 2);
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_putstr_fd("Open failed\n", 2);
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_putstr_fd("Stat failed\n", 2);
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
				MAP_FAILED)
	{
		ft_putstr_fd("Mmap failed\n", 2);
		return (EXIT_FAILURE);
	}
	ft_nm(ptr, av[2]);
	munmap(ptr, buf.st_size);
	return (0);
}
