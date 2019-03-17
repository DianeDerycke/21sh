/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_push_pidnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:50:02 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 16:54:31 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

int		sh_push_pidnew(int pid, t_pid **list)
{
	t_pid	*tmp;

	tmp = NULL;
	if (!list || !*list)
	{
		if (!(*list = sh_pidnew(pid)))
			return (FAILURE);
	}
	else
	{
		tmp = *list;
		while ((*list)->next)
			(*list) = (*list)->next;
		if (!((*list)->next = sh_pidnew(pid)))
			return (FAILURE);
	}
	return (SUCCESS);
}
