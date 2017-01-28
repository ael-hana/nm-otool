/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 23:13:02 by ael-hana          #+#    #+#             */
/*   Updated: 2017/01/28 04:28:45 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# include "libft/libft.h"
# include <stdio.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
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
#endif
