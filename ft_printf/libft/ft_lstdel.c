/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 18:46:10 by ael-hana          #+#    #+#             */
/*   Updated: 2015/12/01 19:05:09 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*ptr;

	while ((ptr = (**alst).next))
	{
		(*del)((**alst).content, (**alst).content_size);
		free(*alst);
		*alst = ptr;
	}
	(*del)((**alst).content, (**alst).content_size);
	free(*alst);
	*alst = NULL;
}
