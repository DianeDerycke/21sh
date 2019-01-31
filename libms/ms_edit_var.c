/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_edit_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:39:32 by dideryck          #+#    #+#             */
/*   Updated: 2018/09/24 19:44:38 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_edit_var(char *v_name, char *v_value, char ***env, size_t index)
{
	ft_strdel((*env + index));
	*(*env + index) = ms_create_variable(v_name, v_value);
}
