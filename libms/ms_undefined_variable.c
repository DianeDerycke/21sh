/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_undefined_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:26:31 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/24 19:41:05 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

ssize_t		ms_undefined_variable(char *var)
{
	ft_putstr_fd(var, 2);
	ft_putendl_fd(": Undefined variable.", 2);
	return (FAILURE);
}
