/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:02:53 by ael-hana          #+#    #+#             */
/*   Updated: 2015/12/03 00:25:20 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strlen_split(char *str, char c)
{
	int			i;
	int			num;

	i = 0;
	num = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c && str[i])
		{
			num += 1;
			while (str[i] != c && str[i])
				i++;
		}
		if (str[i])
			i++;
	}
	return (num);
}

static int		ft_strlen_inter(char *str, char c)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != c)
		i += 1;
	return (i);
}

static char		*ft_strcopy(char *dst, char *src, char c)
{
	size_t		i;

	i = 0;
	if (!dst || !src)
		return (NULL);
	while (src[i] != c && src[i])
	{
		dst[i] = src[i];
		i += 1;
	}
	dst[i] = '\0';
	return (dst);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	int			i;
	int			n;

	if (!s)
		return (NULL);
	n = ft_strlen_split((char *)s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	tab[n] = NULL;
	i = 0;
	while (i < n)
	{
		while (*s == c)
			s++;
		tab[i] = (char *)malloc((ft_strlen_inter((char *)s, c) + 1)
				* sizeof(char));
		if (!tab[i])
			return (NULL);
		ft_strcopy(tab[i], (char *)s, c);
		while (*s != c && *s)
			s++;
		i += 1;
	}
	return (tab);
}
