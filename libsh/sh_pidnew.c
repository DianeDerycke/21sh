/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pidnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:47:02 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 16:53:53 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

t_pid	*sh_pidnew(int pid)
{
	t_pid	*new;

	if (!(new = malloc(sizeof(t_pid))))
		ft_malloc_error();
	new->proc = pid;
	new->next = NULL;
	return (new);
}
