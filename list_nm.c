/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 19:30:53 by ael-hana          #+#    #+#             */
/*   Updated: 2017/03/06 22:16:34 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_nm		*new_node(void *prev)
{
	t_nm	*ptr;

	ptr = malloc(sizeof(t_nm));
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, sizeof(t_nm));
	ptr->type = 'U';
	ptr->prev = prev;
	return (ptr);
}

t_nm		*reset_list(t_nm *ptr)
{
	while (ptr->prev)
		ptr = ptr->prev;
	return (ptr);
}

int			sorted(t_nm *ptr)
{
	while (ptr->prev)
		ptr = ptr->prev;
	while (ptr->next)
	{
		if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

t_nm		*sort_list(t_nm *ptr)
{
	t_nm	*tmp;

	while (!sorted(ptr))
	{
		ptr = reset_list(ptr);
		while (ptr->next)
		{
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			{
				tmp = ptr;
				ptr = ptr->next;
				ptr->prev = tmp->prev;
				if (tmp->prev)
					tmp->prev->next = ptr;
				tmp->prev = ptr;
				tmp->next = ptr->next;
				if (tmp->next)
					tmp->next->prev = tmp;
				ptr->next = tmp;
			}
			ptr = ptr->next;
		}
	}
	return (reset_list(ptr));
}
