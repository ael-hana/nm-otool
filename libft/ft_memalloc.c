/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 01:00:10 by ael-hana          #+#    #+#             */
/*   Updated: 2015/11/30 07:33:36 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	char	*ptr;

	if (!(ptr = malloc(sizeof(char) * size)))
		return (NULL);
	while (size)
		ptr[(size--) - 1] = 0;
	return (ptr);
}
