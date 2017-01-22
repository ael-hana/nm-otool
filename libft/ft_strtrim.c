/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 06:02:43 by ael-hana          #+#    #+#             */
/*   Updated: 2015/12/02 18:21:54 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_cpystr(char *dst, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	if (!dst || !src)
		return (NULL);
	while (n > i && src[i])
	{
		dst[i] = src[i];
		i += 1;
	}
	dst[i] = '\0';
	return (dst);
}

char			*ft_strtrim(char const *s)
{
	int			i;
	int			j;
	char		*ptr;

	i = 0;
	if (!s)
		return (NULL);
	if (!*s)
		return ("");
	j = ft_strlen(s) - 1;
	while (j >= 0 && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		j--;
	}
	if (++j < 0)
		j = 0;
	if (0 >= (i + j))
		return (NULL);
	if ((ptr = (char *)malloc(sizeof(char) * 2 + j)))
		return (ft_cpystr(ptr, s + i, j));
	return (NULL);
}
