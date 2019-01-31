/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_var_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 18:50:04 by dideryck          #+#    #+#             */
/*   Updated: 2018/10/02 12:11:58 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char		*ms_get_var_name(char *arg, size_t end)
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
		ms_malloc_error();
	return (tmp);
}
