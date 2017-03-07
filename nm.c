/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 23:02:33 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/06 21:22:28 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char				use_buf(char *str)
{
	if (!ft_strcmp(str, SECT_TEXT))
		return ('T');
	if (!ft_strcmp(str, SECT_DATA))
		return ('D');
	if (!ft_strcmp(str, SECT_BSS))
		return ('B');
	return ('S');
}

char				display_symbole(size_t n_type, int value, char *buf)
{
	size_t			tmp;
	char			r;

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

void				ft_nm(char *file, char *filename)
{
	unsigned int	magic_number;

	magic_number = *(int *)file;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(file);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle(file);
	else
	{
		if (!ft_strncmp(file, ARMAG, SARMAG))
			handle_ar(file, filename);
		else
			ft_printf("File format unknown for %s", filename);
	}
}

static void			run_nm(char *str)
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
		ft_nm(ptr, str);
		munmap(ptr, buf.st_size);
	}
}

int					main(int ac, char **av)
{
	int				i;

	i = 1;
	if (ac < 3)
		run_nm(ac == 2 ? av[1] : "a.out");
	else
		while (i < ac)
		{
			write(1, "\n", 1);
			ft_putstr(av[i]);
			write(1, ":\n", 2);
			run_nm(av[i++]);
		}
	return (0);
}
