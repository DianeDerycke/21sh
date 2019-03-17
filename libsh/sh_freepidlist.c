/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_freepidlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:59:51 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 16:55:06 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void	sh_freepidlist(t_pid **list)
{
	t_pid	*tmp;

	tmp = NULL;
	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		tmp = NULL;
	}
	free(*list);
	*list = NULL;
	list = NULL;
}
