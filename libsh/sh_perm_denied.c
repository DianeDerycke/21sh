/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_perm_denied.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:05:18 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:41:42 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_perm_denied(char *utility)
{
	ft_putstr_fd(utility, 2);
	ft_putendl_fd(": Permission denied.", 2);
	return (FAILURE);
}
