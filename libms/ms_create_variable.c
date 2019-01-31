/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:14:23 by DERYCKE           #+#    #+#             */
/*   Updated: 2018/10/03 17:49:07 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_create_variable(char *var_name, char *var_value)
{
	size_t		i;
	char		*tmp;
	char		*tmp1;

	i = 1;
	if (!(tmp = ft_strdup(var_name)))
		ms_malloc_error();
	if (!(tmp1 = ft_strjoin_free(tmp, STR_EQUAL)))
		ms_malloc_error();
	if (var_value)
	{
		if (!(tmp = ft_strjoin_free(tmp1, var_value)))
			ms_malloc_error();
		return (tmp);
	}
	return (tmp1);
}
