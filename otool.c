#include "nm.h"

void		ft_putnbr_base(unsigned long long int num, int base)
{
	char	*str;

	str = "0123456789abcdef";
	if (num / base)
		ft_putnbr_base(num / base, base);
	write(1, str + (num % base), 1);
}

static void		h_z(unsigned long long int num)
{
	write(1, "0", 1);
	ft_putnbr_base(num & 0xff, 16);
}

void		display_section(long long int addres, int size, char *ptr)
{
	int		i;

	i = 0;
	ft_putstr("(__TEXT,__text) section");
	while (i < size)
	{
		if (!(i % 16))
		{
			ft_putchar('\n');
			ft_putstr("0000000");
			ft_putnbr_base(addres, 16);
			ft_putchar(' ');
			addres += 16;
		}
		(ptr[i] & 0xff) > 15 ? ft_putnbr_base(ptr[i] & 0xff, 16) : h_z(ptr[i]);
		ft_putchar(' ');
		i++;
	}
}

void		get_seg_64(struct segment_command_64 *seg, struct mach_header_64 *h)
{
	int					i;
	struct section_64	*sec;

	i = 0;
	sec = (struct section_64 *)((char *)seg +
			sizeof(struct segment_command_64));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec[i].segname, SEG_TEXT) &&
				!ft_strcmp(sec[i].sectname, SECT_TEXT))
		{
			display_section(sec[i].addr,
					sec[i].size, (char *)h + sec[i].offset);
		}
		++i;
	}
}

void		get_seg(struct segment_command *seg, struct mach_header *h)
{
	int					i;
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

void		handle_64_otool(char *file)
{
	int						i;
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
}

void		handle_otool(char *file)
{
	int						i;
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
}

void		ft_otool(char *file, char *filename)
{
	int		magic_number;

	magic_number = *(int *)file;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64_otool(file);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_otool(file);
}

int			main(int ac, char **av)
{
	int			fd;
	char		*ptr;
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
	ft_otool(ptr, av[2]);
	munmap(ptr, buf.st_size);
	return (0);
}
