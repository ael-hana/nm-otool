/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 01:55:55 by ael-hana          #+#    #+#             */
/*   Updated: 2015/11/27 02:43:11 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmap(char const *s, char (*f)(char))
{
	char			*ptr;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		ptr[i] = (*f)((char)s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
