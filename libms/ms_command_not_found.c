/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_not_found.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 20:03:40 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/18 15:58:43 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_command_not_found(char *cmd)
{
	if (!cmd)
		return (FAILURE);
	ft_putstr_fd("21sh: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	return (FAILURE);
}
