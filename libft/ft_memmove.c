/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 01:47:39 by ael-hana          #+#    #+#             */
/*   Updated: 2015/11/27 20:29:29 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str;

	if ((!dst && !src) || !(str = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_memcpy(str, src, len);
	return (ft_memcpy(dst, str, len));
}
