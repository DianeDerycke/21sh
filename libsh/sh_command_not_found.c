/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_not_found.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 20:03:40 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:40:12 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_command_not_found(char *cmd)
{
	if (!cmd)
		return (FAILURE);
	ft_putstr_fd("21sh: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	return (FAILURE);
}
