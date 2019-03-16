/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_file_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:52:06 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:40:43 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_file_exist(const char *path)
{
	struct stat	buffer;

	if (!path)
		return (FAILURE);
	if (lstat(path, &buffer) == 0 || stat(path, &buffer) == 0)
		return (SUCCESS);
	return (FAILURE);
}
