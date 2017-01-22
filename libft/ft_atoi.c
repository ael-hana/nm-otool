/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 01:57:03 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/28 06:34:53 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		num;
	int		i;
	char	ok;

	num = 0;
	i = 0;
	ok = 0;
	while (str[i] == 32 || ((str[i] >= 9) && (str[i] <= 13)))
		++i;
	if (str[i] == '-')
		ok = 1;
	if (!ft_strcmp("-2147483648", str + i))
		if (!*(str + i + ft_strlen("-2147483648")))
			return (-2147483648);
	if (str[i] == '+' || str[i] == '-')
		i += 1;
	while (((str[i] - '0') >= 0) && ((str[i] - '9') <= 9))
	{
		num = num * 10;
		num = str[i] - 48 + num;
		++i;
	}
	if (ok)
		num *= -1;
	return (num);
}
