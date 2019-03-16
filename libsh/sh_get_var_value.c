/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_var_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:58:31 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/16 14:41:19 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char		*sh_get_var_value(char *var)
{
	char	*path;
	size_t	i;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] != '=')
		i++;
	if (!(path = ft_strdup(var + i + 1)))
		sh_malloc_error();
	return (path);
}