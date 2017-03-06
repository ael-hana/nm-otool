/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 23:13:02 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/05 19:52:02 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# include "libft/libft.h"
# include <stdio.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <stdlib.h>

typedef struct			s_nm{
	size_t				hex;
	char				type;
	char				*name;
	struct s_nm			*prev;
	struct s_nm			*next;
}						t_nm;
void					ft_printName(char *str, char *str2);
int						reverse_int(int x);
void					display_list(t_nm *ptr);
void					display_value(size_t value);
void					ft_putnbr_base(unsigned long long int num, int base);
void					*prepare_print_32(struct symtab_command *sym,
						char **buf, char *file);
void					*prepare_print(struct symtab_command *sym,
						char **buf, char *file);
void					get_segment_name_32(struct segment_command *seg,
						char **ptr);
void					get_segment_name(struct segment_command_64 *seg,
						char **ptr);
void					handle(char *file);
void					handle_64(char *file);
void					handle_ar(char *file, char *filename);
char					display_symbole(size_t n_type, int value, char *buf);
char					use_buf(char *str);
t_nm					*new_node(void *prev);
t_nm					*reset_list(t_nm *ptr);
int						sorted(t_nm *ptr);
t_nm					*sort_list(t_nm *ptr);
void					ft_nm(char *file, char *filename);
#endif
