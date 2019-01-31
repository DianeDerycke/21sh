/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_perm_denied.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:05:18 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/24 19:39:20 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_perm_denied(char *utility)
{
	ft_putstr_fd(utility, 2);
	ft_putendl_fd(": Permission denied.", 2);
	return (FAILURE);
}
