/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_undefined_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:26:31 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:42:08 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

ssize_t		sh_undefined_variable(char *var)
{
	ft_putstr_fd(var, 2);
	ft_putendl_fd(": Undefined variable.", 2);
	return (FAILURE);
}
