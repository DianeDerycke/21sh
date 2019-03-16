/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_var_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 18:50:04 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/16 14:41:11 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

char		*sh_get_var_name(char *arg, size_t end)
{
	char	*tmp;

	tmp = NULL;
	if (!arg)
		return (NULL);
	if (end > 0)
		tmp = ft_strndup(arg, end);
	else
		tmp = ft_strdup(arg);
	if (!tmp)
		sh_malloc_error();
	return (tmp);
}
