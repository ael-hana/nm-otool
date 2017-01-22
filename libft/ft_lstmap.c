/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 19:30:06 by ael-hana          #+#    #+#             */
/*   Updated: 2015/12/01 22:06:25 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ptr;
	t_list	*tmp2;
	void	*tmp;

	ptr = (*f)(lst);
	if ((tmp = ft_lstnew(ptr->content, ptr->content_size)))
	{
		tmp2 = (t_list *)tmp;
		lst = lst->next;
		while (lst)
		{
			ptr = (*f)(lst);
			if (!(tmp2->next = ft_lstnew(ptr->content, ptr->content_size)))
				return (NULL);
			tmp2 = tmp2->next;
			lst = lst->next;
		}
	}
	return ((t_list *)tmp);
}
