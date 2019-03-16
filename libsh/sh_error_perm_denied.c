/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error_perm_denied.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:24:35 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:40:30 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_error_perm_denied(char *utility, char *cmd)
{
	ft_putstr_fd(utility, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Permisson denied.", 2);
	return (FAILURE);
}
