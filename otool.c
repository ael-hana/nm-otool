/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:38:28 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/07 17:39:36 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_64_otool(char *file)
{
	size_t					i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = (struct mach_header_64 *)file;
	lc = (void *)file + sizeof(struct mach_header_64);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			get_seg_64((void *)lc, header);
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	ft_putstr("\n");
}

void		handle_otool(char *file)
{
	size_t					i;
	struct mach_header		*header;
	struct load_command		*lc;

	header = (struct mach_header *)file;
	lc = (void *)file + sizeof(struct mach_header_64);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			get_seg((void *)lc, header);
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	ft_putstr("\n");
}

void		ft_otool(char *file, char *filename)
{
	unsigned int	magic_number;

	magic_number = *(int *)file;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64_otool(file);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_otool(file);
	else if (magic_number == FAT_CIGAM || magic_number == FAT_CIGAM)
		fat_handle(file, filename);
	else
	{
		if (ft_strncmp(file, ARMAG, SARMAG) == 0)
			handle_otool_ar(file, filename);
		else
			ft_putendl("Unknown binary");
	}
}

void		run_otool(char *str)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(str, O_RDONLY)) < 0)
		ft_putstr_fd("Open failed\n", 2);
	else if (fstat(fd, &buf) < 0)
		ft_putstr_fd("Stat failed\n", 2);
	else if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
		MAP_FAILED)
		ft_putstr_fd("Mmap failed\n", 2);
	else
	{
		ft_otool(ptr, str);
		munmap(ptr, buf.st_size);
	}
}

int			main(int ac, char **av)
{
	int		i;

	i = 1;
	if (ac < 2)
		ft_putstr("Missing ARGV\n");
	else
		while (i < ac)
		{
			if (av[i][ft_strlen(av[i]) - 1] == 'a' &&
				av[i][ft_strlen(av[i]) - 2] == '.')
				ft_printf("Archive : %s\n", av[i]);
			else
				ft_printf("%s:\n", av[i]);
			run_otool(av[i++]);
		}
	return (0);
}
