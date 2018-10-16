/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 14:11:19 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/06/25 15:01:15 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_lst(t_dblist *lst)
{
	t_elem		*ptr;
	t_elem		*next_ptr;
	char		*tmp;

	ptr = lst->first;
	next_ptr = lst->first->next;
	while (ptr->content != lst->last->content)
	{
		if (ft_strcmp(ptr->content, next_ptr->content) > 0)
		{
			tmp = ptr->content;
			ptr->content = next_ptr->content;
			next_ptr->content = tmp;
		}
		ptr = ptr->next;
		next_ptr = ptr->next;
	}
	ptr = lst->first;
	while (ptr->next && ft_strcmp(ptr->content, ptr->next->content) <= 0)
		ptr = ptr->next;
	if (ptr->next)
		ft_sort_lst(lst);
}
