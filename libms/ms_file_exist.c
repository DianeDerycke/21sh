/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:52:06 by dideryck          #+#    #+#             */
/*   Updated: 2019/02/18 15:59:11 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_file_exist(const char *path)
{
	struct stat	buffer;

	if (!path)
		return (FAILURE);
	if (lstat(path, &buffer) == 0 || stat(path, &buffer) == 0)
		return (SUCCESS);
	return (FAILURE);
}
