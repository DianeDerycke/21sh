/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 14:43:26 by mrandou           #+#    #+#             */
/*   Updated: 2018/10/17 14:46:36 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

t_env		*sh_create_elem(void)
{
	t_env		*new;
	if (!(new = malloc(sizeof(t_env))))
		ft_malloc_error("21sh");
	new->key = NULL;
	new->value = NULL;
	return (new);
}
