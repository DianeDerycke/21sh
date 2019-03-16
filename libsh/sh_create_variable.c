/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_create_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:14:23 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:40:19 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char	*sh_create_variable(char *var_name, char *var_value)
{
	size_t		i;
	char		*tmp;
	char		*tmp1;

	i = 1;
	if (!(tmp = ft_strdup(var_name)))
		sh_malloc_error();
	if (!(tmp1 = ft_strjoin_free(tmp, STR_EQUAL)))
		sh_malloc_error();
	if (var_value)
	{
		if (!(tmp = ft_strjoin_free(tmp1, var_value)))
			sh_malloc_error();
		return (tmp);
	}
	return (tmp1);
}
