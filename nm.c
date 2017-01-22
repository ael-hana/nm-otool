/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 23:02:33 by ael-hana          #+#    #+#             */
/*   Updated: 2017/01/22 00:38:55 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "nm.h"

void		print_output(int nsyms, int symoff, int stroff, char *file)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*tab;

	tab = (void *)file + symoff;
	stringtable = (void *)file + stroff;
	i = 0;
	while (i < nsyms)
	{
		ft_putstr_fd(stringtable + tab[i].n_un.n_strx, 1);
		ft_putstr_fd("\n", 1);
		++i;
	}
}

void		handle_64(char *file)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)file;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)file + sizeof(struct mach_header_64);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, file);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
}

void		ft_nm(char *file)
{
	int		magic_number;

	magic_number = *(int *)file;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(file);
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
	ft_nm(ptr);
	munmap(ptr, buf.st_size);
	return (0);
}
