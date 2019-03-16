/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:31:16 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:40:59 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_get_cwd(char **buf)
{
	if (!(*buf = malloc(MS_BUFF_SIZE)))
		sh_malloc_error();
	if (!(getcwd(*buf, MS_BUFF_SIZE)))
	{
		ft_strdel(buf);
		return (FAILURE);
	}
	return (SUCCESS);
}
