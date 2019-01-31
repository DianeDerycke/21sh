/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_not_found.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 20:03:40 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/25 15:06:23 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_command_not_found(char *cmd)
{
	ft_putstr("21sh: command not found: ");
	ft_putendl(cmd);
	return (FAILURE);
}
