/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:52:06 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/24 17:49:45 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_file_exist(const char *path)
{
	struct stat	buffer;

	if (lstat(path, &buffer) == 0 || stat(path, &buffer) == 0)
		return (SUCCESS);
	return (FAILURE);
}
