/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 19:04:11 by ael-hana          #+#    #+#             */
/*   Updated: 2015/11/27 20:29:21 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr;
	char	*ptr2;

	ptr = dst;
	ptr2 = (char *)src;
	while (0 < n--)
		*ptr++ = *ptr2++;
	return (dst);
}
