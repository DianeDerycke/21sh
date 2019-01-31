/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:31:16 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/24 18:27:39 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_get_cwd(char **buf)
{
	if (!(*buf = malloc(MS_BUFF_SIZE)))
		ms_malloc_error();
	if (!(getcwd(*buf, MS_BUFF_SIZE)))
	{
		ft_strdel(buf);
		return (FAILURE);
	}
	return (SUCCESS);
}
