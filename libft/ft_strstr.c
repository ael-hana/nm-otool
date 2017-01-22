/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 00:17:34 by ael-hana          #+#    #+#             */
/*   Updated: 2015/12/03 00:09:05 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char	*str1;
	char	*str2;
	int		i;

	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!*str2)
		return (str1);
	while (*str1)
	{
		i = 0;
		while (str1[i] != '\0' && str1[i] == str2[i])
			i += 1;
		if (!str2[i])
			return (str1);
		++str1;
	}
	return (NULL);
}
