/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_edit_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:39:32 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:40:27 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void	sh_edit_var(char *v_name, char *v_value, char ***env, size_t index)
{
	ft_strdel((*env + index));
	*(*env + index) = sh_create_variable(v_name, v_value);
}
