/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 22:06:11 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/31 10:15:45 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_read_input(char **input)
{
	ssize_t		is_read_done;

	is_read_done = get_next_line(0, input);
	if (is_read_done == -1)
	{
		ft_strdel(input);
		return (ERR_INTR);
	}
	if (is_read_done == 1 && !(**input))
	{
		ft_strdel(input);
		return (PAGAIN);
	}
	return (SUCCESS);
}
