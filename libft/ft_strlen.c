/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 03:26:02 by ael-hana          #+#    #+#             */
/*   Updated: 2015/11/25 04:19:57 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlen(const char *s)
{
	unsigned int	*i;

	i = (unsigned int *)s;
	while (42)
	{
		if (!(*i & 0xFF))
			return ((unsigned char*)i - (unsigned char *)s);
		if (!(*i & 0xFF00))
			return ((unsigned char*)i - (unsigned char *)s + 1);
		if (!(*i & 0xFF0000))
			return ((unsigned char*)i - (unsigned char *)s + 2);
		if (!(*i & 0xFF000000))
			return ((unsigned char*)i - (unsigned char *)s + 3);
		++i;
	}
}
