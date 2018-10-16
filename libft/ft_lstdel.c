/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 23:17:03 by dideryck          #+#    #+#             */
/*   Updated: 2017/11/30 00:49:06 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*node;
	t_list		*tmp;

	if (!alst || !(node = *alst))
		return ;
	tmp = node;
	while (tmp)
	{
		node = tmp;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = node->next;
	}
	*alst = NULL;
}
